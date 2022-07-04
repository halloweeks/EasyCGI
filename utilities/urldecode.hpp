#ifndef _URL_DECODE_
#define _URL_DECODE_

#include <string.h>

std::string urldecode(const std::string& value) {
	std::string result;
    result.reserve(value.size());
    for (std::size_t i = 0; i < value.size(); ++i) {
    	auto ch = value[i];
        if (ch == '%' && (i + 2) < value.size()) {
            auto hex = value.substr(i + 1, 2);
            auto dec = static_cast<char>(std::strtol(hex.c_str(), nullptr, 16));
            result.push_back(dec);
            i += 2;
        } else if (ch == '+') {
            result.push_back(' ');
        } else {
            result.push_back(ch);
        }
    }
    return result;
}

#endif