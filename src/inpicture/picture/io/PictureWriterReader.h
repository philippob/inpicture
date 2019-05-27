#ifndef INPICTURE_PICTUREWRITERREADER_H
#define INPICTURE_PICTUREWRITERREADER_H

#include "../Picture.h"

class PictureWriterReader {
public:
  using Pointer = std::unique_ptr<PictureWriterReader>;

  virtual bool isFileTypeSupported(std::string extension) const = 0;

  virtual void write(std::string file, const Picture::Pointer &picture) = 0;

  virtual Picture::Pointer read(std::string file) = 0;

};


#endif //INPICTURE_PICTUREWRITERREADER_H
