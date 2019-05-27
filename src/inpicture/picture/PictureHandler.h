#ifndef INPICTURE_PICTUREHANDLER_H
#define INPICTURE_PICTUREHANDLER_H

#include <vector>

#include "Picture.h"
#include "io/PictureWriterReader.h"
#include "exception/PictureHandlerNotFound.h"

class PictureHandler : public PictureWriterReader {
public:
  using PicutreTypeHandlers = std::vector<PictureWriterReader::Pointer>;

protected:
  PicutreTypeHandlers handlers{};

public:
  PicutreTypeHandlers &getHandlers();

  void addHandler(PictureWriterReader::Pointer &writerReader);

  void write(std::string file, const Picture::Pointer &picture) override;

  Picture::Pointer read(std::string file) override;

};

#endif //INPICTURE_PICTUREHANDLER_H
