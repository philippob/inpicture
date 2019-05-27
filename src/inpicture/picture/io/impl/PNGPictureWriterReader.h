#ifndef INPICTURE_PNGPICTUREWRITERREADER_H
#define INPICTURE_PNGPICTUREWRITERREADER_H

#include "../PictureWriterReader.h"
#include "../../exception/FileReadException.h"
#include "../../exception/FileWriteException.h"
#include "../../exception/InvalidFileException.h"

class PNGPictureWriterReader : public PictureWriterReader {
public:
  bool isFileTypeSupported(std::string extension) const override;

  void write(std::string file, const Picture::Pointer &picture) override;

  Picture::Pointer read(std::string file) override;

};

#endif //INPICTURE_PNGPICTUREWRITERREADER_H
