#ifndef SANDBOX_LEETCODE_PASCALS_TRIANGLE_H
#define SANDBOX_LEETCODE_PASCALS_TRIANGLE_H

#include <array>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <map>

#include "interface.h"
#include "common/to_str.h"

using namespace std;

class PascalsTriangle : public ICodingProblem
{
public:
    vector<vector<int>> generate(int numRows)
    {
        std::vector<std::vector<int>> ret;
        bool                          use_binomial = true;

        if (numRows > 0)
        {
            if (use_binomial)
            {
                for (int i = 1; i <= numRows; i++)
                {
                    ret.push_back(GetBinomial(i - 1));
                }
            }
            else
            {
                std::vector<int> current_row;
                for (int i = 0; i < numRows; i++)
                {
                    current_row.resize(i + 1);
                    current_row[0] = 1;
                    current_row[i] = 1;

                    for (int j = 1; j < i; j++)
                    {
                        current_row[j] = ret[i - 1][j - 1] + ret[i - 1][j];
                    }

                    ret.push_back(current_row);
                }
            }
        }

        return ret;
    }

    void RunTests() override
    {
        for (int i = 1; i < 20; i++)
        {
            std::vector<std::vector<int>> pascals_triangle = generate(i);

            for (const auto& row_coefficient : pascals_triangle)
            {
                for (const auto& coefficient : row_coefficient)
                {
                    std::cout << coefficient;
                }
            }
        }
    }

    struct Combinatorics
    {
        int count;
        int choose;

        bool operator==(const Combinatorics& other) const
        {
            if (count == other.count)
            {
                int max_val       = max(choose, count - choose);
                int other_max_val = max(other.choose, other.count - other.choose);
                return max_val == other_max_val;
            }

            return false;
        }

        bool operator!=(const Combinatorics& other) const
        {
            return !(*this == other);
        }
    };

private:
    int GetFactorial(int val)
    {
        if (factorials.contains(val))
        {
            return factorials[val];
        }

        if (val == 0 || val == 1)
        {
            return 1;
        }

        factorials[val] = val * GetFactorial(val - 1);
        return factorials[val];
    }

    std::vector<int> GetBinomial(int n)
    {
        std::vector<int> coefficients;

        if (n >= 0)
        {
            coefficients.resize(n + 1);
            coefficients[0] = 1;
            coefficients[n] = 1;

            for (int i = 1; i < n; i++)
            {
                int           coefficient;
                Combinatorics temp{n, i};
                if (coefficients_map.contains(temp))
                {
                    coefficient = coefficients_map[temp];
                }
                else
                {
                    int max_of_i_and_n_minus_i = max(i, n - i);
                    coefficient                = GetProductUpto(n, i) / GetFactorial(i);
                    coefficients_map[temp]     = coefficient;
                }
                coefficients[i] = coefficient;
            }
        }

        return coefficients;
    }

    inline int GetProductUpto(int n, int a)
    {
        int p = 1;
        for (int i = n; i > (n - a); i--)
        {
            p *= i;
        }

        return p;
    }

    struct CombinatoricsHash
    {
        std::size_t operator()(const PascalsTriangle::Combinatorics& in) const noexcept
        {
            size_t count_hash   = std::hash<int>{}(in.count);
            size_t max_val_hash = std::hash<int>{}(std::max(in.count - in.choose, in.choose));
            return count_hash ^ (max_val_hash << 1);
        }
    };

    static std::map<int, int>                                        factorials;
    static std::unordered_map<Combinatorics, int, CombinatoricsHash> coefficients_map;
};

#endif