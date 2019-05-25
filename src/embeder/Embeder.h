#ifndef INPICTURE_EMBEDER_H
#define INPICTURE_EMBEDER_H


#include <memory>

#include "../image/Image.h"

class Embeder {
public:
  using Byte = unsigned char;

  virtual void embed(std::shared_ptr<Image> image, const std::vector<Byte> &data) = 0;

};


#endif //INPICTURE_EMBEDER_H
