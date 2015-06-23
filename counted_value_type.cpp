#include <iostream>

#include "counted_value_type.hpp"
#include "counted_operations.hpp"

// note other types will need to be defined as required.
template<> counted_operations counted_value_type<int>::counts_;

// Local variables:
// flycheck-clang-language-standard: "c++14"
// End:
