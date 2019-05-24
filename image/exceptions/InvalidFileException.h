#ifndef INPICTURE_INVALIDFILEEXCEPTION_H
#define INPICTURE_INVALIDFILEEXCEPTION_H


#include <exception>
#include <string>

class InvalidFileException : public std::exception {
protected:
  const std::string file;
  const std::string format;
  const std::string message;

public:
  InvalidFileException(std::string file, std::string format) : file(std::move(file)), format(std::move(format)) {}

  InvalidFileException(std::string file, std::string format, std::string message) : file(std::move(file)),
                                                                                    format(std::move(format)),
                                                                                    message(std::move(message)) {}

  const std::string &getMessage() const {
    return message;
  }

  const std::string &getFile() const {
    return file;
  }

  const std::string &getFormat() const {
    return format;
  }

  const char *what() const noexcept override {
    return message.c_str();
  }

};


#endif //INPICTURE_INVALIDFILEEXCEPTION_H
