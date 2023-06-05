#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class ScendingSequence {

public:
    using value_type = int;


private:
    using storage_t = std::vector<value_type>;
    storage_t seq_;

public:
    using size_type = storage_t::size_type; 
    void insert(value_type x) {
        seq_.insert(std::lower_bound(seq_.begin(), seq_.end(), x), x);
    }   

    [[nodiscard]] value_type operator [] (size_type idx) const noexcept {
        return seq_[idx];
    }
    [[nodiscard]] size_type size() const noexcept {
        return seq_.size();
    }

    [[nodiscard]] auto begin() const noexcept { return seq_.begin(); }

    [[nodiscard]] auto end() const noexcept { return seq_.end(); }
};
int main() {
   
    ScendingSequence s;  // s.seq_:  
    s.insert(7);           // s.seq_: 7
    s.insert(2);           // s.seq_: 27
    s.insert(4);           // s.seq_: 247
    s.insert(9);           // s.seq_: 2479
    s.insert(5);           // s.seq_: 24579
    std::cout << s[3];     // prints 7
    for (auto x : s) {
        std::cout << x <<' ';  // 2 4 5 7 9
    }
    // use type aliases
    ScendingSequence::value_type x = 1;
    ScendingSequence::size_type  n = 2;
    // ScendingSequence::storage_t
    return 0;
}