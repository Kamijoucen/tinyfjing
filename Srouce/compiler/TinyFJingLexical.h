/*
 * @Author: kamijoucen
 * @Date: 2019-10-31 00:05:53
 * @LastEditTime: 2019-11-09 19:38:32
 * @LastEditors: kamijoucen
 * @Description: 
 * @FilePath: \tinyfjing\Srouce\compiler\TinyFJingLexical.h
 * @
 */
#ifndef TINYFJING_TINYFJINGLEXICAL_H
#define TINYFJING_TINYFJINGLEXICAL_H

#include "TinyFJingSTL.h"

namespace tinyfjing
{

namespace compiler
{

enum class CodeTokenType
{

    String,     // 字符串
    Integer,    // 整型数字
    Float,      // 浮点数
    Double,     // 双精度浮点
    Identifier, // 标识符

    //----------------------------------------

    Var,      // var
    Def,      // def
    False,    // false
    True,     // true
    Return,   // return
    Break,    // break
    Continue, // continue
    If,       // if
    Else,     // else
    While,    // while
    Do,       // do
    For,      // for
    End,      // end
    Module,   // module
    Using,    // using

    //----------------------------------------

    LeftParen,  // (
    RightParen, // )
    Comma,      // ,
    Colon,      // :
    Concat,     // &
    Add,        // +
    Sub,        // -
    Mul,        // *
    Div,        // /
    IntDiv,     // \ (can apply on floats)
    Mod,        // %
    LT,         // <
    GT,         // >
    LE,         // <=
    GE,         // >=
    Assign,     // =
    EQ,         // ==
    NE,         // <> or !=
    And,        // and
    Or,         // or
    Not,        // not

    //----------------------------------------

    Comment, // -- xxx
    Unknown,

};

struct CodeToken
{
    typedef std::vector<CodeToken> List;

    CodeTokenType tokenType = CodeTokenType::Unknown;
    long row = -1;
    long column = -1;
    string_t str;

    union {
        int int_value;
        float float_value;
        double double_value;
    } data;

    CodeToken() = default;

    CodeToken(CodeTokenType tokenType, long row, long column, string_t str);
};

struct CodeFile
{
    typedef std::shared_ptr<CodeFile> Ptr;
    typedef std::vector<Ptr> List;

    CodeToken::List tokens;

    static CodeFile::Ptr Parse(const string_t &code);
};

} // namespace compiler

} // namespace tinyfjing

#endif //TINYFJING_TINYFJINGLEXICAL_H
