#include <iostream>
#include <vector>
using namespace std;

class Samples {

public:
    Samples() : min_{0}, max_{1}, v_{min_, max_} {
        v_.reserve(8);
    } 

    int add(int i) {
        v_.push_back(i);
    }

    int min() const { return min_ ;}
    int max() const { return max_; }
private:
    int min_;
    int max_;
    std::vector<int> v_;
};
int main() {
    cout << "TestConst" << "\n";
    Samples s1;
    s1.add(3);
    cout << s1.max() << "\n";
    const Samples s2;
    // s2.add(3);
    return 0;
}