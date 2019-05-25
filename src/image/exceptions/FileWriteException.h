#ifndef INPICTURE_FILEWRITEEXCEPTION_H
#define INPICTURE_FILEWRITEEXCEPTION_H


#include "InputOutputException.h"

class FileWriteException : public InputOutputException {
protected:
  std::string file{};

public:
  FileWriteException(std::string file) : file(std::move(file)) {};

  FileWriteException(std::string file, std::string message) : file(std::move(file)), InputOutputException(message) { }

  const std::string &getFile() const {
    return file;
  }

};


#endif //INPICTURE_FILEWRITEEXCEPTION_H
