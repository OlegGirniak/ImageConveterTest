cmake_minimum_required(VERSION 3.10)

project(ImageConverter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/includes)

find_package(PNG REQUIRED)

set(SOURCE_FILES
    src/main.cpp
    src/BMPImageConverter.cpp
    src/PNGImageConverter.cpp
)

add_executable(ImageConverter ${SOURCE_FILES})

target_link_libraries(ImageConverter PRIVATE PNG::PNG)
target_include_directories(ImageConverter PRIVATE ${PNG_INCLUDE_DIRS})

