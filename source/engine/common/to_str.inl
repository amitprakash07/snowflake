#ifndef ENGINE_COMMON_TO_STR_INL
#define ENGINE_COMMON_TO_STR_INL

#include "to_str.h"

template <>
char* engine::ToStr<int>(const int& data)
{
    char* ret_char_array = kCharArrayStorageFor32BitData;
    ret_char_array[kMaxCharArraySizeFor32Bit - 1] = '\0';
    uint8_t begin = kMaxCharArraySizeFor32Bit - 2;
    int copied_data = data < 0 ? (0 - data) : data;

    while (copied_data)
    {
        ret_char_array[begin] = kDecimalInChars[copied_data % 10];
        copied_data /= 10;
        begin--;
    }

    if (data < 0)
    {
        ret_char_array[begin] = '-';
    }
    else
    {
        begin++;
    }

    char* ret_ptr = ret_char_array + begin;
    return ret_ptr;
}
#endif 
