#ifndef TINYFJING_UNITTEST_H
#define TINYFJING_UNITTEST_H

#include "TinyFJingSTL.h"
#include <iostream>
#include <string>

using namespace std;

namespace tinyfjing {

    string_t ReadAnsiFile(const string_t& fileName) {
        ifstream i(fileName, ios_base::binary);
        i.seekg(0, ios_base::end);
        auto pos = i.tellg();
        i.seekg(0, ios_base::beg);

        string buffer;
        buffer.resize((size_t) pos);
        i.read(&buffer[0], pos);

#ifdef _UNICODE_TINYMOE
        return atow(buffer);
#else
        return buffer;
#endif
    }
}

#endif //TINYFJING_UNITTEST_H
