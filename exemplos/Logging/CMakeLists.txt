cmake_minimum_required(VERSION 3.14)

project(Exemplo_Logger LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory( ./myApp )
add_subdirectory( ./myLogger )
