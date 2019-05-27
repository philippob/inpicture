#include "FileWriteException.h"

FileWriteException::FileWriteException(std::string file) : file(file) {

}

const std::string &FileWriteException::getFile() const {
  return file;
}
