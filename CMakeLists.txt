cmake_minimum_required(VERSION 3.14)
project(inpicture)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.65.1 REQUIRED program_options filesystem)
find_package(PNG 1.6.34 REQUIRED png)
find_package(JPEG 80 REQUIRED jpeg)

add_executable(inpicture src/main.cpp src/inpicture/InPicture.cpp src/inpicture/InPicture.h src/inpicture/picture/Picture.cpp src/inpicture/picture/Picture.h src/inpicture/picture/PictureHandler.cpp src/inpicture/picture/PictureHandler.h src/inpicture/picture/io/PictureWriterReader.h src/inpicture/picture/exception/PictureHandlerNotFound.cpp src/inpicture/picture/exception/PictureHandlerNotFound.h src/inpicture/picture/io/impl/PNGPictureWriterReader.cpp src/inpicture/picture/io/impl/PNGPictureWriterReader.h src/inpicture/picture/exception/FileReadException.cpp src/inpicture/picture/exception/FileReadException.h src/inpicture/picture/exception/InvalidFileException.cpp src/inpicture/picture/exception/InvalidFileException.h src/inpicture/picture/exception/FileWriteException.cpp src/inpicture/picture/exception/FileWriteException.h)
target_link_libraries(inpicture PNG::PNG JPEG::JPEG Boost::program_options Boost::filesystem)