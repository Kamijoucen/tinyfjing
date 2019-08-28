#ifndef TINYFJING_TINYFJINGSTL_H
#define TINYFJING_TINYFJINGSTL_H

#include <vector>
#include <list>
#include <set>
#include <map>
#include <memory>
#include <string>
#include <sstream>
#include <algorithm>
#include <tuple>
#include <functional>
#include <fstream>
#include <iostream>
#include <utility>

namespace tinyfjing
{
#ifdef _UNICODE_TINYFJING
    typedef wchar_t char_t;
	typedef std::wstring string_t;
	typedef std::wifstream ifstream_t;
	typedef std::wofstream ofstream_t;
	typedef std::wistream istream_t;
	typedef std::wostream ostream_t;
	typedef std::wstringstream stringstream_t;

	#define T(X) L ## X
	#define strtol_t wcstol
	#define strtod_t wcstod
#else
    typedef char char_t;
    typedef std::string string_t;
    typedef std::ifstream ifstream_t;
    typedef std::ofstream ofstream_t;
    typedef std::istream istream_t;
    typedef std::ostream ostream_t;
    typedef std::stringstream stringstream_t;

#define T(X) X
#define strtol_t strtol
#define strtod_t strtod
#endif
}

#endif //TINYFJING_TINYFJINGSTL_H
