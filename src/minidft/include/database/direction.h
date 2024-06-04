//
// Created by liwenjie on 2024/6/3.
//
/*
 * @description: pin/port direction
 */
#ifndef NDB_DIRECTION_H
#define NDB_DIRECTION_H

namespace ndb {

    enum class Direction {
        INPUT,
        OUTPUT,
        INOUT,
        UNKNOWN
    };
}

#endif//NDB_DIRECTION_H
