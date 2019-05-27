#ifndef INPICTURE_INVALIDFILEEXCEPTION_H
#define INPICTURE_INVALIDFILEEXCEPTION_H

#include <exception>
#include <string>

class InvalidFileException : public std::exception {
protected:
  const std::string file;
  const std::string format;

public:
  InvalidFileException(std::string file, std::string format);

  const std::string &getFile() const;

  const std::string &getFormat() const;

};


#endif //INPICTURE_INVALIDFILEEXCEPTION_H
