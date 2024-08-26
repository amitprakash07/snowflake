#include "string_util.h"

using namespace engine;
std::string util::RemoveString(std::string remove_from, std::string remvoe_with,
                               bool beginning) {
  std::string returnString;
  if (beginning) {
    char *returnStringInChar =
        new char[remove_from.size() - remvoe_with.size() + 1];
    memcpy(returnStringInChar, remove_from.c_str() + remvoe_with.size(),
           remove_from.size() - remvoe_with.size());
    returnStringInChar[remove_from.size() - remvoe_with.size()] = '\0';
    returnString = returnStringInChar;
    delete[] returnStringInChar;
  }
  return returnString;
}
std::string util::ReverseEachWordsInString(std::string sentence,
                                           char separator) {
  size_t start_index = 0;
  size_t end_index = 0;

  while (sentence[end_index] != '\0') {
    if (sentence[end_index + 1] == separator ||
        sentence[end_index + 1] == '\0') {
      // reverse word
      size_t word_end_index = end_index;
      while (start_index < word_end_index) {
        char temp = sentence[start_index];
        sentence[start_index] = sentence[word_end_index];
        sentence[word_end_index] = temp;
        start_index++;
        word_end_index--;
      }

      end_index++;
      start_index = end_index + 1;
    } else {
      end_index++;
    }
  }

  return sentence;
}

std::string util::ReverseOnlyLetters(std::string s) {
  size_t start_index = 0;
  size_t end_index = s.size();
  while (start_index < end_index) {
    if (!IsLetter(s[start_index])) {
      start_index++;
      continue;
    }

    if (!IsLetter(s[end_index])) {
      end_index--;
      continue;
    }

    char temp = s[start_index];
    s[start_index] = s[end_index];
    s[end_index] = temp;
    start_index++;
    end_index--;
  }

  return s;
}

bool util::IsLetter(char ch) {
  // A-Z : 65 - 90
  // a-z : 97 - 122
  if (65 <= ch && ch <= 90) {
    return true;
  }

  if (97 <= ch && ch <= 122) {
    return true;
  }

  return false;
}
