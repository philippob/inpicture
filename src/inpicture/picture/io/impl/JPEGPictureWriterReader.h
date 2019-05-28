#ifndef INPICTURE_JPEGPICTUREWRITERREADER_H
#define INPICTURE_JPEGPICTUREWRITERREADER_H

#include "../PictureWriterReader.h"
#include "../../exception/FileReadException.h"
#include "../../exception/FileWriteException.h"
#include "../../exception/InvalidFileException.h"

class JPEGPictureWriterReader : public PictureWriterReader {
public:
  bool isFileTypeSupported(std::string extension) const override;

  void write(std::string file, const Picture::Pointer &picture) override;

  Picture::Pointer read(std::string file) override;

};

#endif //INPICTURE_JPEGPICTUREWRITERREADER_H
