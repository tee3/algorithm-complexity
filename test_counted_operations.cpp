#define BOOST_TEST_MODULE counted_operations
#include <boost/test/unit_test.hpp>

#include <iostream>

#include <utility>
#include <limits>

#include "counted_operations.hpp"
#include "counted_operations_io.hpp"

BOOST_AUTO_TEST_CASE (counted_operations_minimal)
{
   // minimal tests
   {
      counted_operations c;

      BOOST_CHECK_EQUAL (c.constructions,0);
      BOOST_CHECK_EQUAL (c.assignments,0);
      BOOST_CHECK_EQUAL (c.copies,0);
      BOOST_CHECK_EQUAL (c.destructions,0);
      BOOST_CHECK_EQUAL (c.accesses,0);
      BOOST_CHECK_EQUAL (c.comparisons,0);
      BOOST_CHECK_EQUAL (c.swaps,0);

      c.constructions = 1;
      c.assignments = 1;
      c.copies = 1;
      c.destructions = 1;
      c.accesses = 1;
      c.comparisons = 1;
      c.swaps = 1;

      BOOST_CHECK_EQUAL (c.constructions,1);
      BOOST_CHECK_EQUAL (c.assignments,1);
      BOOST_CHECK_EQUAL (c.copies,1);
      BOOST_CHECK_EQUAL (c.destructions,1);
      BOOST_CHECK_EQUAL (c.accesses,1);
      BOOST_CHECK_EQUAL (c.comparisons,1);
      BOOST_CHECK_EQUAL (c.swaps,1);

      c.reset ();

      BOOST_CHECK_EQUAL (c.constructions,0);
      BOOST_CHECK_EQUAL (c.assignments,0);
      BOOST_CHECK_EQUAL (c.copies,0);
      BOOST_CHECK_EQUAL (c.destructions,0);
      BOOST_CHECK_EQUAL (c.accesses,0);
      BOOST_CHECK_EQUAL (c.comparisons,0);
      BOOST_CHECK_EQUAL (c.swaps,0);
   }

   {
      counted_operations c (0);
      BOOST_CHECK_EQUAL (c.constructions,0);
      BOOST_CHECK_EQUAL (c.assignments,0);
      BOOST_CHECK_EQUAL (c.copies,0);
      BOOST_CHECK_EQUAL (c.destructions,0);
      BOOST_CHECK_EQUAL (c.accesses,0);
      BOOST_CHECK_EQUAL (c.comparisons,0);
      BOOST_CHECK_EQUAL (c.swaps,0);
   }

   {
      counted_operations c (1);
      BOOST_CHECK_EQUAL (c.constructions,1);
      BOOST_CHECK_EQUAL (c.assignments,1);
      BOOST_CHECK_EQUAL (c.copies,1);
      BOOST_CHECK_EQUAL (c.destructions,1);
      BOOST_CHECK_EQUAL (c.accesses,1);
      BOOST_CHECK_EQUAL (c.comparisons,1);
      BOOST_CHECK_EQUAL (c.swaps,1);
   }

   {
      counted_operations c (std::numeric_limits<counted_operations::counter_type>::max ());

      BOOST_CHECK_EQUAL (c.constructions,
                         std::numeric_limits<counted_operations::counter_type>::max ());
      BOOST_CHECK_EQUAL (c.assignments,
                         std::numeric_limits<counted_operations::counter_type>::max ());
      BOOST_CHECK_EQUAL (c.copies,
                         std::numeric_limits<counted_operations::counter_type>::max ());
      BOOST_CHECK_EQUAL (c.destructions,
                         std::numeric_limits<counted_operations::counter_type>::max ());
      BOOST_CHECK_EQUAL (c.accesses,
                         std::numeric_limits<counted_operations::counter_type>::max ());
      BOOST_CHECK_EQUAL (c.comparisons,
                         std::numeric_limits<counted_operations::counter_type>::max ());
      BOOST_CHECK_EQUAL (c.swaps,
                         std::numeric_limits<counted_operations::counter_type>::max ());
   }

   {
      counted_operations c (1,2,3,4,5,6,7);

      BOOST_CHECK_EQUAL (c.constructions,1);
      BOOST_CHECK_EQUAL (c.assignments,2);
      BOOST_CHECK_EQUAL (c.copies,3);
      BOOST_CHECK_EQUAL (c.destructions,4);
      BOOST_CHECK_EQUAL (c.accesses,5);
      BOOST_CHECK_EQUAL (c.comparisons,6);
      BOOST_CHECK_EQUAL (c.swaps,7);
   }

   // addition
   {
      counted_operations c0 (1);

      BOOST_CHECK_EQUAL (c0.constructions,1);
      BOOST_CHECK_EQUAL (c0.assignments,1);
      BOOST_CHECK_EQUAL (c0.copies,1);
      BOOST_CHECK_EQUAL (c0.destructions,1);
      BOOST_CHECK_EQUAL (c0.accesses,1);
      BOOST_CHECK_EQUAL (c0.comparisons,1);
      BOOST_CHECK_EQUAL (c0.swaps,1);

      counted_operations c1 (1);

      BOOST_CHECK_EQUAL (c1.constructions,1);
      BOOST_CHECK_EQUAL (c1.assignments,1);
      BOOST_CHECK_EQUAL (c1.copies,1);
      BOOST_CHECK_EQUAL (c1.destructions,1);
      BOOST_CHECK_EQUAL (c1.accesses,1);
      BOOST_CHECK_EQUAL (c1.comparisons,1);
      BOOST_CHECK_EQUAL (c1.swaps,1);

      counted_operations c2 = c0 + c1;

      BOOST_CHECK_EQUAL (c0.constructions,1);
      BOOST_CHECK_EQUAL (c0.assignments,1);
      BOOST_CHECK_EQUAL (c0.copies,1);
      BOOST_CHECK_EQUAL (c0.destructions,1);
      BOOST_CHECK_EQUAL (c0.accesses,1);
      BOOST_CHECK_EQUAL (c0.comparisons,1);
      BOOST_CHECK_EQUAL (c0.swaps,1);

      BOOST_CHECK_EQUAL (c1.constructions,1);
      BOOST_CHECK_EQUAL (c1.assignments,1);
      BOOST_CHECK_EQUAL (c1.copies,1);
      BOOST_CHECK_EQUAL (c1.destructions,1);
      BOOST_CHECK_EQUAL (c1.accesses,1);
      BOOST_CHECK_EQUAL (c1.comparisons,1);
      BOOST_CHECK_EQUAL (c1.swaps,1);

      BOOST_CHECK_EQUAL (c2.constructions,2);
      BOOST_CHECK_EQUAL (c2.assignments,2);
      BOOST_CHECK_EQUAL (c2.copies,2);
      BOOST_CHECK_EQUAL (c2.destructions,2);
      BOOST_CHECK_EQUAL (c2.accesses,2);
      BOOST_CHECK_EQUAL (c2.comparisons,2);
      BOOST_CHECK_EQUAL (c2.swaps,2);

      c2 += c0;

      BOOST_CHECK_EQUAL (c0.constructions,1);
      BOOST_CHECK_EQUAL (c0.assignments,1);
      BOOST_CHECK_EQUAL (c0.copies,1);
      BOOST_CHECK_EQUAL (c0.destructions,1);
      BOOST_CHECK_EQUAL (c0.accesses,1);
      BOOST_CHECK_EQUAL (c0.comparisons,1);
      BOOST_CHECK_EQUAL (c0.swaps,1);

      BOOST_CHECK_EQUAL (c2.constructions,3);
      BOOST_CHECK_EQUAL (c2.assignments,3);
      BOOST_CHECK_EQUAL (c2.copies,3);
      BOOST_CHECK_EQUAL (c2.destructions,3);
      BOOST_CHECK_EQUAL (c2.accesses,3);
      BOOST_CHECK_EQUAL (c2.comparisons,3);
      BOOST_CHECK_EQUAL (c2.swaps,3);
   }

   // io
   {
      counted_operations c;

      std::cout << c << "\n";
   }
}

// Local variables:
// flycheck-clang-language-standard: "c++14"
// End:
