#ifndef PAIR_HPP
# define PAIR_HPP

# include "Vec.hpp"

/*
* @brief Data structure combining 2 vectors and thir distance
* to each other
*
* These are used to store every combination of vectors and their
* distance from another. By storing them in a std::vector<Pair>
* and sorting it the closest distances can be found easily
*/
typedef struct s_pair {
	double  dist;
	Vec     a;
	Vec     b;
} Pair;

bool operator<( const Pair& lhs, const Pair& rhs );
bool operator>( const Pair& lhs, const Pair& rhs );

#endif // ! PAIR_HPP
