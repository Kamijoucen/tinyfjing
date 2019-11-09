/*
 * @Author: kamijoucen
 * @Date: 2019-10-29 23:11:48
 * @LastEditTime: 2019-11-09 19:37:40
 * @LastEditors: kamijoucen
 * @Description: 
 * @FilePath: \tinyfjing\Srouce\TinyFJingMessage.h
 * @
 */
#ifndef TINYFJING_TINYFJINGMESSAGE_H
#define TINYFJING_TINYFJINGMESSAGE_H

#include "TinyFJingSTL.h"

namespace tinyfjing {

    const static std::map<string_t, string_t> TINYFJING_MESSAGE = {
            {T("FIRST_LINE_NEED_MODULE"), T("文件第一行需要使用 module 关键字指定模块名称")},
            {T("NEED_IDENTIFIER"),        T("需要一个标识符")},
            {T("NEED_KEYWORD"),           T("需要一个关键字:${name}")},
            {T("TOKEN_ENDED"),            T("文件意外结束")},
            {T("TOKEN_ERROR"),            T("token类型错误")},
            {T("EXPRESSION_NOT_FOUND"),   T("表达式未找到")}
    };

    inline static string_t GetFormatMsg(const string_t &key, const std::map<string_t, string_t> &param) {
        // todo
        return T("");
    }

    inline static string_t GetFormatMsg(const string_t &key) {
        auto iter = TINYFJING_MESSAGE.find(key);
        if (iter != TINYFJING_MESSAGE.end()) {
            return iter->second;
        }
        return "";
    }

}

#endif //TINYFJING_TINYFJINGMESSAGE_H
