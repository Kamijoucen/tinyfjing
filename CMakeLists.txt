cmake_minimum_required(VERSION 3.8)
project(tinyfjing)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(gtest Srouce)

include_directories(gtest/include Srouce)

set(LIBRARIES gtest pthread)

link_directories(gtest)

add_executable(tinyfjing UnitTest/Main.cpp Srouce/TinyFJingSTL.h Srouce/compiler/TinyFJingLexicalAnalyzer.cpp Srouce/compiler/TinyFJingLexicalAnalyzer.h UnitTest/LexicalTest.h UnitTest/UnitTest.h)

target_link_libraries(tinyfjing ${LIBRARIES})

