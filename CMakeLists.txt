cmake_minimum_required(VERSION 3.14)
project(inpicture)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.65.1 REQUIRED program_options)
find_package(PNG 1.6.34 REQUIRED png)
find_package(JPEG 80 REQUIRED jpeg)

add_executable(inpicture src/main.cpp src/inpicture/InPicture.cpp src/inpicture/InPicture.h src/inpicture/picture/Picture.cpp src/inpicture/picture/Picture.h src/inpicture/picture/io/PictureLoader.h src/inpicture/picture/io/PictureSaver.h)
target_link_libraries(inpicture PNG::PNG JPEG::JPEG Boost::program_options)