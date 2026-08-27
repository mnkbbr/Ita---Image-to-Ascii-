cmake_minimum_required(VERSION 3.15)

project(Ita)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Ita 
    src/main.cpp
    src/GetMeanValue.cpp
    src/GetNum.cpp
    src/HelpMenu.cpp
)

target_include_directories(Ita PRIVATE include)