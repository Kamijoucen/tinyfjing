cmake_minimum_required(VERSION 3.14)
project(tinyfjing)

set(CMAKE_CXX_STANDARD 11)


add_subdirectory(gtest Srouce)

include_directories(gtest/include Srouce)

link_directories(gtest)

set(LIBRARIES gtest pthread)

include(CTest)

add_executable(tinyfjing UnitTest/Main.cpp Srouce/TinyFJingSTL.h Srouce/compiler/TinyFJingLexicalAnalyzer.cpp Srouce/compiler/TinyFJingLexicalAnalyzer.h UnitTest/LexicalTest.h UnitTest/UnitTest.h)

target_link_libraries(tinyfjing ${LIBRARIES})

