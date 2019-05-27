#include "PictureHandlerNotFound.h"

PictureHandlerNotFound::PictureHandlerNotFound(std::string extension) : extension(extension) {

}


const std::string &PictureHandlerNotFound::getExtension() const {
  return extension;
}
