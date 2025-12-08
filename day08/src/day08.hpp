#ifndef DAY08_HPP
# define DAY08_HPP

# include "Pair.hpp"
# include "Vec.hpp"
# include <vector>

typedef std::vector<Pair> PairVec;
typedef std::vector<Vec>::iterator Iter;
typedef std::list<Vec> List;
typedef List::iterator LIter;
typedef std::vector<List>::iterator VLIter;

enum e_states {
    TA_MISS,
    TB_MISS,
    BOTH_MISS,
    BOTH_SAME,
    BOTH_DIFF
};

#endif // ! DAY08_HPP
