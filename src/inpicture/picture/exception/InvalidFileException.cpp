#include "InvalidFileException.h"

InvalidFileException::InvalidFileException(std::string file, std::string format) : file(file), format(format) {}

const std::string &InvalidFileException::getFile() const {
  return file;
}

const std::string &InvalidFileException::getFormat() const {
  return format;
}
