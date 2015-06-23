#define BOOST_TEST_MODULE algorithm_complexity
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
#include "counted_operations.hpp"
#include "counted_operations_io.hpp"

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

         counted_operations counts;

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
            std::cout << counted_int::counts () << "\n";
#endif

            counted_operations snapshot = counted_int::counts ();

            counts += snapshot;

#if defined (MEASURE_COMPLEXITY_CHECK_ITERATION)
            // @todo this may fail for any individual run, but succeeds on average
            BOOST_CHECK_EQUAL (snapshot.constructions,0);
            BOOST_CHECK_EQUAL (snapshot.assignments,0);
            BOOST_CHECK_EQUAL (snapshot.copies,0);
            BOOST_CHECK_EQUAL (snapshot.destructions,0);
            BOOST_CHECK_EQUAL (snapshot.accesses,0);
            BOOST_CHECK_LE (snapshot.comparisons,n_log2_n);
            BOOST_CHECK_LE (snapshot.swaps,n_log2_n);
#endif
         }

         // calculate averages
         counts.constructions =
            std::ceil (counts.constructions /
                       static_cast<long double> (iterations));
         counts.assignments =
            std::ceil (counts.assignments /
                       static_cast<long double> (iterations));
         counts.copies =
            std::ceil (counts.copies /
                       static_cast<long double> (iterations));
         counts.destructions =
            std::ceil (counts.destructions /
                       static_cast<long double> (iterations));
         counts.accesses =
            std::ceil (counts.accesses /
                       static_cast<long double> (iterations));
         counts.comparisons =
            std::ceil (counts.comparisons /
                       static_cast<long double> (iterations));
         counts.swaps =
            std::ceil (counts.swaps /
                       static_cast<long double> (iterations));

         std::cout << "(v.size, iterations, (n * log_2 (n)): (" << v.size () << ", " << iterations << ", " << n_log2_n << ")\n";
         std::cout << counts << "\n";

         // This should succeed on average.
         BOOST_CHECK_EQUAL (counts.constructions,0);
         BOOST_CHECK_EQUAL (counts.assignments,0);
         BOOST_CHECK_EQUAL (counts.copies,0);
         BOOST_CHECK_EQUAL (counts.destructions,0);
         BOOST_CHECK_EQUAL (counts.accesses,0);
         BOOST_CHECK_LE (counts.comparisons,n_log2_n);
         BOOST_CHECK_LE (counts.swaps,n_log2_n);
      }
   }
}

// Local variables:
// flycheck-clang-language-standard: "c++14"
// End:
