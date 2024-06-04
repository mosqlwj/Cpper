//
// Created by liwenjie on 2024/6/3.
//
/*
 * @description: flatten model
 */
#ifndef NDB_FLAT_MODEL_H
#define NDB_FLAT_MODEL_H

#include <vector>

#include "object.h"

class Primitive;
namespace ndb {

    class FlatModel : public Object {
    public:
        // sort
    private:
        std::vector<Primitive*> flat_model_;
    };
}
#endif//NDB_FLAT_MODEL_H
