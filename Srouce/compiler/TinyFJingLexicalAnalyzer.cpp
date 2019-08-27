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

            State state = State::Begin;

            auto AddToken = [&](int length, CodeTokenType type) {
                if (type == CodeTokenType::Comment) {
                    std::cout << T("comment") << std::endl;
                    return;
                }
            };

            while (auto c = *reading) {
                switch (state) {
                    case State::Begin:
                        switch (c) {
                            case T('-'):
                                begin = reading;
                                state = State::InPreComment;
                                break;
                            case T('"'):
                                state = State::InString;
                                break;
                            case T('('):
                                break;
                            case T(')'):
                                break;
                            case T(' '):
                            case T('\t'):
                            case T('\r'):
                                break;
                            case T('\n'):
                                row += 1;
                                column = 1;
                                break;
                            default:
                                if (std::isalpha(c) || c == T('_')) {
                                    begin = reading;
                                    state = State::InIdentifier;
                                } else if (std::isdigit(c)) {
                                    begin = reading;
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
                            begin = nullptr;
                            state = State::Begin;
                        }
                        break;
                    case State::InFloat:
                        if (std::isdigit(c)) {
                            // 不做处理
                        } else {
                            // AddToken
                        }
                        break;
                    case State::InPreComment:
                        if (c == T('-')) {
                            state = State::InComment;
                        } else {
                            // todo AddToken CodeTokenType::Sub
                        }
                        break;
                    case State::InComment:
                        if (c == T('\n')) {
                            // todo AddToken CodeTokenType::Comment
                            AddToken(reading - begin, CodeTokenType::Comment);
                            begin = nullptr;
                            state = State::Begin;
                        }
                        break;
                    case State::InString:
                        if (c == T('"')) {
                            // todo AddToken String
                            begin++; // 这里 +1 使用为string可能为空串例如：""
                            AddToken(reading - begin, CodeTokenType::String);
                            state = State::Begin;
                            begin = nullptr;
                        }
                        break;
                    case State::InIdentifier:
                        if (std::isdigit(c) || std::isalpha(c) || c == T('_') || c == T('.') || c == T('-')) {
                            // 不做处理
                        } else {
                            // todo AddToken Identifier
                        }
                        break;
                    default:
                        break;
                }
                reading++;
            }

            // 如果达到文件末尾，且尚未回到Begin状态，这里用来处理最后一个token
            switch (state) {
                case State::Begin:
                    // 不做处理
                    break;
                default:
                    break;
            }


            return nullptr;
        }
    }
}