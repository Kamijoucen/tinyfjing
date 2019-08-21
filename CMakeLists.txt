cmake_minimum_required(VERSION 3.14)
project(tinyfjing)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(tinyfjing main.cpp TinyFJingSTL.h compiler/TinyFJingLexicalAnalyzer.cpp compiler/TinyFJingLexicalAnalyzer.h)
