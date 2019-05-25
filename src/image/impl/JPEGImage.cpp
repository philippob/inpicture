#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

#include "JPEGImage.h"

JPEGImage::JPEGImage(Image::Unit width, Image::Unit height) {
  initialize(width, height);
}

void JPEGImage::load(const std::string &path) {
  //TODO: implementation
}

void JPEGImage::save(const std::string &path) {
  //TODO: implementation
}

Image::Unit JPEGImage::getWidth() {
  return width;
}

Image::Unit JPEGImage::getHeight() {
  return height;
}

Image::PixelBuffer &JPEGImage::getPixelBuffer() {
  return buffer;
}

Image::Pixel &JPEGImage::getPixel(Image::Unit x, Image::Unit y) {
  return buffer[y * width + x];
}

void JPEGImage::setPixel(Image::Unit x, Image::Unit y, const Image::Pixel &pixel) {
  buffer[y * width + x] = pixel;
}

void JPEGImage::initialize(Image::Unit width, Image::Unit height) {
  this->width = width;
  this->height = height;
  buffer.resize(width * height);
}
