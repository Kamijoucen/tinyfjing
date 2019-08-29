#ifndef TINYFJING_LEXICALTEST_H
#define TINYFJING_LEXICALTEST_H

#include <compiler/TinyFJingLexicalAnalyzer.h>
#include "UnitTest.h"
#include "TinyFJingSTL.h"
#include "compiler/TinyFJingLexicalAnalyzer.h"
#include "gtest/gtest.h"

using namespace std;
using namespace tinyfjing;
using namespace tinyfjing::compiler;

TEST(Lexical, identifier)
{
    auto code = T("name true\n\tadd  var");
    CodeFile::Ptr ptr = CodeFile::Parse(code);

    ASSERT_EQ(ptr->tokens.size(), 4);

    ASSERT_EQ(ptr->tokens[0].str, "name");
    ASSERT_EQ(ptr->tokens[0].tokenType, CodeTokenType::Identifier);

    ASSERT_EQ(ptr->tokens[1].str, "true");
    ASSERT_EQ(ptr->tokens[1].tokenType, CodeTokenType::True);

    ASSERT_EQ(ptr->tokens[2].str, "add");
    ASSERT_EQ(ptr->tokens[2].tokenType, CodeTokenType::Identifier);

    ASSERT_EQ(ptr->tokens[3].str, "var");
    ASSERT_EQ(ptr->tokens[3].tokenType, CodeTokenType::Var);
}

TEST(Lexical, number)
{
    auto code = T("30\n12.4 3");
    CodeFile::Ptr ptr = CodeFile::Parse(code);

    ASSERT_EQ(ptr->tokens.size(), 3);

    ASSERT_EQ(ptr->tokens[0].str, "30");
    ASSERT_EQ(ptr->tokens[0].tokenType, CodeTokenType::Integer);
    ASSERT_EQ(ptr->tokens[0].data.int_value, 30);

    ASSERT_EQ(ptr->tokens[1].str, "12.4");
    ASSERT_EQ(ptr->tokens[1].tokenType, CodeTokenType::Float);
    ASSERT_FLOAT_EQ(ptr->tokens[1].data.float_value, 12.4);

    ASSERT_EQ(ptr->tokens[2].str, "3");
    ASSERT_EQ(ptr->tokens[2].tokenType, CodeTokenType::Integer);
    ASSERT_EQ(ptr->tokens[2].data.int_value, 3);
}

TEST(Lexical, string)
{
    auto code = T("a1 \"fjing\" sfc\n55\"lisicen\"");
    CodeFile::Ptr ptr = CodeFile::Parse(code);

    ASSERT_EQ(ptr->tokens.size(), 5);

    ASSERT_EQ(ptr->tokens[0].str, "a1");
    ASSERT_EQ(ptr->tokens[0].tokenType, CodeTokenType::Identifier);

    ASSERT_EQ(ptr->tokens[1].str, "fjing");
    ASSERT_EQ(ptr->tokens[1].tokenType, CodeTokenType::String);

    ASSERT_EQ(ptr->tokens[2].str, "sfc");
    ASSERT_EQ(ptr->tokens[2].tokenType, CodeTokenType::Identifier);

    ASSERT_EQ(ptr->tokens[3].str, "55");
    ASSERT_EQ(ptr->tokens[3].tokenType, CodeTokenType::Integer);
    ASSERT_EQ(ptr->tokens[3].data.int_value, 55);

    ASSERT_EQ(ptr->tokens[4].str, "lisicen");
    ASSERT_EQ(ptr->tokens[4].tokenType, CodeTokenType::String);

}

TEST(a, a)
{
    auto code = T("5\"a\"");
    CodeFile::Ptr ptr = CodeFile::Parse(code);
    ASSERT_EQ(ptr->tokens.size(), 2);
}

#endif //TINYFJING_LEXICALTEST_H
