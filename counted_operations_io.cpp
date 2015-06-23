#include <iostream>

#include "counted_operations.hpp"

std::ostream &
operator<< (std::ostream & os, const counted_operations & rhs)
{
   os <<
      "(" << "\n" <<
      "   constructions: " << rhs.constructions << "\n" <<
      "   assignments: " << rhs.assignments << "\n" <<
      "   copies: " << rhs.copies << "\n" <<
      "   accesses: " << rhs.copies << "\n" <<
      "   destructions: " << rhs.destructions << "\n" <<
      "   comparisons: " << rhs.comparisons << "\n" <<
      "   swaps: " << rhs.swaps << "\n"
      ")";

   return os;
}

// Local variables:
// flycheck-clang-language-standard: "c++14"
// End:
