#define BOOST_TEST_MODULE examples
#include <boost/test/unit_test.hpp>

#include <iostream>

#include <algorithm>
#include <iterator>
#include <vector>

#include "counted_int.hpp"

#include "counted_operations_io.hpp"

BOOST_AUTO_TEST_CASE (std_vector_complexity_all)
{
   std::cout << "initial state ------------------------\n";

   std::cout << counted_int::counts () << "\n";

   {
      std::cout << "creating a vector via std::initializer_list of int ------------------------\n";

      counted_int::reset ();

      std::vector<counted_int> v { 0, 1, 2, 3, 4, 5, 6, 7 };

      std::cout << "v.size: " << v.size () << "\n";
      std::cout << counted_int::counts () << "\n";
   }

   {
      std::cout << "creating a vector via std::vector<counted_int>::push_back ------------------------\n";

      counted_int::reset ();

      std::vector<counted_int> v;
      for (int i = 0; i < 8; ++i)
      {
         v.push_back (i);
      }

      std::cout << "v.size: " << v.size () << "\n";
      std::cout << counted_int::counts () << "\n";
   }

   {
      std::cout << "creating a vector via std::vector<counted_int>::emplace_back ------------------------\n";

      counted_int::reset ();

      std::vector<counted_int> v;
      for (int i = 0; i < 8; ++i)
      {
         v.emplace_back (i);
      }

      std::cout << "v.size: " << v.size () << "\n";
      std::cout << counted_int::counts () << "\n";
   }

   {
      std::cout << "sorting a vector via std::vector<counted_int>, discounting creating the vector ------------------------\n";

      counted_int::reset ();

      std::vector<counted_int> v;
      for (int i = 0; i < 8; ++i)
      {
         v.emplace_back (i);
      }

      counted_int::reset ();

      std::sort (std::begin (v),std::end (v));

      std::cout << "v.size: " << v.size () << "\n";
      std::cout << counted_int::counts () << "\n";
   }

   {
      counted_int::reset ();

      const int v_size = 8;
      std::vector<counted_int> v;

      {
         v.reserve (v_size);
         for (int i = 0; i < v_size; ++i)
         {
            v.emplace_back (i);
         }
      }

      std::cout << "sorting a vector> ------------------------\n";

      counted_int::reset ();

      std::sort (std::begin (v),std::end (v));

      std::cout << "v.size: " << v.size () << "\n";
      std::cout << counted_int::counts () << "\n";

      std::cout << "failing find on a vector ------------------------\n";

      counted_int::reset ();

      auto v_i = std::find (std::begin (v),std::end (v),counted_int (v_size + 1));
      BOOST_CHECK (v_i == v.end ());

      std::cout << "v.size: " << v.size () << "\n";
      std::cout << counted_int::counts () << "\n";

      std::cout << "succeeding find on a vector ---------------------\n";

      counted_int::reset ();

      v_i = std::find (std::begin (v),std::end (v),counted_int (v_size / 2));
      BOOST_CHECK (v_i != v.end ());

      std::cout << "v.size: " << v.size () << "\n";
      std::cout << counted_int::counts () << "\n";

      std::cout << "failing search on a sorted vector ---------------------\n";

      counted_int::reset ();

      v_i = std::lower_bound (std::begin (v),std::end (v),counted_int (v_size + 1));
      BOOST_CHECK (v_i == v.end ());

      std::cout << "v.size: " << v.size () << "\n";
      std::cout << counted_int::counts () << "\n";

      std::cout << "succeeding search on a sorted vector ---------------------\n";

      counted_int::reset ();

      v_i = std::lower_bound (std::begin (v),std::end (v),counted_int (v_size / 2));
      BOOST_CHECK (v_i != v.end ());

      std::cout << "v.size: " << v.size () << "\n";
      std::cout << counted_int::counts () << "\n";
   }
}

// Local variables:
// flycheck-clang-language-standard: "c++14"
// End:
