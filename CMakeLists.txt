cmake_minimum_required(VERSION 3.14)
project(inpicture)

set(CMAKE_CXX_STANDARD 17)

find_package(PNG 1.6.34 REQUIRED png)
find_package(JPEG 80 REQUIRED jpeg)

add_executable(inpicture main.cpp image/Image.h embeder/Embeder.h image/impl/PNGImage.cpp image/impl/PNGImage.h image/exceptions/InputOutputException.h image/exceptions/FileReadException.h image/exceptions/FileWriteException.h image/exceptions/InvalidFileException.h image/impl/JPEGImage.cpp image/impl/JPEGImage.h)
target_link_libraries(inpicture PNG::PNG JPEG::JPEG)