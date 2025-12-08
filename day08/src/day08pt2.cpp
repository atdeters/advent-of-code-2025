#include <fstream>
#include <iostream>
#include <algorithm>
#include "day08.hpp"

int main( int ac, char **av ) {

	// File handling etc
	if (ac > 2) {
		std::cerr << "Usage: ./day08pt1 <puzzle-input>" << std::endl;
		return 1;
	}
	std::ifstream file;
    std::istream* in = &std::cin;
	if (ac == 2) {
		file.open(av[1]);
        if (!file.is_open()) {
    		std::cerr << "Could not open file: " << av[1] << std::endl;
	    	return 1;
        }
        in = &file;
	}

	// Get a vector of Vec
	std::string buffer;
	std::vector<Vec> coor;
	while (std::getline(*in, buffer)) {
		coor.push_back(buffer);
	}
	if (ac != 2) {
		file.close();
	}

	// SORT BY DISTANCE TO EACH OTHER
	Vec a;
	Vec b;
	std::vector<Pair> pairs;
	for (Iter it = coor.begin(); it != coor.end(); it++) {
		for (Iter jt = it + 1; jt != coor.end(); jt++) {
			double dist = Vec::dist(*it, *jt);
			Pair tmp;
			tmp.dist = dist;
			tmp.a = *it;
			tmp.b = *jt;
			pairs.push_back(tmp);
		}
	}

	std::sort(pairs.rbegin(), pairs.rend());
	std::vector<std::list<Vec> > connections;

	while (true) {

		// Get the vecs of the current pair
        if (pairs.empty()) {
            break;
        }
		Vec ta = (*pairs.rbegin()).a;
		Vec tb = (*pairs.rbegin()).b;

        // Try finding lists containing the two values
        List *ta_list = NULL;
        List *tb_list = NULL;
        for (VLIter it = connections.begin(); it != connections.end(); it++) {

            // Look in every list
            List currLst = *it;
            List *addr = &(*it);

            for (LIter jt = currLst.begin(); jt != currLst.end(); jt++) {
                if (*jt == ta) {
                    ta_list = addr;
                }
                if (*jt == tb) {
                    tb_list = addr;
                }
            }
        }

        // Case: Both in same list [Do nothing]
        if (ta_list && ta_list == tb_list) {}
        // Didn't find tb but ta [Add tb to ta_list]
        else if (ta_list && !tb_list) {
            (*ta_list).push_back(tb);
        }
        // Didn't find ta but tb [Add ta to tb_list]
        else if (!ta_list && tb_list) {
            (*tb_list).push_back(ta);
        }
        // Found both but in different lists [Merge them into one]
        else if (ta_list && tb_list) {
            (*ta_list).merge(*tb_list);
            // Remove empty tb_list
            std::vector<std::list<Vec> > tmp;
            for (VLIter it = connections.begin(); it != connections.end(); it++) {
                if (!(*it).empty()) {
                    tmp.push_back(*it);
                }
            }
            connections = tmp;
        }
        // Both not found [Start new list]
        else {
            std::list<Vec> tmp;
            tmp.push_back(ta);
            tmp.push_back(tb);
            connections.push_back(tmp);
        }
        if (!pairs.empty()) {
            pairs.pop_back();
        }
	    std::sort(connections.rbegin(), connections.rend());
        if ((*connections.begin()).size() == coor.size()) {
            std::cout << "The multiplication of the x-coordinates of the last two junction boxes equals \e[1m" << ta.x() * tb.x() << "\e[0m" << std::endl;
            break;
        }
	}
}
