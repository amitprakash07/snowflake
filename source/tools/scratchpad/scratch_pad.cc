#include <bitset>
#include <functional>
#include <iostream>
#include <vector>

struct Data {
  uint32_t InstanceID : 24;
  uint32_t InstanceMask : 8;
  uint32_t InstanceContributionToHitGroupIndex : 24;
  uint32_t Flags : 8;
};

// void* operator new(size_t size)
//{
//     std::cout << "Allocated " << size << std::endl;
//     return malloc(size);
// }
//
// void operator delete(void* ptr)
//{
//     free(ptr);
// }

enum D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS : uint32_t {
  D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_NONE = 0,
  D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_ALLOW_UPDATE = 0x1,
  D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_ALLOW_COMPACTION = 0x2,
  D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_PREFER_FAST_TRACE = 0x4,
  D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_PREFER_FAST_BUILD = 0x8,
  D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_MINIMIZE_MEMORY = 0x10,
  D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_PERFORM_UPDATE = 0x20
};

struct DataForTestClassForOverloading {
 private:
  uint8_t m_data;
};

class TestClassForOverloading {
 public:
  DataForTestClassForOverloading GetData() { return m_data; }
  const DataForTestClassForOverloading& GetData() const { return GetData(); }

 private:
  DataForTestClassForOverloading m_data;
};

class TestLambdaExecution {
 public:
  TestLambdaExecution(size_t count) {
    m_lambdaList.resize(count);

    for (size_t it = 0; it < count; it++) {
      m_values.push_back(it + 1);
    }
  }

  void InitData(size_t index, std::function<uint32_t(uint32_t)> lambda) {
    m_lambdaList[index] = lambda;
  }

  void ExecuteLambda() {
    for (size_t it = 0; it < m_values.size(); it++) {
      m_values[it] = m_lambdaList[it](m_values[it]);
    }
  }

  static void Test() {
    size_t count = 20;
    TestLambdaExecution testLambda(count);

    {
      uint32_t addMore = 1;

      for (size_t it = 0; it < count; it++, addMore++) {
        testLambda.InitData(it, [addMore](uint32_t inVal) -> uint32_t {
          return (inVal * 2) + addMore;
        });
      }
    }

    testLambda.ExecuteLambda();
  }

  void UpdateValues(uint32_t index, uint32_t factor) {
    m_values[index] = ((m_values[index] + factor) * factor) + 2301;
  }

  static void UseLambdaToUpdate() {
    size_t count = 200000;
    uint32_t factor = 1;
    TestLambdaExecution testLambda_1(count);

    for (uint32_t it = 0; it < count; it++, factor++) {
      auto lambda = [&testLambda_1](uint32_t index, uint32_t factor) {
        testLambda_1.m_values[index] =
            ((testLambda_1.m_values[index] + factor) * factor) + 2301;
      };

      lambda(it, factor);
    }
  }

  static void UseFunctionToUpdate() {
    size_t count = 200000;
    uint32_t factor = 1;
    TestLambdaExecution testLambda_2(count);
    for (uint32_t it = 0; it < count; it++, factor++) {
      testLambda_2.UpdateValues(it, factor);
    }
  }

 private:
  std::vector<uint32_t> m_values;
  std::vector<std::function<uint32_t(uint32_t anotherVal)>> m_lambdaList;
};

enum TestEnum { One = 0x1, Two = 0x2 };

enum class ReplayPlugin { FrameAnalyzer, FrameModifer };

//template <class Enum, bool is_enum = std::is_enum<Enum>::value>
//class IReplayPlugin {};
//
//class ReplayPlugin : public IReplayPlugin<uint32_t>
//{
//    
//};

#include <iostream>
#include <utility>

struct Default {
  int foo() const { return 1; }
  void foo_void() {}
};

struct NonDefault {
  NonDefault() = delete;
  int foo() const { return 1; }
};

struct T {
  enum { int_t, float_t } type;

  template <typename Integer,
            std::enable_if_t<std::is_integral<Integer>::value, bool> = true>
  T(Integer) : type(int_t) {}

  template <
      typename Floating,
      std::enable_if_t<std::is_floating_point<Floating>::value, bool> = true>
  T(Floating) : type(float_t) {}  // OK
};

int main(int argcCount, char* argc[]) {

    decltype(Default().foo()) n1 = 1;  // type of n1 is int

    constexpr bool void_type = std::is_void<decltype(Default().foo_void())>();
  //  decltype(NonDefault().foo()) n2 = n1;               // error: no default
  //  constructor
  decltype(std::declval<NonDefault>().foo()) n2 = n1;  // type of n2 is int
  std::cout << "n1 = " << n1 << '\n' << "n2 = " << n2 << '\n';

  for (uint32_t i = 0; i < 10; i++) {
    std::cout << i << std::endl;
  }

    for (uint32_t i = 0; i < 10; ++i) {
    std::cout << i << std::endl;
  }



  TestLambdaExecution::Test();
  // TestLambdaExecution::UseLambdaToUpdate();
  // TestLambdaExecution::UseFunctionToUpdate();

  // TestClassForOverloading test;
  // const DataForTestClassForOverloading temp = test.GetData();

  // uint32_t val = 0x20000100;

  // uint64_t val_64 = 0x0123456789abcdef;
  // char* val_64_ptr = (char*)&val_64;

  // uint32_t val_32_lsb = 0;
  // char* val_32_1_ptr = (char*)&val_32_lsb;

  // uint32_t val_32_msb = 0;
  // char* val_32_2_ptr = (char*)&val_32_msb;

  // uint8_t ptrIter = 0;
  // for (uint8_t i = 0; i < 4; i++) {
  //   val_32_1_ptr[i] = val_64_ptr[ptrIter];
  //   ptrIter++;
  // }

  // for (uint8_t i = 0; i < 4; i++) {
  //   val_32_2_ptr[i] = val_64_ptr[ptrIter];
  //   ptrIter++;
  // }

  // uint64_t make64 = 0;
  // make64 = val_32_msb;
  // make64 = make64 << 32;
  // make64 |= val_32_lsb;

  /*char* make64Ptr = (char*) & make64;
  ptrIter = 0;
  for (uint8_t i = 0; i < 4; i++)
  {
      make64Ptr[ptrIter] = val_32_1_ptr[i];
      ptrIter++;
  }

  for (uint8_t i = 0; i < 4; i++)
  {
      make64Ptr[ptrIter] = val_32_2_ptr[i];
      ptrIter++;
  }*/

  // val;
  // uint32_t testEnum = One | Two;

  // uint32_t buildFlags =
  //     D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_ALLOW_UPDATE |
  //     D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_ALLOW_COMPACTION |
  //     D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_PERFORM_UPDATE;

  // std::cout << std::bitset<8>(buildFlags) << std::endl;

  // if (buildFlags &
  //     D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_PERFORM_UPDATE) {
  //   uint32_t performUpdateMask =
  //       D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_PERFORM_UPDATE;
  //   buildFlags ^= performUpdateMask;
  //   std::cout << std::bitset<8>(buildFlags) << std::endl;
  // }

  // std::string s1("0123456789");
  // Data* d1 = new Data();
  // Data d;
  // d.InstanceID = 10;
  // d.InstanceMask = 5;
  // d.InstanceContributionToHitGroupIndex = 1;
  // d.Flags = 0;

  // std::cout << "Sizeof data is " << sizeof(Data) << std::endl;
  // std::cout << std::bitset<32>(d.InstanceID) << std::endl
  //           << std::bitset<32>(d.InstanceMask);

  // uint32_t instanceId = d.InstanceID;
  // uint32_t instanceMask = d.InstanceMask;
  // std::cout << "Instance Val" << instanceId << std::endl;
  // std::cout << "Instance Mask" << instanceMask << std::endl;
  // instanceMask++;
  // instanceId++;

  // d.InstanceID = instanceId;
  // d.InstanceMask = instanceMask;
  // std::cout << std::bitset<32>(d.InstanceID) << std::endl
  //           << std::bitset<32>(d.InstanceMask);
}