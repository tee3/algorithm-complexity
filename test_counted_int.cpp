#define BOOST_TEST_MODULE counted_int
#include <boost/test/unit_test.hpp>

#include <iostream>

#include <utility>

#include "counted_int.hpp"
#include "counted_operations.hpp"
#include "counted_operations_io.hpp"

BOOST_AUTO_TEST_CASE (counted_int_minimal)
{
   // mininal tests
   {
      std::cout << "initial state ------------------------\n";

      std::cout << counted_int::counts () << "\n";

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

      std::cout << counted_int::counts () << "\n";

      std::cout << "reset ------------------------\n";

      counted_int::reset ();

      std::cout << counted_int::counts () << "\n";
   }
}

// Local variables:
// flycheck-clang-language-standard: "c++14"
// End:
