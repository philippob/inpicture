#ifndef INPICTURE_PICTURE_H
#define INPICTURE_PICTURE_H

#include <vector>
#include <memory>

class Picture {
public:
  using Byte = unsigned char;

  using Unit = unsigned long;

  using Pixel = union {
    struct {
      Byte red, green, blue, alpha;
    } channels;

    Byte values[4];

    unsigned int color;

  };

  using PixelBuffer = std::vector<Pixel>;

  using Pointer = std::unique_ptr<Picture>;

protected:
  PixelBuffer pixelBuffer{};

  Unit width{}, height{};

public:
  Picture() = default;

  Picture(Unit width, Unit height);

  Unit getWidth() const;

  Unit getHeight() const;

  Unit getSize() const;

  virtual void initialize(Unit width, Unit height);

  virtual void resize(Unit newWidth, Unit newHeight);

  virtual PixelBuffer &getPixelBuffer();

  virtual void setPixelBuffer(const PixelBuffer &pixelBuffer);

  virtual Pixel &getPixel(Unit index);

  virtual Pixel &getPixel(Unit x, Unit y);

  virtual void setPixel(Unit index, const Pixel &pixel);

  virtual void setPixel(Unit x, Unit y, const Pixel &pixel);

};

#endif //INPICTURE_PICTURE_H
