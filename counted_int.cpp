#include <iostream>

#include "counted_int.hpp"

void
counted_int::
print_counted_operations ()
{
   std::cout << "constructions: " << constructions << "\n";
   std::cout << "assignments: " << assignments << "\n";
   std::cout << "copies: " << copies << "\n";
   std::cout << "accesses: " << copies << "\n";
   std::cout << "destructions: " << destructions << "\n";
   std::cout << "comparisons: " << comparisons << "\n";
   std::cout << "swaps: " << swaps << "\n";
}

long long int counted_int::constructions = 0;
long long int counted_int::assignments = 0;
long long int counted_int::copies = 0;
long long int counted_int::destructions = 0;
long long int counted_int::accesses = 0;
long long int counted_int::comparisons = 0;
long long int counted_int::swaps = 0;

// Local variables:
// flycheck-clang-language-standard: "c++14"
// End:
