cmake_minimum_required(VERSION 3.5)
project(TLMN CXX)
set(SRC src/TextMiningCompiler.cc
        )
include_directories(includes)
add_executable(TextMiningCompiler ${SRC})
set(CMAKE_CPP_FLAGS "-g -02 -Wall -Werror -Wextra -std=c++17 -pedantic")
