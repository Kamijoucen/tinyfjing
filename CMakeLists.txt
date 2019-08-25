cmake_minimum_required(VERSION 3.14)
project(tinyfjing)

set(CMAKE_CXX_STANDARD 14)
#set(GOOGLETEST_VERSION 1)

include_directories(Srouce)

add_subdirectory(gtest)

include_directories(gtest/include)

link_directories(gtest)

set(LIBRARIES gtest pthread)

add_executable(tinyfjing Srouce/TinyFJingSTL.h Srouce/compiler/TinyFJingLexicalAnalyzer.cpp Srouce/compiler/TinyFJingLexicalAnalyzer.h UnitTest/LexicalTest.h UnitTest/Main.cpp)

target_link_libraries(tinyfjing ${LIBRARIES})

