#define BOOST_TEST_MODULE complexity
#include <boost/test/unit_test.hpp>

#include <iostream>

#include <cmath>

#include "complexity.hpp"

BOOST_AUTO_TEST_CASE (complexity)
{
   for (long int i = 2; i < 12; ++i)
   {
      auto n = static_cast<unsigned long long int> (1) << i;

      std::cout << "-------------------\n";
      std::cout << "O(1) where n = " << n << ": " << O_1 (n) << "\n";
      std::cout << "O(n) where n = " << n << ": " << O_n (n) << "\n";
      std::cout << "O(n log2 (n)) where n = " << n << ": " << O_n_log2_n (n) << "\n";
      std::cout << "O(n^2) where n = " << n << ": " << O_n_2 (n) << "\n";
      std::cout << "O(n^3) where n = " << n << ": " << O_n_3 (n) << "\n";

      // @todo exact tests only, this is totally broken
      BOOST_CHECK_EQUAL (complexity_string (n,1),"O(1)");
      BOOST_CHECK_EQUAL (complexity_string (n,n),"O(n)");
      BOOST_CHECK_EQUAL (complexity_string (n,n*std::log2(n)),"O(n*log2(n))");
      BOOST_CHECK_EQUAL (complexity_string (n,n*n),"O(n^2)");
      BOOST_CHECK_EQUAL (complexity_string (n,n*n*n),"O(n^3)");
   }
}

// Local variables:
// flycheck-clang-language-standard: "c++14"
// End:
