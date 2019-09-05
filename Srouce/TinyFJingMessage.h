#ifndef TINYFJING_TINYFJINGMESSAGE_H
#define TINYFJING_TINYFJINGMESSAGE_H

#include "TinyFJingSTL.h"

namespace tinyfjing {

    static std::map<string_t, string_t> TINYFJING_MESSAGE = {
            {T("FIRST_LINE_NEED_MODULE"), T("文件第一行需要使用 module 关键字指定模块名称")},
            {T("NEED_IDENTIFIER"),        T("需要一个标识符")},
            {T("NEED_KEYWORD"),           T("需要一个关键字:${name}")},
            {T("TOKEN_ENDED"),            T("文件意外结束")}
    };

    inline static string_t GetFormatMsg(const string_t &key, const std::map<string_t, string_t> &param) {
        // todo
        return T("");
    }

    inline static string_t GetFormatMsg(const string_t &key) {
        return TINYFJING_MESSAGE[key];
    }

}

#endif //TINYFJING_TINYFJINGMESSAGE_H
