#ifndef INPICTURE_PICTUREHANDLERNOTFOUND_H
#define INPICTURE_PICTUREHANDLERNOTFOUND_H

#include <exception>
#include <string>

class PictureHandlerNotFound : public std::exception {
protected:
  const std::string extension;

public:
  explicit PictureHandlerNotFound(std::string extension);

  const std::string &getExtension() const;

};

#endif //INPICTURE_PICTUREHANDLERNOTFOUND_H
