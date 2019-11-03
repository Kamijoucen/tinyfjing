cmake_minimum_required(VERSION 3.8)
project(tinyfjing)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -Wall")

#add_definitions(-O3)
add_definitions(-Wall)

add_subdirectory(gtest Srouce)

include_directories(gtest/include Srouce)

set(LIBRARIES gtest pthread)

link_directories(gtest)

add_executable(tinyfjing UnitTest/Main.cpp Srouce/TinyFJingSTL.h Srouce/compiler/TinyFJingLexical.cpp Srouce/compiler/TinyFJingLexical.h UnitTest/LexicalTest.h UnitTest/UnitTest.h Srouce/compiler/TinyFJingParser.cpp Srouce/compiler/TinyFJingParser.h Srouce/ast/TinyFJingAST.cpp Srouce/ast/TinyFJingAST.h Srouce/TinyFJingMessage.h Srouce/ast/TinyFJingValue.cpp Srouce/ast/TinyFJingValue.h)

target_link_libraries(tinyfjing ${LIBRARIES})

