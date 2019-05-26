#ifndef INPICTURE_PICTURELOADER_H
#define INPICTURE_PICTURELOADER_H

#include "../Picture.h"

class PictureLoader {
public:
  virtual Picture::Pointer load(std::string file) = 0;

};

#endif //INPICTURE_PICTURELOADER_H
