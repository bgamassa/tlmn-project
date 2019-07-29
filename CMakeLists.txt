cmake_minimum_required(VERSION 3.5)
project(TLMN CXX)
set(SRC1 src/TextMiningCompiler.cc
        )
set (SRC2 src/TextMiningApp.cc
        )
find_package(Boost 1.55 REQUIRED COMPONENTS serialization)
include_directories(includes ${Boost_INCLUDE_DIR})
add_executable(TextMiningCompiler ${SRC1})
add_executable(TextMiningApp ${SRC2})
target_link_libraries(TextMiningCompiler LINK_PUBLIC ${Boost_LIBRARIES} )
target_link_libraries(TextMiningApp LINK_PUBLIC ${Boost_LIBRARIES} )
set(CMAKE_CPP_FLAGS "-O3 -02 -Wall -Werror -Wextra -std=c++17 -pedantic")

set(doxyfile_in ../doc/Doxyfile)
set(doxyfile ../doc)
add_custom_target(doc
        COMMAND doxygen ${doxyfile_in}
        WORKING_DIRECTORY ../doc)


