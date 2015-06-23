#ifndef counted_operations_hpp
#define counted_operations_hpp

struct counted_operations
{
   typedef unsigned long long int counter_type;

   counted_operations () :
      counted_operations (0)
   {
   }

   explicit
   counted_operations (counter_type n) :
      constructions (n),
      assignments (n),
      copies (n),
      destructions (n),
      accesses (n),
      comparisons (n),
      swaps (n)
   {
   }

   counted_operations (counter_type constructions__,
                       counter_type assignments__,
                       counter_type copies__,
                       counter_type destructions__,
                       counter_type accesses__,
                       counter_type comparisons__,
                       counter_type swaps__) :
      constructions (constructions__),
      assignments (assignments__),
      copies (copies__),
      destructions (destructions__),
      accesses (accesses__),
      comparisons (comparisons__),
      swaps (swaps__)
   {
   }

   counted_operations &
   operator+= (const counted_operations & rhs)
   {
      constructions += rhs.constructions;
      assignments += rhs.assignments;
      copies += rhs.copies;
      destructions += rhs.destructions;
      accesses += rhs.accesses;
      comparisons += rhs.comparisons;
      swaps += rhs.swaps;

      return *this;
   }

   counted_operations
   operator+ (const counted_operations & rhs)
   {
      counted_operations tmp (*this);
      tmp += rhs;
      return tmp;
   }

   void
   reset ()
   {
      *this = counted_operations ();
   }

   counter_type constructions;
   counter_type assignments;
   counter_type copies;
   counter_type destructions;
   counter_type accesses;
   counter_type comparisons;
   counter_type swaps;
};

// Local variables:
// flycheck-clang-language-standard: "c++14"
// End:

#endif
