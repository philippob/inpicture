#include "PNGPictureWriterReader.h"

#include <stdlib.h>
#include <stdio.h>
#include <png.h>

void PNGPictureWriterReader::write(std::string file, const Picture::Pointer &picture) {
  FILE *filePointer = fopen(file.c_str(), "wb");
  if (!filePointer) {
    throw FileWriteException{file};
  }

  png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) {
    fclose(filePointer);
    throw std::runtime_error{"internal exception"};
  }

  png_infop info = png_create_info_struct(png);
  if (!info) {
    fclose(filePointer);
    throw std::runtime_error{"internal exception"};
  }

  if (setjmp(png_jmpbuf(png))) {
    fclose(filePointer);
    throw std::runtime_error{"internal exception"};
  }

  png_init_io(png, filePointer);
  png_set_IHDR(
      png,
      info,
      picture->getWidth(),
      picture->getHeight(),
      8,
      PNG_COLOR_TYPE_RGBA,
      PNG_INTERLACE_NONE,
      PNG_COMPRESSION_TYPE_DEFAULT,
      PNG_FILTER_TYPE_DEFAULT
  );
  png_write_info(png, info);

  auto *imageData = reinterpret_cast<png_bytep *>(malloc(sizeof(png_bytep) * picture->getHeight()));
  for (Picture::Unit y = 0; y < picture->getHeight(); y++)
    imageData[y] = reinterpret_cast<png_byte *>(malloc(picture->getWidth() * sizeof(Picture::Pixel)));

  for (Picture::Unit y = 0; y < picture->getHeight(); y++) {
    png_bytep row = imageData[y];
    for (Picture::Unit x = 0; x < picture->getWidth(); x++) {

      png_bytep pixel = &(row[x * 4]);
      pixel[0] = picture->getPixel(x, y).channels.red;
      pixel[1] = picture->getPixel(x, y).channels.green;
      pixel[2] = picture->getPixel(x, y).channels.blue;
      pixel[3] = picture->getPixel(x, y).channels.alpha;
    }
  }

  png_write_image(png, imageData);
  png_write_end(png, NULL);

  fclose(filePointer);
  png_destroy_write_struct(&png, &info);
}

Picture::Pointer PNGPictureWriterReader::read(std::string file) {
  FILE *filePointer = fopen(file.c_str(), "rb");
  if (!filePointer) {
    throw FileReadException{file};
  }

  Picture::Byte header[8];
  fread(&header, 0, 8, filePointer);
  if (!png_sig_cmp(header, 0, 8)) {
    fclose(filePointer);
    throw InvalidFileException{file, "PNG"};
  }

  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) {
    fclose(filePointer);
    throw std::runtime_error{"internal exception"};
  }

  png_infop info = png_create_info_struct(png);
  if (!info) {
    fclose(filePointer);
    throw std::runtime_error{"internal exception"};
  }

  if (setjmp(png_jmpbuf(png))) {
    fclose(filePointer);
    throw std::runtime_error{"internal exception"};
  }

  png_init_io(png, filePointer);
  png_read_info(png, info);

  auto picture = std::make_unique<Picture>();
  picture->initialize(png_get_image_width(png, info), png_get_image_height(png, info));

  auto colorType = png_get_color_type(png, info);
  auto bitDepth = png_get_bit_depth(png, info);

  if (bitDepth == 16)
    png_set_strip_16(png);

  if (colorType == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png);

  if (colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8)
    png_set_expand_gray_1_2_4_to_8(png);

  if (png_get_valid(png, info, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png);

  if (colorType == PNG_COLOR_TYPE_RGB ||
      colorType == PNG_COLOR_TYPE_GRAY ||
      colorType == PNG_COLOR_TYPE_PALETTE)
    png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

  if (colorType == PNG_COLOR_TYPE_GRAY ||
      colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png);

  png_read_update_info(png, info);

  auto *imageData = reinterpret_cast<png_bytep *>(malloc(sizeof(png_bytep) * picture->getHeight()));
  for (Picture::Unit y = 0; y < picture->getHeight(); y++)
    imageData[y] = reinterpret_cast<png_byte *>(malloc(png_get_rowbytes(png, info)));

  png_read_image(png, imageData);
  fclose(filePointer);
  png_destroy_read_struct(&png, &info, NULL);

  for (Picture::Unit y = 0; y < picture->getHeight(); y++) {
    png_bytep row = imageData[y];
    for (Picture::Unit x = 0; x < picture->getWidth(); x++) {
      png_bytep pixel = &(row[x * 4]);

      picture->getPixel(x, y).channels.red = pixel[0];
      picture->getPixel(x, y).channels.green = pixel[1];
      picture->getPixel(x, y).channels.blue = pixel[2];
      picture->getPixel(x, y).channels.alpha = pixel[3];
    }
  }

  return picture;
}

bool PNGPictureWriterReader::isFileTypeSupported(std::string extension) const {
  return extension == "png";
}

