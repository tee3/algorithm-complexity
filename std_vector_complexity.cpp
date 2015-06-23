#define BOOST_TEST_MODULE std_vector_complexity
#include <boost/test/unit_test.hpp>

#include <iostream>

#include <algorithm>
#include <iterator>
#include <random>
#include <vector>

#include <utility>

#include <cmath>

#include <cassert>

#include "counted_int.hpp"

/// @brief If defined, the contents of the data structure and the
/// results for each iteration will be printed.
///
/// This can be enabled for small N.
#undef MEASURE_COMPLEXITY_DEBUG_PRINT

/// @brief If defined, the counts for each iterations will be checked
/// against the criteria.
///
/// This can be enabled for small N.
#undef MEASURE_COMPLEXITY_CHECK_ITERATION

#if defined (MEASURE_COMPLEXITY_DEBUG_PRINT)
/// @brief Extremely basic printer for a vector of counted integers.
std::ostream &
operator<< (std::ostream & os, const std::vector<counted_int> & v)
{
   std::cout << v.size () << "\n";
   for (const auto & vi : v)
   {
      std::cout << vi << " ";
   }

   return os;
}
#endif

BOOST_AUTO_TEST_CASE (std_vector_complexity_all)
{
   std::cout << "initial state ------------------------\n";

   counted_int::print_counted_operations ();

   {
      std::cout << "creating a vector via std::initializer_list of int ------------------------\n";

      counted_int::reset ();

      std::vector<counted_int> v { 0, 1, 2, 3, 4, 5, 6, 7 };

      std::cout << "v.size: " << v.size () << "\n";
      counted_int::print_counted_operations ();
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
      counted_int::print_counted_operations ();
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
      counted_int::print_counted_operations ();
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
      counted_int::print_counted_operations ();
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
      counted_int::print_counted_operations ();

      std::cout << "failing find on a vector ------------------------\n";

      counted_int::reset ();

      auto v_i = std::find (std::begin (v),std::end (v),counted_int (v_size + 1));
      BOOST_CHECK (v_i == v.end ());

      std::cout << "v.size: " << v.size () << "\n";
      counted_int::print_counted_operations ();

      std::cout << "succeeding find on a vector ---------------------\n";

      counted_int::reset ();

      v_i = std::find (std::begin (v),std::end (v),counted_int (v_size / 2));
      BOOST_CHECK (v_i != v.end ());

      std::cout << "v.size: " << v.size () << "\n";
      counted_int::print_counted_operations ();

      std::cout << "failing search on a sorted vector ---------------------\n";

      counted_int::reset ();

      v_i = std::lower_bound (std::begin (v),std::end (v),counted_int (v_size + 1));
      BOOST_CHECK (v_i == v.end ());

      std::cout << "v.size: " << v.size () << "\n";
      counted_int::print_counted_operations ();

      std::cout << "succeeding search on a sorted vector ---------------------\n";

      counted_int::reset ();

      v_i = std::lower_bound (std::begin (v),std::end (v),counted_int (v_size / 2));
      BOOST_CHECK (v_i != v.end ());

      std::cout << "v.size: " << v.size () << "\n";
      counted_int::print_counted_operations ();
   }

   // actual complexity measurement
   {
      using n_container_type = std::vector<std::vector<counted_int>::size_type>;

      n_container_type ns;
      for (n_container_type::size_type i = 0; i < 10; ++i)
      {
         ns.emplace_back (n_container_type::value_type (1) << i);
      }
      const int iterations = 1000;

      auto urng = std::mt19937 { std::random_device {} () };

      std::vector<counted_int> v;

      for (const auto & n : ns)
      {
         v.reserve (n);
         for (auto i = v.size (); i < n; ++i)
         {
            v.push_back (std::vector<counted_int>::value_type (i));
         }

         assert (v.size () == n);

         const unsigned long long int n_log2_n =
            std::ceil (v.size () *
                       std::log2 (static_cast<long double> (v.size ())));

         long long int constructions = 0;
         long long int assignments = 0;
         long long int copies = 0;
         long long int destructions = 0;
         long long int accesses = 0;
         long long int comparisons = 0;
         long long int swaps = 0;

         for (int i = 0; i < iterations; ++i)
         {
            std::shuffle (std::begin (v),std::end (v),urng);

#if defined (MEASURE_COMPLEXITY_DEBUG_PRINT)
            std::cout << v << "\n";
#endif

            counted_int::reset ();

            std::sort (std::begin (v),std::end (v));

#if defined (MEASURE_COMPLEXITY_DEBUG_PRINT)
            std::cout << v << "\n";
#endif

#if defined (MEASURE_COMPLEXITY_DEBUG_PRINT)
            std::cout << "(v.size, (n * log_2 (n)): (" << v.size () << ", " << n_log2_n << ")\n";
            counted_int::print_counted_operations ();
#endif

            constructions += counted_int::constructions;
            assignments += counted_int::assignments;
            copies += counted_int::copies;
            destructions += counted_int::destructions;
            accesses += counted_int::accesses;
            comparisons += counted_int::comparisons;
            swaps += counted_int::swaps;

#if defined (MEASURE_COMPLEXITY_CHECK_ITERATION)
            // @todo this may fail for any individual run, but succeeds on average
            BOOST_CHECK_EQUAL (counted_int::constructions,0);
            BOOST_CHECK_EQUAL (counted_int::assignments,0);
            BOOST_CHECK_EQUAL (counted_int::copies,0);
            BOOST_CHECK_EQUAL (counted_int::destructions,0);
            BOOST_CHECK_EQUAL (counted_int::accesses,0);
            BOOST_CHECK_LE (counted_int::comparisons,n_log2_n);
            BOOST_CHECK_LE (counted_int::swaps,n_log2_n);
#endif
         }

         // calculate averages
         constructions =
            std::ceil (constructions /
                       static_cast<long double> (iterations));
         assignments =
            std::ceil (assignments /
                       static_cast<long double> (iterations));
         copies =
            std::ceil (copies /
                       static_cast<long double> (iterations));
         destructions =
            std::ceil (destructions /
                       static_cast<long double> (iterations));
         accesses =
            std::ceil (accesses /
                       static_cast<long double> (iterations));
         comparisons =
            std::ceil (comparisons /
                       static_cast<long double> (iterations));
         swaps =
            std::ceil (swaps /
                       static_cast<long double> (iterations));

         std::cout << "(v.size, iterations, (n * log_2 (n)): (" << v.size () << ", " << iterations << ", " << n_log2_n << ")\n";
         std::cout << "constructions: " << constructions << "\n";
         std::cout << "assignments: " << assignments << "\n";
         std::cout << "copies: " << copies << "\n";
         std::cout << "accesses: " << copies << "\n";
         std::cout << "destructions: " << destructions << "\n";
         std::cout << "comparisons: " << comparisons << "\n";
         std::cout << "swaps: " << swaps << "\n";

         // This should succeed on average.
         BOOST_CHECK_EQUAL (constructions,0);
         BOOST_CHECK_EQUAL (assignments,0);
         BOOST_CHECK_EQUAL (copies,0);
         BOOST_CHECK_EQUAL (destructions,0);
         BOOST_CHECK_EQUAL (accesses,0);
         BOOST_CHECK_LE (comparisons,n_log2_n);
         BOOST_CHECK_LE (swaps,n_log2_n);
      }
   }
}

// Local variables:
// flycheck-clang-language-standard: "c++14"
// End:
