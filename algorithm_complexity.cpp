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

#include "complexity.hpp"
#include "counted_int.hpp"
#include "counted_operations.hpp"
#include "counted_operations_io.hpp"

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

BOOST_AUTO_TEST_CASE (algorithm_complexity_all)
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

         counted_operations expected_counts (0,
                                             0,
                                             0,
                                             0,
                                             0,
                                             O_n_log2_n (v.size ()),
                                             O_n_log2_n (v.size ()));

         counted_operations counts;

         for (int i = 0; i < iterations; ++i)
         {
            std::shuffle (std::begin (v),std::end (v),urng);

            counted_int::reset ();

            std::sort (std::begin (v),std::end (v));

            counts += counted_int::counts ();
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

         std::cout << "(v.size, iterations): (" << v.size () << ", " << iterations << ")\n";
         std::cout << counts << "\n";
         std::cout << "expected counts:\n";
         std::cout << expected_counts << "\n";

         // This should succeed on average.
         BOOST_CHECK_EQUAL (counts.constructions,
                            expected_counts.constructions);
         BOOST_CHECK_EQUAL (counts.assignments,
                            expected_counts.assignments);
         BOOST_CHECK_EQUAL (counts.copies,
                            expected_counts.copies);
         BOOST_CHECK_EQUAL (counts.destructions,
                            expected_counts.destructions);
         BOOST_CHECK_EQUAL (counts.accesses,
                            expected_counts.accesses);
         BOOST_CHECK_LE (counts.comparisons,
                         expected_counts.comparisons);
         BOOST_CHECK_LE (counts.swaps,
                         expected_counts.swaps);
      }
   }
}

// Local variables:
// flycheck-clang-language-standard: "c++14"
// End:
