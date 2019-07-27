cmake_minimum_required(VERSION 3.5)
project(TLMN CXX)
set(SRC src/TextMiningCompiler.cc
        )
find_package(Boost 1.55 REQUIRED COMPONENTS serialization)
include_directories(includes ${Boost_INCLUDE_DIR})
add_executable(TextMiningCompiler ${SRC})
target_link_libraries(TextMiningCompiler LINK_PUBLIC ${Boost_LIBRARIES} )
set(CMAKE_CPP_FLAGS "-g -02 -Wall -Werror -Wextra -std=c++17 -pedantic")
