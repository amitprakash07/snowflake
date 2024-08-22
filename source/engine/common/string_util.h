#ifndef ENGINE_COMMON_STRING_UTIL_H
#define ENGINE_COMMON_STRING_UTIL_H

#include <string>

namespace engine {
namespace util {
std::string RemoveString(std::string removeFrom, std::string remmveWith,
                         bool beginning = true);
}
}  
#endif