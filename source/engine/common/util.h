#ifndef ENGINE_COMMON_UTIL_H
#define ENGINE_COMMON_UTIL_H

#include <vector>
#include <sstream>

namespace engine {
namespace util {
    inline std::vector<int> PrefixArray(const std::vector<int>& input);

    std::string ToStr(const std::vector<int>& input_array);
    
}
}  
#endif