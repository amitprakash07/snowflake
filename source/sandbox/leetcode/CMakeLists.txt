cmake_minimum_required(VERSION 3.25.0)

declare_target(LeetCode)
include_src(coding_problems.h)
include_src(coding_problem_list.h)
include_src(unique_email_address.h)
include_src(sorted_square_array.h)
include_src(leet_code_main.cc)

make_executable_target()
group_target(LeetCode)