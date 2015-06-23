#ifndef _complexity_hpp
#define _complexity_hpp

#include <string>

#include <cmath>

inline
unsigned long long int
O_1 (unsigned long long int /* n */)
{
   return static_cast<unsigned long long int> (1);
}

inline
unsigned long long int
O_n (unsigned long long int n)
{
   return n;
}

inline
unsigned long long int
O_n_log2_n (unsigned long long int n)
{
   return std::ceil (n * std::log2 (static_cast<long double> (n)));
}

inline
unsigned long long int
O_n_2 (unsigned long long int n)
{
   return n * n;
}

inline
unsigned long long int
O_n_3 (unsigned long long int n)
{
   return n * n * n;
}

/// @todo this is pretty broken
std::string
complexity_string (unsigned long long int n,
                   unsigned long long int count)
{
   if (count < O_n (n))
   {
      return "O(1)";
   }
   else if (count < O_n_log2_n (n))
   {
      return "O(n)";
   }
   else if (count < O_n_2 (n))
   {
      return "O(n*log2(n))";
   }
   else if (count < O_n_3 (n))
   {
      return "O(n^2)";
   }
   else if (count == O_n_3 (n))
   {
      return "O(n^3)";
   }

   return "O(?)";
}

#endif
