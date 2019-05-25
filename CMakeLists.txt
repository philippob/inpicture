cmake_minimum_required(VERSION 3.14)
project(inpicture)

set(CMAKE_CXX_STANDARD 17)

find_package(PNG 1.6.34 REQUIRED png)
find_package(JPEG 80 REQUIRED jpeg)

add_executable(inpicture src/main.cpp src/image/Image.h src/embeder/Embeder.h src/image/impl/PNGImage.cpp src/image/impl/PNGImage.h src/image/exceptions/InputOutputException.h src/image/exceptions/FileReadException.h src/image/exceptions/FileWriteException.h src/image/exceptions/InvalidFileException.h src/image/impl/JPEGImage.cpp src/image/impl/JPEGImage.h)
target_link_libraries(inpicture PNG::PNG JPEG::JPEG)