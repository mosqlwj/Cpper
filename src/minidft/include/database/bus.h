#ifndef NDB_BUS_H
#define NDB_BUS_H

#include "object.h"

namespace ndb {

    class Bus : public Object{
    public:
        Bus(const std::string& name, int left, int right) : Object(name) {
            if (left_index_ >= right_index_) {
                SetDownto(true);
                SetLength(left_index_ - right_index_ + 1);
            } else {
                SetDownto(false);
                SetLength(right_index_ - left_index_ + 1);
            }
        }

        bool IsBus() override { return true; }

        void SetDownto(bool is_downto) { is_downto_ = is_downto; }
        bool IsDownto() { return is_downto_; }

        void SetLength(int length) { length_ = length; }
        int GetLength() { return length_; }

        int GetLeftIndex() { return left_index_; }
        int GetRightIndex() { return right_index_; }

        bool InRange(int index) {
            if (is_downto_) {
                return index <= left_index_ && index >= right_index_;
            } else {
                return index >= left_index_ && index <= right_index_;
            }
        }

    private:
        bool is_downto_{true}; // [8:0], [0:8]
        int length_{0};
        int left_index_{-1};
        int right_index_{-1};
    };
}

#endif