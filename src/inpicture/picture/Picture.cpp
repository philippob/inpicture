#include "Picture.h"

Picture::Picture(Picture::Unit width, Picture::Unit height) {
  initialize(width, height);
}

Picture::Unit Picture::getWidth() const {
  return width;
}

Picture::Unit Picture::getHeight() const {
  return height;
}

Picture::Unit Picture::getSize() const {
  return width * height;
}

void Picture::initialize(Picture::Unit width, Picture::Unit height) {
  this->width = width;
  this->height = height;
  pixelBuffer.resize(width * height);
}

void Picture::resize(Picture::Unit newWidth, Picture::Unit newHeight) {
  PixelBuffer newBuffer{};
  newBuffer.resize(newWidth * newHeight);

  for (Unit y = 0; y < (height > newHeight ? newHeight : height); y++)
    for (Unit x = 0; x < (width > newWidth ? newWidth : width); x++)
      newBuffer[y * newWidth + x] = pixelBuffer[y * width + x];

  pixelBuffer = newBuffer;
  width = newWidth;
  height = newHeight;
}

Picture::PixelBuffer &Picture::getPixelBuffer() {
  return pixelBuffer;
}

void Picture::setPixelBuffer(const Picture::PixelBuffer &pixelBuffer) {
  this->pixelBuffer = pixelBuffer;
}

Picture::Pixel &Picture::getPixel(Picture::Unit index) {
  return pixelBuffer[index];
}

Picture::Pixel &Picture::getPixel(Picture::Unit x, Picture::Unit y) {
  return pixelBuffer[y * width + x];
}

void Picture::setPixel(Picture::Unit index, const Picture::Pixel &pixel) {
  pixelBuffer[index] = pixel;
}

void Picture::setPixel(Picture::Unit x, Picture::Unit y, const Picture::Pixel &pixel) {
  pixelBuffer[y * width + x] = pixel;
}
