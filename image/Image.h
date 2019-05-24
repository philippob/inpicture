#ifndef INPICTURE_IMAGE_H
#define INPICTURE_IMAGE_H


#include <vector>
#include <string>

class Image {
public:
  using Unit = unsigned long;

  using Byte = unsigned char;

  using Pixel = union {
    struct {
      Byte red, green, blue, alpha;
    } values;

    unsigned int color;
  };

  using PixelBuffer = std::vector<Pixel>;

public:
  virtual void load(const std::string &path) = 0;

  virtual void save(const std::string &path) = 0;

  virtual Unit getWidth() = 0;

  virtual Unit getHeight() = 0;

  virtual PixelBuffer& getPixelBuffer() = 0;

  virtual Pixel &getPixel(Unit x, Unit y) = 0;

  virtual void setPixel(Unit x, Unit y, const Pixel& pixel) = 0;

};


#endif //INPICTURE_IMAGE_H
