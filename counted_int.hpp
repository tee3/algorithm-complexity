#ifndef counted_int_hpp
#define counted_int_hpp

#include <utility>

#include "counted_operations.hpp"

class counted_int
{
public:
   counted_int (const int v) :
      v_ (v)
   {
      ++counts_.constructions;
   }

   counted_int (const counted_int & rhs)
   {
      ++counts_.copies;

      v_ = rhs.v_;
   }

   counted_int &
   operator= (const counted_int & rhs)
   {
      ++counts_.assignments;

      v_ = rhs.v_;

      return *this;
   }

   operator int () const
   {
      ++counts_.accesses;

      return v_;
   }

   ~counted_int ()
   {
      ++counts_.destructions;
   }

   bool
   operator== (const counted_int & rhs) const
   {
      ++counts_.comparisons;

      return v_ == rhs.v_;
   }

   bool
   operator< (const counted_int & rhs) const
   {
      ++counts_.comparisons;

      return v_ < rhs.v_;
   }

   bool
   operator!= (const counted_int & rhs) const
   {
      return !(*this == rhs);
   }

   bool
   operator<= (const counted_int & rhs) const
   {
      return !(rhs < *this);
   }

   bool
   operator> (const counted_int & rhs) const
   {
      return rhs < *this;
   }

   bool
   operator>= (const counted_int & rhs) const
   {
      return !(*this < rhs);
   }

   friend
   void
   swap (counted_int & lhs, counted_int & rhs)
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

   int v_;
};

// Local variables:
// flycheck-clang-language-standard: "c++14"
// End:

#endif
