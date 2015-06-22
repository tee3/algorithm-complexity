#define BOOST_TEST_MODULE counted_int
#include <boost/test/unit_test.hpp>

#include <iostream>

#include <utility>

#include "counted_int.hpp"

BOOST_AUTO_TEST_CASE (counted_int_minimal)
{
   // mininal tests
   {
      std::cout << "verifying that counts are public ------------\n";

      std::cout << "constructions: " << counted_int::constructions << "\n";
      std::cout << "assignments: " << counted_int::assignments << "\n";
      std::cout << "copies: " << counted_int::copies << "\n";
      std::cout << "destructions: " << counted_int::destructions << "\n";
      std::cout << "accesses: " << counted_int::accesses << "\n";
      std::cout << "comparisons: " << counted_int::comparisons << "\n";
      std::cout << "swaps: " << counted_int::swaps << "\n";

      std::cout << "initial state ------------------------\n";

      counted_int::print_counted_operations ();

      std::cout << "minimal test ------------------------\n";

      counted_int::reset ();

      {
         counted_int c0 (0);
         counted_int c1 = 1;
         counted_int c2 (c1);
         counted_int c3 = c2;

         bool b0 = c0 == c1;
         BOOST_CHECK_EQUAL (b0,false);
         bool b1 = c0 != c1;
         BOOST_CHECK_EQUAL (b1,true);
         bool b2 = c0 < c1;
         BOOST_CHECK_EQUAL (b2,true);
         bool b3 = c0 > c1;
         BOOST_CHECK_EQUAL (b3,false);
         bool b4 = c0 <= c1;
         BOOST_CHECK_EQUAL (b4,true);
         bool b5 = c0 >= c1;
         BOOST_CHECK_EQUAL (b5,false);

         using std::swap;
         swap (c2,c3);
      }

      counted_int::print_counted_operations ();

      std::cout << "reset ------------------------\n";

      counted_int::reset ();

      counted_int::print_counted_operations ();
   }
}

// Local variables:
// flycheck-clang-language-standard: "c++14"
// End:
