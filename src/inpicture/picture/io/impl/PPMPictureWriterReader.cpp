#include "PPMPictureWriterReader.h"
#include "../../Picture.h"

#include <fstream>
#include <string>

bool PPMPictureWriterReader::isFileTypeSupported(std::string extension) const {
  return extension == "ppm";
}

void PPMPictureWriterReader::write(std::string file, const Picture::Pointer &picture) {
  std::ofstream outputStream{file};
  if (!outputStream) {
    throw FileWriteException{file};
  }

  outputStream << "P3" << std::endl;
  outputStream << picture->getWidth() << " " << picture->getHeight() << std::endl;
  outputStream << 0xFF << std::endl;

  for (Picture::Unit y = 0; y < picture->getHeight(); y++)
    for (Picture::Unit x = 0; x < picture->getWidth(); x++)
      outputStream << static_cast<unsigned int>(picture->getPixel(x, y).channels.red) << " "
        << static_cast<unsigned int>(picture->getPixel(x, y).channels.green) << " "
        << static_cast<unsigned int>(picture->getPixel(x, y).channels.blue)
        << std::endl;

  outputStream.close();
}

Picture::Pointer PPMPictureWriterReader::read(std::string file) {
  std::ifstream inputStream{file};
  if (!inputStream) {
    throw FileReadException{file};
  }

  std::string pictureType;
  inputStream >> pictureType;

  if (pictureType != "P3") {
    inputStream.close();
    throw InvalidFileException{file, "PPM/P3"};
  }

  auto picture = std::make_unique<Picture>();

  Picture::Unit width = 0, height = 0;
  inputStream >> width >> height;

  picture->initialize(width, height);

  for (Picture::Unit y = 0; y < height; y++) {
    for (Picture::Unit x = 0; x < width; x++) {
      auto &pixel = picture->getPixel(x, y);
      inputStream >> pixel.channels.red >> pixel.channels.green >> pixel.channels.blue;
    }
  }

  return picture;
}
