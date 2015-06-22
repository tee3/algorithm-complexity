#include <iostream>

#include <utility>

#include <cassert>

#include "counted_int.hpp"

int
main ()
{
   // mininal tests
   {
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
         assert (!b0);
         bool b1 = c0 != c1;
         assert (b1);
         bool b2 = c0 < c1;
         assert (b2);
         bool b3 = c0 > c1;
         assert (!b3);
         bool b4 = c0 <= c1;
         assert (b4);
         bool b5 = c0 >= c1;
         assert (!b5);

         using std::swap;
         swap (c2,c3);
      }

      counted_int::print_counted_operations ();

      std::cout << "reset ------------------------\n";

      counted_int::reset ();

      counted_int::print_counted_operations ();
   }

   return 0;
}

// Local variables:
// flycheck-clang-language-standard: "c++14"
// End:
