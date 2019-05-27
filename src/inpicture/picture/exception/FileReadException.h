#ifndef INPICTURE_FILEREADEXCEPTION_H
#define INPICTURE_FILEREADEXCEPTION_H

#include <exception>
#include <string>

class FileReadException : public std::exception {
protected:
  const std::string file;

public:
  explicit FileReadException(std::string file);

  const std::string &getFile() const;

};

#endif //INPICTURE_FILEREADEXCEPTION_H
