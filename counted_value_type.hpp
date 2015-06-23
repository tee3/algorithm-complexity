#ifndef counted_value_type_hpp
#define counted_value_type_hpp

#include <utility>

#include "counted_operations.hpp"

template<typename T = int>
class counted_value_type
{
public:
   counted_value_type (const T v) :
      v_ (v)
   {
      ++counts_.constructions;
   }

   counted_value_type (const counted_value_type & rhs) :
      v_ (rhs.v_)
   {
      ++counts_.copies;
   }

   counted_value_type &
   operator= (const counted_value_type & rhs)
   {
      ++counts_.assignments;

      v_ = rhs.v_;

      return *this;
   }

   operator T () const
   {
      ++counts_.accesses;

      return v_;
   }

   ~counted_value_type ()
   {
      ++counts_.destructions;
   }

   bool
   operator== (const counted_value_type & rhs) const
   {
      ++counts_.comparisons;

      return v_ == rhs.v_;
   }

   bool
   operator< (const counted_value_type & rhs) const
   {
      ++counts_.comparisons;

      return v_ < rhs.v_;
   }

   bool
   operator!= (const counted_value_type & rhs) const
   {
      return !(*this == rhs);
   }

   bool
   operator<= (const counted_value_type & rhs) const
   {
      return !(rhs < *this);
   }

   bool
   operator> (const counted_value_type & rhs) const
   {
      return rhs < *this;
   }

   bool
   operator>= (const counted_value_type & rhs) const
   {
      return !(*this < rhs);
   }

   friend
   void
   swap (counted_value_type & lhs, counted_value_type & rhs)
   {
      ++counts_.swaps;

      std::swap (lhs.v_,rhs.v_);
   }

   static
   const counted_operations &
   counts ()
   {
      return counts_;
   }

   static
   void
   reset ()
   {
      counts_.reset ();
   }

private:
   static
   counted_operations counts_;

   T v_;
};

// Local variables:
// flycheck-clang-language-standard: "c++14"
// End:

#endif
