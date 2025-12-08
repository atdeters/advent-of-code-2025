#include "Vec.hpp"
#include <sstream>
#include <stdlib.h>

//################################################################################################//
//                                          CONSTRUCTORS                                          //
//################################################################################################//
Vec::Vec() : _x(0), _y(0), _z(0) {};
Vec::Vec( const std::string& s) : _x(0), _y(0), _z(0) {
    std::stringstream ss(s);
    std::string buff;
    size_t count = 0;
    while (std::getline(ss, buff, ',')) {
        if (count == 0) {
            _x = std::atoi(buff.c_str());
        }
        else if (count == 1) {
            _y = std::atoi(buff.c_str());
        }
        else if (count == 2) {
            _z = std::atoi(buff.c_str());
        }
        else {
            break;
        }
        count++;
    }
};

//################################################################################################//
//                                            GETTERS                                             //
//################################################################################################//
int Vec::x() const { return _x; };
int Vec::y() const { return _y; };
int Vec::z() const { return _z; };

//################################################################################################//
//                                    STATIC MEMBER FUNCTIONS                                     //
//################################################################################################//
double Vec::dist( Vec lhs, Vec rhs ) {
    double a = pow(lhs._x - rhs._x, 2);
    double b = pow(lhs._y - rhs._y, 2);
    double c = pow(lhs._z - rhs._z, 2);
    return (std::sqrt(a+b+c));
};

//################################################################################################//
//                                       OPERATOR OVERLOADS                                       //
//################################################################################################//
bool operator<( Vec lhs, Vec rhs ) {
    Vec root("0,0,0");
	return (Vec::dist(root, lhs) < Vec::dist(root, rhs));
}

bool operator==( Vec lhs, Vec rhs ) {
	return (lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z());
}

bool operator<( std::list<Vec> lhs, std::list<Vec> rhs ) {
	return ( lhs.size() < rhs.size() );
}

bool operator>( std::list<Vec> lhs, std::list<Vec> rhs ) {
	return ( lhs.size() > rhs.size() );
}
