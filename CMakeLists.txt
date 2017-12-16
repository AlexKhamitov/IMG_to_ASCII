cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(IMG_to_ASCII LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp libaa.hpp)

#aalib
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(Aalib)
target_link_libraries(${PROJECT_NAME} PRIVATE aa::aa)

#imagemagick
include(FindPkgConfig)
pkg_check_modules(Magick++ REQUIRED IMPORTED_TARGET Magick++)
target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::Magick++)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

