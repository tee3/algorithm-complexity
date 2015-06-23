#ifndef counted_operations_io_hpp
#define counted_operations_io_hpp

#include <iosfwd>

#include "counted_operations.hpp"

std::ostream &
operator<< (std::ostream & os, const counted_operations & rhs);

// Local variables:
// flycheck-clang-language-standard: "c++14"
// End:

#endif
