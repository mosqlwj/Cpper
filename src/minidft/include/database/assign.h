#ifndef NDB_ASSIGN_H
#define NDB_ASSIGN_H

#include "object.h"


namespace ndb {
    class Net;

    class Assign : public Object{
    public:
        Assign(Net* left, Net* right) : Object(""), left_(left), right_(right) {}

        [[nodiscard]] auto GetLeft() const { return left_; }
        [[nodiscard]] auto GetRight() const { return right_; }

        bool IsAssign() override { return true; }
    private:
        Net* left_{nullptr};
        Net* right_{nullptr};
    };
}

#endif
