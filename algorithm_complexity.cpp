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

/// @brief Returns the averaged counts for the algorithm passed within
/// the function.
template<typename Setup, typename Algorithm, typename Container>
counted_operations
test_algorithm_complexity (Container c,
                           Setup setup,
                           Algorithm algorithm,
                           int iterations)
{
   counted_operations ave;
   counted_operations min;
   counted_operations max;

   for (int i = 0; i != iterations; ++i)
   {
      setup (c);

      counted_int::reset ();

      algorithm (c);

      counted_operations snapshot = counted_int::counts ();

      ave += snapshot;

      if (snapshot.constructions > max.constructions)
      {
         max.constructions = snapshot.constructions;
      }
      if (snapshot.assignments > max.assignments)
      {
         max.assignments = snapshot.assignments;
      }
      if (snapshot.copies > max.copies)
      {
         max.copies = snapshot.copies;
      }
      if (snapshot.destructions > max.destructions)
      {
         max.destructions = snapshot.destructions;
      }
      if (snapshot.accesses > max.accesses)
      {
         max.accesses = snapshot.accesses;
      }
      if (snapshot.comparisons > max.comparisons)
      {
         max.comparisons = snapshot.comparisons;
      }
      if (snapshot.swaps > max.swaps)
      {
         max.swaps = snapshot.swaps;
      }
   }

   // calculate averages
   ave.constructions =
      std::ceil (ave.constructions / static_cast<long double> (iterations));
   ave.assignments =
      std::ceil (ave.assignments / static_cast<long double> (iterations));
   ave.copies =
      std::ceil (ave.copies / static_cast<long double> (iterations));
   ave.destructions =
      std::ceil (ave.destructions / static_cast<long double> (iterations));
   ave.accesses =
      std::ceil (ave.accesses / static_cast<long double> (iterations));
   ave.comparisons =
      std::ceil (ave.comparisons / static_cast<long double> (iterations));
   ave.swaps =
      std::ceil (ave.swaps / static_cast<long double> (iterations));

   return ave;
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

         counted_operations counts =
            test_algorithm_complexity (v,
                                       [&] (auto & v)
                                       {
                                          std::shuffle (std::begin (v),std::end (v),urng);
                                       },
                                       [&] (auto & v)
                                       {
                                          std::sort (std::begin (v),std::end (v));
                                       },
                                       iterations);

         std::cout << "(v.size, iterations): (" << v.size () << ", " << iterations << ")\n";
         std::cout << "counts:\n";
         std::cout << counts << "\n";
         std::cout << "expected counts:\n";
         std::cout << expected_counts << "\n";
         std::cout << "complexity estimates\n";
         std::cout << "(\n";
         std::cout << "   constructions: " << complexity_string (v.size (),counts.constructions) << "\n";
         std::cout << "   assignments: " << complexity_string (v.size (),counts.assignments) << "\n";
         std::cout << "   copies: " << complexity_string (v.size (),counts.copies) << "\n";
         std::cout << "   destructions: " << complexity_string (v.size (),counts.destructions) << "\n";
         std::cout << "   accesses: " << complexity_string (v.size (),counts.accesses) << "\n";
         std::cout << "   comparisons: " << complexity_string (v.size (),counts.comparisons) << "\n";
         std::cout << "  swaps: " << complexity_string (v.size (),counts.swaps) << "\n";
         std::cout << ")\n";

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
