#ifndef TINYFJING_TINYFJINGLEXICALANALYZER_H
#define TINYFJING_TINYFJINGLEXICALANALYZER_H

#include "TinyFJingSTL.h"

namespace tinyfjing {

    namespace compiler {

        enum class CodeTokenType {

            String,         // 字符串
            Integer,        // 整型数字
            Float,          // 浮点数
            Identifier,     // 标识符

            //----------------------------------------

            Var,            // var
            Global,         // global
            False,          // false
            True,           // true
            Return,         // return
            Break,          // break
            Continue,       // continue
            If,             // if
            Else,           // else
            While,          // while
            Do,             // do

            //----------------------------------------

            LeftParen,      // (
            RightParen,     // )
            Comma,          // ,
            Colon,          // :
            Concat,         // &
            Add,            // +
            Sub,            // -
            Mul,            // *
            Div,            // /
            IntDiv,         // \ (can apply on floats)
            Mod,            // %
            LT,             // <
            GT,             // >
            LE,             // <=
            GE,             // >=
            EQ,             // =
            NE,             // <>
            And,            // and
            Or,             // or
            Not,            // not

            //----------------------------------------

            Comment,        // -- xxx
            Unknown,

        };

        struct CodeToken {
            typedef std::vector<CodeToken> List;

            CodeTokenType tokenType = CodeTokenType::Unknown;
            long row = -1;
            long column = -1;
            string_t value;

            CodeToken() = default;

            CodeToken(CodeTokenType tokenType, long row, long column, string_t value);
        };

        inline CodeToken::CodeToken(CodeTokenType tokenType, long row, long column, string_t value)
                : tokenType(tokenType), row(row), column(column), value(std::move(value)) {}


        struct CodeFile {
            typedef std::shared_ptr<CodeFile> Ptr;
            typedef std::vector<Ptr> List;

            CodeToken::List tokens;

            static CodeFile::Ptr Parse(const string_t &code);
        };


    }

}


#endif //TINYFJING_TINYFJINGLEXICALANALYZER_H
