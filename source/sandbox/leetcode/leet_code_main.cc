#include <functional>
#include <map>
#include <set>
#include <string>

#include "coding_problem_list.h"
#include "common/util.h"

int subarraySum(vector<int>& nums, int k) {
  unordered_map<int, int> counts;
  counts[0] = 1;
  int ans = 0, curr = 0;

  for (int num : nums) {
    curr += num;
    ans += counts[curr - k];
    counts[curr]++;
  }

  return ans;
}

int numberOfSubarrays(vector<int>& nums, int k) {
  unordered_map<int, int> counts;
  counts[0] = 1;
  int ans = 0, curr = 0;

  for (int num : nums) {
    curr += num % 2;
    ans += counts[curr - k];
    counts[curr] += 1;
  }

  return ans;
}

vector<vector<int>> findWinners(vector<vector<int>>& matches) {
  std::set<int> winners;
  map<int, int> loosers;

  std::vector<std::vector<int>> ret_vector;
  ret_vector.push_back(std::vector<int>());
  ret_vector.push_back(std::vector<int>());

  for (size_t it = 0; it < matches.size(); it++) {
    winners.insert(matches[it][0]);
    loosers[matches[it][1]]++;
  }

  for (std::set<int>::const_iterator it = winners.cbegin(); it != winners.cend();
       it++) {
    if (loosers.find(*it) == loosers.end()) {
      ret_vector[0].push_back(*it);
    }
  }

  for (std::map<int, int>::const_iterator it = loosers.cbegin();
       it != loosers.cend(); it++) {
    if (it->second == 1) {
      ret_vector[1].push_back(it->first);
    }
  }

  return ret_vector;
}

int main(int argCount, char* argc[]) {

    std::vector<int> array = {1, 1, 2, 1, 1};
  numberOfSubarrays(array, 2);
    std::vector<int> prefix_array = engine::util::PrefixArray(array);
    std::cout << engine::util::ToStr(prefix_array);
  INSTANTIATE_PROBLEM(UniqueEmailAddressProblem);
  INSTANTIATE_PROBLEM(SortedSquareArray);
  INSTANTIATE_PROBLEM(MinStartValueProblem);
  INSTANTIATE_PROBLEM(KRadiusAveragesProblem);
}