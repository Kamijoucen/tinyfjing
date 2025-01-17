/*
 * @Author: kamijoucen
 * @Date: 2019-11-09 16:26:50
 * @LastEditTime: 2019-11-09 19:38:43
 * @LastEditors: kamijoucen
 * @Description: 
 * @FilePath: \tinyfjing\Srouce\compiler\TinyFJingParser.h
 * @
 */

#ifndef TINYFJING_TINYFJINGPARSER_H
#define TINYFJING_TINYFJINGPARSER_H

#include "TinyFJingSTL.h"
#include "TinyFJingLexical.h"
#include "ast/TinyFJingAST.h"

namespace tinyfjing
{

namespace compiler
{

class Module
{
public:
    typedef std::shared_ptr<Module> Ptr;
    typedef std::weak_ptr<Module> WeakPtr;
    typedef std::vector<ast::UsingStatementAst::Ptr> UsingList;
    typedef std::vector<ast::BaseAst::Ptr> CodesList;

    string_t name; // 模块名
    UsingList usings;
    CodesList codes;

    static Module::Ptr Parse(const CodeFile::Ptr &ptr);
};

struct Parser
{

    typedef std::vector<CodeToken>::iterator Iterator;

    // 语句
    struct Statement
    {
        static ast::UsingStatementAst::Ptr
        ParseUsingStatement(Parser::Iterator &reading, Parser::Iterator &end);

        static ast::IfStatementAst::Ptr
        ParseIfStatement(Parser::Iterator &reading, Parser::Iterator &end);
    };

    // 表达式，出现在语句中
    struct Expression
    {
        static ast::BaseAst::Ptr
        ParseExpression(Parser::Iterator &reading, Parser::Iterator &end);

        static ast::BaseAst::Ptr
        ParsePrimaryExpression(Parser::Iterator &reading, Parser::Iterator &end);

        static ast::BaseAst::Ptr
        ParseNumberExpression(Parser::Iterator &reading, Parser::Iterator &end);

        static ast::BaseAst::Ptr
        ParseBooleanExpression(Parser::Iterator &reading, Parser::Iterator &end);

        static ast::BaseAst::Ptr
        ParseParenExpression(Parser::Iterator &reading, Parser::Iterator &end);

        static ast::BaseAst::Ptr
        ParseIdentifierExpression(Parser::Iterator &reading, Parser::Iterator &end);

        // 单目运算表达式
        static ast::BaseAst::Ptr
        ParseUnaryExpression(Parser::Iterator &reading, Parser::Iterator &end);

        static ast::BaseAst::Ptr
        ParseBinaryOpRHS(Parser::Iterator &reading, Parser::Iterator &end, ast::BaseAst::Ptr lhs, int precedence);
    };
};
} // namespace compiler
} // namespace tinyfjing

#endif //TINYFJING_TINYFJINGPARSER_H
