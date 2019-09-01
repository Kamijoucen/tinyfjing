#include "TinyFJingLexicalAnalyzer.h"

namespace tinyfjing {

    namespace compiler {

        CodeFile::Ptr CodeFile::Parse(const string_t &code) {
            auto file = std::make_shared<CodeFile>();

            enum class State {
                Begin,
                InPreComment,
                InComment,
                InInteger,
                InFloat,
                InString,
                InIdentifier,
            };

            // 正在读的指针位置
            const char_t *reading = code.c_str();
            // token开始的指针位置
            const char_t *begin = nullptr;

            // begin - reading = token长度
            // begin + token长度 = token结束位置

            int row = 1;
            int column = 1;

            int beginColumn = 0;

            State state = State::Begin;

            auto NextChar = [&]() {
                if (*reading == T('\n')) {
                    column = 1;
                    row += 1;
                } else {
                    column++;
                }
            };

            auto AddToken = [&](int length, CodeTokenType type) {
                if (type == CodeTokenType::Comment) {
                    return;
                }
                auto tokenBeing = begin ? begin : reading;
                string_t strValue(tokenBeing, tokenBeing + length);

                if (type == CodeTokenType::Identifier) {
                    type =
                            strValue == T("var") ? CodeTokenType::Var :
                            strValue == T("def") ? CodeTokenType::Def :
                            strValue == T("true") ? CodeTokenType::True :
                            strValue == T("false") ? CodeTokenType::False :
                            strValue == T("return") ? CodeTokenType::Return :
                            strValue == T("break") ? CodeTokenType::Break :
                            strValue == T("continue") ? CodeTokenType::Continue :
                            strValue == T("if") ? CodeTokenType::If :
                            strValue == T("else") ? CodeTokenType::Else :
                            strValue == T("while") ? CodeTokenType::While :
                            strValue == T("do") ? CodeTokenType::Do :
                            strValue == T("and") ? CodeTokenType::And :
                            strValue == T("or") ? CodeTokenType::Or :
                            strValue == T("not") ? CodeTokenType::Not :
                            strValue == T("for") ? CodeTokenType::For :
                            CodeTokenType::Identifier;
                }


                CodeToken token(type, row, beginColumn ? beginColumn : column, strValue);
                switch (type) {
                    case CodeTokenType::Integer:
                        token.data.int_value = std::stoi(strValue);
                        break;
                    case CodeTokenType::Float:
                        token.data.float_value = std::stof(strValue);
                        break;
//                    case CodeTokenType::Double:
//                        token.data.double_value = std::stod(strValue);
//                        break;
                    default:
                        break;
                }
                file->tokens.push_back(std::move(token));
            };

            while (auto c = *reading) {
                switch (state) {
                    case State::Begin:
                        switch (c) {
                            case T('+'):
                                AddToken(1, CodeTokenType::Add);
                                break;
                            case T('-'):
                                begin = reading;
                                beginColumn = column;
                                state = State::InPreComment;
                                break;
                            case T(','):
                                AddToken(1, CodeTokenType::Comma);
                                break;
                            case T('*'):
                                AddToken(1, CodeTokenType::Mul);
                                break;
                            case T('/'):
                                AddToken(1, CodeTokenType::Div);
                                break;
                            case T('"'):
                                begin = reading;
                                beginColumn = column;
                                state = State::InString;
                                break;
                            case T('('):
                                AddToken(1, CodeTokenType::LeftParen);
                                break;
                            case T(')'):
                                AddToken(1, CodeTokenType::RightParen);
                                break;
                            case T(' '):
                            case T('\t'):
                            case T('\r'):
                                break;
                            case T('\n'):
                                break;
                            default:
                                if (std::isalpha(c) || c == T('_')) {
                                    begin = reading;
                                    beginColumn = column;
                                    state = State::InIdentifier;
                                } else if (std::isdigit(c)) {
                                    begin = reading;
                                    beginColumn = column;
                                    state = State::InInteger;
                                } else {
                                    // todo throws exception
                                }
                        }
                        break;
                    case State::InInteger:

                        if (std::isdigit(c)) {
                            // 不做处理
                        } else if (c == T('.') && std::isdigit(reading[1])) {
                            state = State::InFloat;
                        } else {
                            AddToken(reading - begin, CodeTokenType::Integer);
                            state = State::Begin;
                            beginColumn = 0;
                            reading--;
                            begin = nullptr;
                        }
                        break;
                    case State::InFloat:
                        if (std::isdigit(c)) {
                            // 不做处理
                        } else {
                            AddToken(reading - begin, CodeTokenType::Float);
                            state = State::Begin;
                            beginColumn = 0;
                            reading--;
                            begin = nullptr;
                        }
                        break;
                    case State::InPreComment:
                        if (c == T('-')) {
                            state = State::InComment;
                        } else {
                            AddToken(reading - begin, CodeTokenType::Sub);
                            state = State::Begin;
                            beginColumn = 0;
                            reading--;
                            begin = nullptr;
                        }
                        break;
                    case State::InComment:
                        if (c == T('\n')) {
                            AddToken(reading - begin, CodeTokenType::Comment);
                            state = State::Begin;
                            beginColumn = 0;
                            reading--;
                            begin = nullptr;
                        }
                        break;
                    case State::InString:
                        if (c == T('"')) {
                            begin++; // 这里 +1 忽略掉字符串的第一个 "
                            AddToken(reading - begin, CodeTokenType::String);
                            state = State::Begin;
                            beginColumn = 0;
                            // 这里就不进行reading--，因为String的最后一个 " 可以直接忽略
                            begin = nullptr;
                        }
                        break;
                    case State::InIdentifier:
                        if (std::isdigit(c) || std::isalpha(c) || c == T('_') || c == T('.') || c == T('-')) {
                            // 不做处理
                        } else {
                            AddToken(reading - begin, CodeTokenType::Identifier);
                            state = State::Begin;
                            beginColumn = 0;
                            reading--;
                            begin = nullptr;
                        }
                        break;
                }
                NextChar();
                reading++;
            }

            // 如果达到文件末尾，且尚未回到Begin状态，这里用来处理最后一个token
            switch (state) {
                case State::Begin:
                    // 不做处理
                    break;
                case State::InIdentifier:
                    AddToken(reading - begin, CodeTokenType::Identifier);
                    break;
                case State::InInteger:
                    AddToken(reading - begin, CodeTokenType::Integer);
                    break;
                case State::InFloat:
                    AddToken(reading - begin, CodeTokenType::Float);
                    break;
                case State::InString:
                    std::cout << "token error" << std::endl;
                    break;
            }

            return file;
        }
    }
}