#include <functional>
#include <string>

#include "coding_problem_list.h"
#include "common/util.h"

int main(int argCount, char* argc[]) {

    std::vector<int> array = {5, 2, 1, 6, 3, 8 };
    std::vector<int> prefix_array = engine::util::PrefixArray(array);
    std::cout << engine::util::ToStr(prefix_array);
  INSTANTIATE_PROBLEM(UniqueEmailAddressProblem);
  INSTANTIATE_PROBLEM(SortedSquareArray);
  INSTANTIATE_PROBLEM(MinStartValueProblem);
  INSTANTIATE_PROBLEM(KRadiusAveragesProblem);
}