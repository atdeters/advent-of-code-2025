#include "Pair.hpp"

bool operator<( const Pair& lhs, const Pair& rhs ) {
	return (lhs.dist < rhs.dist);
}

bool operator>( const Pair& lhs, const Pair& rhs ) {
	return (lhs.dist > rhs.dist);
}
