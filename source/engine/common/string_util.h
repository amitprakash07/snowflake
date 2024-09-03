#ifndef ENGINE_COMMON_STRING_UTIL_H
#define ENGINE_COMMON_STRING_UTIL_H

#include <stack>
#include <string>

namespace engine {
namespace util {
std::string RemoveString(const std::string& remove_from,
                         const std::string& remove_with, bool beginning = true);

std::string ReverseEachWordsInString(std::string sentence,
                                     char separator = ' ');

std::string ReverseOnlyLetters(std::string s);

bool IsLetter(char ch);

std::string RemoveDuplicates(const std::string& s);

size_t LengthOfLongestSubstring(const std::string& str);

     std::string SimplifyPath(const std::string& path);

    std::string MakeGood(const std::string& s);
     }  // namespace util
}  // namespace engine
#endif