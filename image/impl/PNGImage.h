#ifndef INPICTURE_PNGIMAGE_H
#define INPICTURE_PNGIMAGE_H


#include "../Image.h"
#include "../exceptions/FileReadException.h"
#include "../exceptions/FileWriteException.h"
#include "../exceptions/InvalidFileException.h"

class PNGImage : public Image {
protected:
  PixelBuffer buffer{};
  Unit width{0}, height{0};

private:
  void initialize(Unit width, Unit height);

public:
  PNGImage() = default;

  PNGImage(Unit width, Unit height);

  ~PNGImage() = default;

  void load(const std::string &path) override;

  void save(const std::string &path) override;

  Unit getWidth() override;

  Unit getHeight() override;

  PixelBuffer &getPixelBuffer() override;

  Pixel &getPixel(Unit x, Unit y) override;

  void setPixel(Unit x, Unit y, const Pixel &pixel) override;

};


#endif //INPICTURE_PNGIMAGE_H
