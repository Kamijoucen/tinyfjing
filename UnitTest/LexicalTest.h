#ifndef TINYFJING_LEXICALTEST_H
#define TINYFJING_LEXICALTEST_H

#include "UnitTest.h"
#include "TinyFJingSTL.h"
#include "compiler/TinyFJingLexicalAnalyzer.h"
#include "gtest/gtest.h"

using namespace std;
using namespace tinyfjing;
using namespace tinyfjing::compiler;

TEST(Lexical, comment)
{
    auto code = T("-- b\n--a");
    CodeFile::Ptr ptr = CodeFile::Parse(code);
}

#endif //TINYFJING_LEXICALTEST_H
