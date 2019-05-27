#ifndef INPICTURE_FILEWRITEEXCEPTION_H
#define INPICTURE_FILEWRITEEXCEPTION_H

#include <exception>
#include <string>

class FileWriteException : public std::exception {
protected:
  const std::string file;

public:
  explicit FileWriteException(std::string file);

  const std::string &getFile() const;

};

#endif //INPICTURE_FILEWRITEEXCEPTION_H
