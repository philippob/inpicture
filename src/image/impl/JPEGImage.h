#ifndef INPICTURE_JPEGIMAGE_H
#define INPICTURE_JPEGIMAGE_H


#include "../Image.h"
#include "../exceptions/FileReadException.h"
#include "../exceptions/FileWriteException.h"
#include "../exceptions/InvalidFileException.h"

class JPEGImage : public Image {
public:

protected:
  PixelBuffer buffer;
  Unit width, height;

  void initialize(Unit width, Unit height);

public:
  JPEGImage() = default;

  JPEGImage(Unit width, Unit height);

  void load(const std::string &path) override;

  void save(const std::string &path) override;

  Unit getWidth() override;

  Unit getHeight() override;

  PixelBuffer &getPixelBuffer() override;

  Pixel &getPixel(Unit x, Unit y) override;

  void setPixel(Unit x, Unit y, const Pixel &pixel) override;

};


#endif //INPICTURE_JPEGIMAGE_H
