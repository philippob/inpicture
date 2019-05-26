#ifndef INPICTURE_PICTURESAVER_H
#define INPICTURE_PICTURESAVER_H

#include "../Picture.h"

class PictureSaver {
public:
  virtual void save(std::string file, const Picture::Pointer &picture) = 0;

};

#endif //INPICTURE_PICTURESAVER_H
