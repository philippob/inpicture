#ifndef INPICTURE_FILEREADEXCEPTION_H
#define INPICTURE_FILEREADEXCEPTION_H


#include "InputOutputException.h"

class FileReadException : public InputOutputException {
protected:
  std::string file{};

public:
  FileReadException(std::string file) : file(std::move(file)) {};

  FileReadException(std::string file, std::string message) : file(std::move(file)), InputOutputException(message) { }

  const std::string &getFile() const {
    return file;
  }

};


#endif //INPICTURE_FILEREADEXCEPTION_H
