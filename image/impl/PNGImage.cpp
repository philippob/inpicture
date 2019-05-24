#include <stdlib.h>
#include <stdio.h>
#include <png.h>

#include "PNGImage.h"
#include "../Image.h"

PNGImage::PNGImage(Image::Unit width, Image::Unit height) {
  initialize(width, height);
}

void PNGImage::load(const std::string &path) {
  FILE *file = fopen(path.c_str(), "rb");
  if (!file) {
    throw FileReadException{path};
  }

  Byte header[8];
  fread(&header, 0, 8, file);
  if (!png_sig_cmp(header, 0, 8)) {
    fclose(file);
    throw InvalidFileException{path, "PNG"};
  }

  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) {
    fclose(file);
    throw InputOutputException{"internal error"};
  }

  png_infop info = png_create_info_struct(png);
  if (!info) {
    fclose(file);
    throw InputOutputException{"internal error"};
  }

  if (setjmp(png_jmpbuf(png))) {
    fclose(file);
    throw InputOutputException{"internal error"};
  }

  png_init_io(png, file);
  png_read_info(png, info);

  width = png_get_image_width(png, info);
  height = png_get_image_height(png, info);

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

  auto x = png_get_rowbytes(png, info);

  auto *imageData = reinterpret_cast<png_bytep *>(malloc(sizeof(png_bytep) * height));
  for (Unit y = 0; y < height; y++)
    imageData[y] = reinterpret_cast<png_byte *>(malloc(png_get_rowbytes(png, info)));

  png_read_image(png, imageData);
  fclose(file);
  png_destroy_read_struct(&png, &info, NULL);

  initialize(width, height);

  for (Unit y = 0; y < height; y++) {
    png_bytep row = imageData[y];
    for (Unit x = 0; x < width; x++) {
      auto index = y * width + x;

      png_bytep pixel = &(row[x * 4]);
      buffer[index].values.red = pixel[0];
      buffer[index].values.green = pixel[1];
      buffer[index].values.blue = pixel[2];
      buffer[index].values.alpha = pixel[3];
    }
  }
}

void PNGImage::save(const std::string &path) {
  FILE *file = fopen(path.c_str(), "wb");
  if (!file) {
    throw FileWriteException{path};
  }

  png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) {
    fclose(file);
    throw InputOutputException{"Internal error"};
  }

  png_infop info = png_create_info_struct(png);
  if (!info) {
    fclose(file);
    throw InputOutputException{"Internal error"};
  }

  if (setjmp(png_jmpbuf(png))) {
    fclose(file);
    throw InputOutputException{"Internal error"};
  }

  png_init_io(png, file);
  png_set_IHDR(
      png,
      info,
      width,
      height,
      8,
      PNG_COLOR_TYPE_RGBA,
      PNG_INTERLACE_NONE,
      PNG_COMPRESSION_TYPE_DEFAULT,
      PNG_FILTER_TYPE_DEFAULT
  );
  png_write_info(png, info);

  auto *imageData = reinterpret_cast<png_bytep *>(malloc(sizeof(png_bytep) * height));
  for (Unit y = 0; y < height; y++)
    imageData[y] = reinterpret_cast<png_byte *>(malloc(width * sizeof(Pixel)));

  for (Unit y = 0; y < height; y++) {
    png_bytep row = imageData[y];
    for (Unit x = 0; x < width; x++) {
      auto index = y * width + x;

      png_bytep pixel = &(row[x * 4]);
      pixel[0] = buffer[index].values.red;
      pixel[1] = buffer[index].values.green;
      pixel[2] = buffer[index].values.blue;
      pixel[3] = buffer[index].values.alpha;
    }
  }

  png_write_image(png, imageData);
  png_write_end(png, NULL);

  fclose(file);
  png_destroy_write_struct(&png, &info);
}

Image::Unit PNGImage::getWidth() {
  return width;
}

Image::Unit PNGImage::getHeight() {
  return height;
}

Image::PixelBuffer &PNGImage::getPixelBuffer() {
  return buffer;
}

Image::Pixel &PNGImage::getPixel(Image::Unit x, Image::Unit y) {
  return buffer[y * width + x];
}

void PNGImage::setPixel(Image::Unit x, Image::Unit y, const Image::Pixel &pixel) {
  buffer[y * width + x] = pixel;
}

void PNGImage::initialize(Image::Unit width, Image::Unit height) {
  this->width = width;
  this->height = height;
  buffer.resize(width * height);
}
