#ifndef ENGINE_COMMON_STRING_UTIL_H
#define ENGINE_COMMON_STRING_UTIL_H

#include <string>

namespace engine {
    namespace util {
        std::string RemoveString(const std::string& remove_from, const std::string& remove_with,
            bool beginning = true);

        std::string ReverseEachWordsInString(std::string sentence,
            char separator = ' ');

        std::string ReverseOnlyLetters(std::string s);

        bool IsLetter(char ch);

        size_t LengthOfLongestSubstring(const std::string& str);
    }  // namespace util
}  // namespace engine
#endif