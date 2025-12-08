#include "day08.hpp"

e_states getState( List *ta_list, List *tb_list ) {
    if (ta_list && ta_list == tb_list) {
        return BOTH_SAME;
    }
    else if (ta_list && !tb_list) {
        return TB_MISS;
    }
    else if (!ta_list && tb_list) {
        return TA_MISS;
    }
    else if (ta_list && tb_list) {
        return BOTH_DIFF;
    }
    return BOTH_MISS;
}
