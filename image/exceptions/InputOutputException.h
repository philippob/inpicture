#ifndef INPICTURE_INPUTOUTPUTEXCEPTION_H
#define INPICTURE_INPUTOUTPUTEXCEPTION_H


#include <string>
#include <exception>

class InputOutputException : public std::exception {
protected:
  const std::string message;

public:
  InputOutputException() = default;

  InputOutputException(std::string message) : message(std::move(message)) { }

  const std::string &getMessage() const {
    return message;
  }

  const char *what() const noexcept override {
    return message.c_str();
  }

};


#endif //INPICTURE_INPUTOUTPUTEXCEPTION_H
