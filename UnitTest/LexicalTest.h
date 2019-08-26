#ifndef TINYFJING_LEXICALTEST_H
#define TINYFJING_LEXICALTEST_H

#include "UnitTest.h"
#include "TinyFJingSTL.h"
#include "compiler/TinyFJingLexicalAnalyzer.h"
#include "gtest/gtest.h"

using namespace std;
using namespace tinyfjing;
using namespace tinyfjing::compiler;

TEST(aa, q)
{
    auto code = ReadAnsiFile(T("D:\\dev\\codework\\clion\\tinyfjing\\TestCaese\\hello.txt"));
    CodeFile::Ptr ptr = CodeFile::Parse(code);
}

#endif //TINYFJING_LEXICALTEST_H
