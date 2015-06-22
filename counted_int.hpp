#ifndef counted_int_hpp
#define counted_int_hpp

#include <utility>

class counted_int
{
public:
   counted_int (const int v) :
      v_ (v)
   {
      ++constructions;
   }

   counted_int (const counted_int & rhs)
   {
      ++copies;

      v_ = rhs.v_;
   }

   counted_int &
   operator= (const counted_int & rhs)
   {
      ++assignments;

      v_ = rhs.v_;

      return *this;
   }

   operator int () const
   {
      ++accesses;

      return v_;
   }

   ~counted_int ()
   {
      ++destructions;
   }

   bool
   operator== (const counted_int & rhs) const
   {
      ++comparisons;

      return v_ == rhs.v_;
   }

   bool
   operator< (const counted_int & rhs) const
   {
      ++comparisons;

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
      ++swaps;

      std::swap (lhs.v_,rhs.v_);
   }

   static
   void
   reset ()
   {
      constructions = 0;
      assignments = 0;
      copies = 0;
      destructions = 0;
      accesses = 0;
      comparisons = 0;
      swaps = 0;
   }

   static
   void
   print_counted_operations ();

private:
   static
   long long int constructions;
   static
   long long int assignments;
   static
   long long int copies;
   static
   long long int destructions;
   static
   long long int accesses;
   static
   long long int comparisons;
   static
   long long int swaps;

private:
   int v_;
};

// Local variables:
// flycheck-clang-language-standard: "c++14"
// End:

#endif
