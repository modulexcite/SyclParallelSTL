/* Copyright (c) 2015 The Khronos Group Inc.

  Permission is hereby granted, free of charge, to any person obtaining a
  copy of this software and/or associated documentation files (the
  "Materials"), to deal in the Materials without restriction, including
  without limitation the rights to use, copy, modify, merge, publish,
  distribute, sublicense, and/or sell copies of the Materials, and to
  permit persons to whom the Materials are furnished to do so, subject to
  the following conditions:

  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Materials.

  MODIFICATIONS TO THIS FILE MAY MEAN IT NO LONGER ACCURATELY REFLECTS
  KHRONOS STANDARDS. THE UNMODIFIED, NORMATIVE VERSIONS OF KHRONOS
  SPECIFICATIONS AND HEADER INFORMATION ARE LOCATED AT
     https://www.khronos.org/registry/

  THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/  
#include "gmock/gmock.h"

#include <vector>
#include <algorithm>

#include <experimental/algorithm>

class SortAlgorithm : public testing::Test {
public:
};

TEST_F(SortAlgorithm, TestStdSort) {
  std::vector<int> v = { 2, 1, 3 };

  std::sort(v.begin(), v.end());

  EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

using namespace std::experimental::parallel;

TEST_F(SortAlgorithm, TestSyclSort) {
  {
    std::vector<int> v(64);
    std::generate(v.begin(), v.end(), std::rand); // Using the C function rand()
    // The bitonic sort is triggered with a power of two vector size
    sycl::sort(sycl::sycl_policy, v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
  }

  {
    std::vector<int> v(3);
    std::generate(v.begin(), v.end(), std::rand); // Using the C function rand()
    // The bitonic sort is triggered with a power of two vector size
    sycl::sort(sycl::sycl_policy, v.begin(), v.end());
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
  }

  {
    std::array<int, 10> a;
    std::generate(a.begin(), a.end(), std::rand);
    sycl::sort(sycl::sycl_policy, a.begin(), a.end());
    EXPECT_TRUE(std::is_sorted(a.begin(), a.end()));
  }
}
