#include <iostream>

using namespace std;

int main() {
    auto s1 = "seven of "s;
    auto s2 = s1;
    s1 += " nine";
    cout << s1 << "\n";
    cout << s2 << "\n";
    auto s3 = "uni"s + "matrix"s;
    cout << s3 << "\n";
    return 0;
}