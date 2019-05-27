#include "PictureHandler.h"

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

PictureHandler::PicutreTypeHandlers &PictureHandler::getHandlers() {
  return handlers;
}

void PictureHandler::write(std::string file, const Picture::Pointer &picture) {
  std::string extension = fs::extension(file);
  std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

  for (auto &handler : handlers) {
    if (handler->isFileTypeSupported(extension)) {
      handler->write(file, picture);
      return;
    }
  }

  throw PictureHandlerNotFound{extension};
}

Picture::Pointer PictureHandler::read(std::string file) {
  std::string extension = fs::extension(file);
  std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

  for (auto &handler : handlers) {
    if (handler->isFileTypeSupported(extension)) {
      return handler->read(file);
    }
  }

  throw PictureHandlerNotFound{extension};
}

void PictureHandler::addHandler(PictureWriterReader::Pointer &writerReader) {
  handlers.push_back(std::move(writerReader));
}
