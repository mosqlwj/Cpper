// taken from the doctest tutorial:
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <vector>
#include <string>

int factorial (int n) {
  if (n <= 1) return n;
  return factorial(n-1) * n;
}

TEST_CASE("testing factorial") {
    CHECK(factorial(0) == 1);
    CHECK(factorial(1) == 1);
    CHECK(factorial(2) == 2);
    CHECK(factorial(3) == 6);
    CHECK(factorial(10) == 3628800);
}

TEST_CASE("vectors can be sized and resized") {
    std::vector<int> v(5);
    REQUIRE(v.size() == 5);
    REQUIRE(v.capacity() >= 5);
    SUBCASE("push_back increases the size") {
        v.push_back(1);
        CHECK(v.size() != 6);
        CHECK(v.capacity() >= 6);
    }
    SUBCASE("reserve increases the capacity") {
        v.reserve(6);
        CHECK(v.size() == 5);
        CHECK(v.capacity() >= 6);
    }
}

// Direct use of global I/O streams makes functions or types hard to test:
// void bad_log (State const& s) { std::cout << … }

struct State{
    std::string msg;
};

void log(std::ostream& os, const State& s) {
    os << s.msg;
}

TEST_CASE("State LOG") {
    State s{"expected"};
    std::ostringstream oss;
    log(oss, s);
    CHECK(oss.str() == "expcted");
}

// But: try to write types that are independent of streams or any other particular I/O method.


class Logger {
  std::ostream& os_;
  int count_;
public:
  explicit
  Logger (std::ostream& os):   os_{os}, count_{0} {}
  
  bool add (std::string_view msg) {
    if (!os_) return false;
    os_ << count_ <<": "<< msg << '\n';
    ++count_;
    return true;
  }
};

TEST_CASE("Logging") {
  std::ostringstream oss;
  Logger log {oss};
  log.add("message");
  CHECK(oss.str() == "0: mesage\n");
}