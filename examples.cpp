#define BOOST_TEST_MODULE examples
#include <boost/test/unit_test.hpp>

#include <iostream>

#include <algorithm>
#include <iterator>
#include <vector>

#include "counted_value_type.hpp"

#include "counted_operations_io.hpp"

BOOST_AUTO_TEST_CASE (std_vector_complexity_all)
{
   std::cout << "initial state ------------------------\n";

   std::cout << counted_value_type<>::counts () << "\n";

   {
      std::cout << "creating a vector via std::initializer_list of int ------------------------\n";

      counted_value_type<>::reset ();

      std::vector<counted_value_type<>> v { 0, 1, 2, 3, 4, 5, 6, 7 };

      std::cout << "v.size: " << v.size () << "\n";
      std::cout << counted_value_type<>::counts () << "\n";
   }

   {
      std::cout << "creating a vector via std::vector<counted_value_type<>>::push_back ------------------------\n";

      counted_value_type<>::reset ();

      std::vector<counted_value_type<>> v;
      for (int i = 0; i < 8; ++i)
      {
         v.push_back (i);
      }

      std::cout << "v.size: " << v.size () << "\n";
      std::cout << counted_value_type<>::counts () << "\n";
   }

   {
      std::cout << "creating a vector via std::vector<counted_value_type<>>::emplace_back ------------------------\n";

      counted_value_type<>::reset ();

      std::vector<counted_value_type<>> v;
      for (int i = 0; i < 8; ++i)
      {
         v.emplace_back (i);
      }

      std::cout << "v.size: " << v.size () << "\n";
      std::cout << counted_value_type<>::counts () << "\n";
   }

   {
      std::cout << "sorting a vector via std::vector<counted_value_type<>>, discounting creating the vector ------------------------\n";

      counted_value_type<>::reset ();

      std::vector<counted_value_type<>> v;
      for (int i = 0; i < 8; ++i)
      {
         v.emplace_back (i);
      }

      counted_value_type<>::reset ();

      std::sort (std::begin (v),std::end (v));

      std::cout << "v.size: " << v.size () << "\n";
      std::cout << counted_value_type<>::counts () << "\n";
   }

   {
      counted_value_type<>::reset ();

      const int v_size = 8;
      std::vector<counted_value_type<>> v;

      {
         v.reserve (v_size);
         for (int i = 0; i < v_size; ++i)
         {
            v.emplace_back (i);
         }
      }

      std::cout << "sorting a vector> ------------------------\n";

      counted_value_type<>::reset ();

      std::sort (std::begin (v),std::end (v));

      std::cout << "v.size: " << v.size () << "\n";
      std::cout << counted_value_type<>::counts () << "\n";

      std::cout << "failing find on a vector ------------------------\n";

      counted_value_type<>::reset ();

      auto v_i = std::find (std::begin (v),std::end (v),counted_value_type<> (v_size + 1));
      BOOST_CHECK (v_i == v.end ());

      std::cout << "v.size: " << v.size () << "\n";
      std::cout << counted_value_type<>::counts () << "\n";

      std::cout << "succeeding find on a vector ---------------------\n";

      counted_value_type<>::reset ();

      v_i = std::find (std::begin (v),std::end (v),counted_value_type<> (v_size / 2));
      BOOST_CHECK (v_i != v.end ());

      std::cout << "v.size: " << v.size () << "\n";
      std::cout << counted_value_type<>::counts () << "\n";

      std::cout << "failing search on a sorted vector ---------------------\n";

      counted_value_type<>::reset ();

      v_i = std::lower_bound (std::begin (v),std::end (v),counted_value_type<> (v_size + 1));
      BOOST_CHECK (v_i == v.end ());

      std::cout << "v.size: " << v.size () << "\n";
      std::cout << counted_value_type<>::counts () << "\n";

      std::cout << "succeeding search on a sorted vector ---------------------\n";

      counted_value_type<>::reset ();

      v_i = std::lower_bound (std::begin (v),std::end (v),counted_value_type<> (v_size / 2));
      BOOST_CHECK (v_i != v.end ());

      std::cout << "v.size: " << v.size () << "\n";
      std::cout << counted_value_type<>::counts () << "\n";
   }
}

// Local variables:
// flycheck-clang-language-standard: "c++14"
// End:
