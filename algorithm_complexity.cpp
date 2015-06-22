#include <iostream>

#include <utility>

#include <cassert>

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

long long int counted_int::constructions = 0;
long long int counted_int::assignments = 0;
long long int counted_int::copies = 0;
long long int counted_int::destructions = 0;
long long int counted_int::accesses = 0;
long long int counted_int::comparisons = 0;
long long int counted_int::swaps = 0;

int
main ()
{
   // mininal tests
   {
      std::cout << "initial state ------------------------\n";

      counted_int::print_counted_operations ();
   
      std::cout << "minimal test ------------------------\n";

      counted_int::reset ();

      {
         counted_int c0 (0);
         counted_int c1 = 1;
         counted_int c2 (c1);
         counted_int c3 = c2;

         bool b0 = c0 == c1;
         assert (!b0);
         bool b1 = c0 != c1;
         assert (b1);
         bool b2 = c0 < c1;
         assert (b2);
         bool b3 = c0 > c1;
         assert (!b3);
         bool b4 = c0 <= c1;
         assert (b4);
         bool b5 = c0 >= c1;
         assert (!b5);

         using std::swap;
         swap (c2,c3);
      }

      counted_int::print_counted_operations ();
   
      std::cout << "reset ------------------------\n";

      counted_int::reset ();
   
      counted_int::print_counted_operations ();
   }
   
   return 0;
}

// Local variables:
// flycheck-clang-language-standard: "c++14"
// End:
