#include "JPEGPictureWriterReader.h"
#include "../../Picture.h"

#include <stdlib.h>
#include <stdio.h>
#include <jpeglib.h>

bool JPEGPictureWriterReader::isFileTypeSupported(std::string extension) const {
  return extension == "jpeg" || extension == "jpg";
}

void JPEGPictureWriterReader::write(std::string file, const Picture::Pointer &picture) {
  FILE *filePointer = fopen(file.c_str(), "wb");
  if (!filePointer) {
    throw FileWriteException{file};
  }

  auto errorHandler = [] (j_common_ptr errorData) {
    fcloseall();
    throw std::runtime_error{"internal exception"};
  };

  jpeg_compress_struct compressStruct;
  jpeg_error_mgr errorManager;

  compressStruct.err = jpeg_std_error(&errorManager);
  errorManager.error_exit = errorHandler;

  jpeg_create_compress(&compressStruct);
  jpeg_stdio_dest(&compressStruct, filePointer);

  compressStruct.image_width = picture->getWidth();
  compressStruct.image_height = picture->getHeight();
  compressStruct.input_components = 3;
  compressStruct.in_color_space = JCS_RGB;

  jpeg_set_defaults(&compressStruct);
  jpeg_set_quality(&compressStruct, 90, TRUE);
  jpeg_start_compress(&compressStruct, TRUE);

  JSAMPROW rowPointer[1];
  rowPointer[0] = new Picture::Byte[picture->getWidth() * 3];

  while (compressStruct.next_scanline < compressStruct.image_height) {
    Picture::Unit rowIndex = 0;

    for (Picture::Unit x = 0; x < picture->getWidth(); x++) {
      auto &pixel = picture->getPixel(x, compressStruct.next_scanline);

      rowPointer[0][rowIndex] = pixel.channels.red;
      rowPointer[0][rowIndex + 1] = pixel.channels.green;
      rowPointer[0][rowIndex + 2] = pixel.channels.blue;

      rowIndex += 3;
    }

    jpeg_write_scanlines(&compressStruct, rowPointer, 1);
  }

  jpeg_finish_compress(&compressStruct);
  fclose(filePointer);
  jpeg_destroy_compress(&compressStruct);
}

Picture::Pointer JPEGPictureWriterReader::read(std::string file) {
  FILE *filePointer = fopen(file.c_str(), "rb");
  if (!filePointer) {
    throw FileReadException{file};
  }

  auto errorHandler = [] (j_common_ptr errorData) {
    fcloseall();
    throw std::runtime_error{"internal exception"};
  };

  jpeg_decompress_struct decompressStruct;
  jpeg_error_mgr errorManager;

  decompressStruct.err = jpeg_std_error(&errorManager);
  errorManager.error_exit = errorHandler;

  jpeg_create_decompress(&decompressStruct);
  jpeg_stdio_src(&decompressStruct, filePointer);
  jpeg_read_header(&decompressStruct, TRUE);
  jpeg_start_decompress(&decompressStruct);

  int rowStride = decompressStruct.output_width * decompressStruct.output_components;
  JSAMPARRAY buffer = (*decompressStruct.mem->alloc_sarray)
      (reinterpret_cast<j_common_ptr>(&decompressStruct), JPOOL_IMAGE, rowStride, 1);

  auto picture = std::make_unique<Picture>();
  picture->initialize(decompressStruct.output_width, decompressStruct.output_height);

  auto channels = decompressStruct.num_components;
  if (channels != 3 && channels != 4) {
    jpeg_destroy_decompress(&decompressStruct);
    fclose(filePointer);
    throw InvalidFileException{file, "JPEG"};
  }

  Picture::Unit line = 0;

  while (decompressStruct.output_scanline < decompressStruct.output_height) {
    jpeg_read_scanlines(&decompressStruct, buffer, 1);

    for (Picture::Unit pixelIndex = 0; pixelIndex < decompressStruct.output_width * channels; pixelIndex += channels) {
      auto &pixel = picture->getPixel(pixelIndex / channels, line);

      pixel.channels.red = buffer[0][pixelIndex];
      pixel.channels.green = buffer[0][pixelIndex + 1];
      pixel.channels.blue = buffer[0][pixelIndex + 2];
      pixel.channels.alpha = (channels == 4) ? buffer[0][pixelIndex + 3] : 0xFF;
    }

    line++;
  }

  jpeg_finish_decompress(&decompressStruct);
  fclose(filePointer);

  return picture;
}
