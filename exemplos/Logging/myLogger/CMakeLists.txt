cmake_minimum_required(VERSION 3.14)

project(myLogger LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(myLogger SHARED
  myLogger_global.h
  mylogger.cpp
  mylogger.h
)

target_link_libraries(myLogger PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(myLogger PRIVATE MYLOGGER_LIBRARY)
