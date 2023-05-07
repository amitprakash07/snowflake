#include <iostream>
#include <vector>

template <typename Tag, class type>
class TaggedDataType {
public:
  TaggedDataType(type) {}
};

TaggedDataType<uint32_t, uint32_t> ee();
using DataAlignment = uint32_t;

class Data
{
public:
  explicit Data(DataAlignment alignment, DataSize size);
};



int main(int argcCount, char* argc[])
{
    std::cout << "yello";
    uint32_t dataVal = 10;
    uint32_t alignment = 256;

    Data data(alignment, dataVal);
}