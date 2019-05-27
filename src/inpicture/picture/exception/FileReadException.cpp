#include "FileReadException.h"

FileReadException::FileReadException(std::string file) : file(file) {}

const std::string &FileReadException::getFile() const {
  return file;
}
