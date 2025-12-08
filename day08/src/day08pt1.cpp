#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <sys/types.h>
#include <vector>
#include <list>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>

#define CONNECTS 10

class Vec {
	private:
		int _x;
		int _y;
		int _z;
	public:
		// Init
		Vec() : _x(0), _y(0), _z(0) {};
		Vec (std::string s) : _x(0), _y(0), _z(0) {
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
		// Getters
		int x() const { return _x; };
		int y() const { return _y; };
		int z() const { return _z; };
		// Static Functions
		static double dist( Vec lhs, Vec rhs ) {
			double a = pow(lhs._x - rhs._x, 2);
			double b = pow(lhs._y - rhs._y, 2);
			double c = pow(lhs._z - rhs._z, 2);

			return (std::sqrt(a+b+c));
		};
};

std::ostream& operator<<( std::ostream& t_out, const Vec& t_vec ) {
	t_out << "x: " << t_vec.x() << "y: " << t_vec.y() << "z: " <<  t_vec.z();
	return t_out;
}

typedef struct s_distPair {
	double	dist;
	Vec		a;
	Vec		b;
} distPair;

bool operator<( distPair lhs, distPair rhs ) {
	return (lhs.dist < rhs.dist);
}

bool operator>( distPair lhs, distPair rhs ) {
	return (lhs.dist > rhs.dist);
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

typedef std::vector<distPair>::iterator DIter;
typedef std::vector<Vec>::iterator Iter;

int main( int ac, char **av ) {

	// File handling etc
	if (ac > 2) {
		std::cerr << "Usage: ./day08pt1 <puzzle-input>" << std::endl;
		return 1;
	}
	std::fstream file;
	if (ac == 2) {
		file.open(av[1]);
	}
	else {
		file.open("/dev/fd/0");
	}
	if (!file.is_open()) {
		std::cerr << "Could not open file: " << av[1] << std::endl;
		return 1;
	}

	// Get a vector of Vec
	std::string buffer;
	std::vector<Vec> coor;
	while (std::getline(file, buffer)) {
		coor.push_back(buffer);
	}
	if (ac != 2) {
		file.close();
	}

	// SORT BY DISTANCE TO EACH OTHER
	Vec a;
	Vec b;
	std::vector<distPair> pairs;
	for (Iter it = coor.begin(); it != coor.end(); it++) {
		for (Iter jt = it + 1; jt != coor.end(); jt++) {
			double dist = Vec::dist(*it, *jt);
			distPair tmp;
			tmp.dist = dist;
			tmp.a = *it;
			tmp.b = *jt;
			pairs.push_back(tmp);
		}
	}

	std::sort(pairs.rbegin(), pairs.rend());

	// Make a vector of lists
	std::vector<std::list<Vec> > connections;
	typedef std::list<Vec> List;
	typedef List::iterator LIter;
	typedef std::vector<List>::iterator VLIter;


	for (size_t i = 0; i < CONNECTS; i++) {

		// Get the values of the current pair
		Vec ta = (*pairs.rbegin()).a;
		Vec tb = (*pairs.rbegin()).b;

		// Check existing lists for them
		/*
		bool stop = false;
		for (VLIter it = connections.begin(); it != connections.end(); it++) {
			for (LIter jt = (*it).begin(); jt != (*it).end(); jt++) {
				// Check if Vec is in the list and the other isnt
				if (*jt == ta) {
					(*it).push_back(tb);
					stop = true;
					break;
				}
				else if (*jt == tb) {
					(*it).push_back(ta);
					stop = true;
					break;
				}
			}
			if (stop) {
				break;
			}
		}
		if (stop) {
			pairs.pop_back();
			continue;
		}
		*/

		// Create new list if all new values
		std::list<Vec> tmp;
		tmp.push_back(ta);
		tmp.push_back(tb);
		connections.push_back(tmp);

		// Remove pair to get to the next
		pairs.pop_back();
	}

	// TODO: Sort connections by size of its lists
	std::sort(connections.rbegin(), connections.rend());
	size_t count = 0;
	long result = 1;
	for (VLIter it = connections.begin(); it != connections.end(); it++) {
		std::cout << "List Nr: " << count << std::endl;
		for (LIter jt = (*it).begin(); jt != (*it).end(); jt++) {
			std::cout << *jt << std::endl;
		}
		if (count < 3) {
			result *= (*it).size();
		}
		count++;
	}

	std::cout << "The result is \e[1m" << result << "\e[0m" << std::endl;
	return 0;
}
