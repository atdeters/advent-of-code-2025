#ifndef VEC_HPP
# define VEC_HPP

# include <string>
# include <cmath>
# include <list>

/*
* @brief Data structure to store a mathematical vector
* using ints for its coordinates
*/
class Vec {
	private:
		int _x;
		int _y;
		int _z;

	public:
		// Constructors
		Vec();
		Vec( const std::string& s);

		// Getters
		int x() const;
		int y() const;
		int z() const;

		// Static Functions
		static double dist( Vec lhs, Vec rhs );
};

//################################################################################################//
//                                       OPERATOR OVERLOADS                                       //
//################################################################################################//
bool operator<( Vec lhs, Vec rhs );
bool operator==( Vec lhs, Vec rhs );
bool operator<( std::list<Vec> lhs, std::list<Vec> rhs );
bool operator>( std::list<Vec> lhs, std::list<Vec> rhs );

#endif // ! VEC_HPP
