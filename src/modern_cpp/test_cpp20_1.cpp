//
// Created by liwenjie on 2024/12/25.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
#include <concepts>
#include <format>
#include <string>
#include <span>
#include <map>
#include <unordered_map>
#include <iterator>
#include <algorithm>
#include <set>
#include <deque>
#include <ranges>

using namespace std;
constexpr auto use_string() {
//    std::string str{"hello"};
//    return str;
    return "hello";
}


template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template <typename T>
requires Numeric<T>

T args(const T& arg) {
    return arg + 42;
}

TEST_CASE("Test CPP20 001")  {
    std::cout << std::format("value:{}", args(20));
}

/**
 * 测试span
 */
template <typename T>
void pspan(std::span<T> s) {
    std::cout << std::format("size: {}\n", s.size()) ;
    std::cout << std::format("size bytes: {}\n", s.size_bytes());
    for (auto& e : s) {
        e += 2; // span修改引用元素
        std::cout << std::format("{} ", e);
    }
    std::cout << std::endl;
}
TEST_CASE("Test CPP20 002")  {
    int a[] = {1, 2, 3, 4};
    pspan<int>(a);
}

/**
* 测试结构化绑定
*/

struct div_result {
    long quotient;
    long remainder;
};

div_result div(long a, long b) {
    div_result r;
    r.quotient = a / b;
    r.remainder =  a % b;
    return r;
}

std::map<std::string, int> m = {{"one", 1}, {"two", 2}, {"three", 3}};

TEST_CASE("Test CPP20 003")  {
    auto [q, r] = div(47, 5);
    std::cout << std::format("q:{}, r:{}\n", q, r);

    for (auto& [k, v] : m) {
        std::cout << std::format("key:{}, value:{}\n", k, v);
    }
}

/**
* 测试constexpr-if
*/

template <typename T>
auto get_value(const T v) {
    if constexpr(std::is_pointer_v<T>) {
        return *v;
    } else {
        return v;
    }
}

TEST_CASE("Test CPP20 004")  {
    int x{10};
    int* y{&x};
    std::cout << std::format("value:{}\n", get_value(x));
    std::cout << std::format("value:{}\n", get_value(y));
}

/**
* 测试模板函数参数推到
*/

template <typename T1, typename T2>

std::string f(const T1 a, const T2 b) {
    return std::format("{} {}", typeid(a).name(), typeid(b).name());
}

TEST_CASE("Test CPP20 005")  {
    std::cout << std::format("{}", f(1, 2));
}

/**
* 测试vector quick delete
*/
void printc(auto& r) {
    std::cout << std::format("1 size is {}\n", r.size());
    for (auto& e : r) {
        std::cout << std::format("{} ", e);
    }
    cout << "\n";
}

template<typename T>
void quick_delete(T& v, size_t idx) {
    if (idx < v.size()) {
        v[idx] = std::move(v.back());
        std::cout << std::format("2 size is {} \n", v.size());
        v.pop_back();
        std::cout << std::format("3 size is {} \n", v.size());
    }
}

TEST_CASE("Test CPP20 006")  {
    vector v{ 12, 196, 47, 38, 19 };
    printc(v);
    quick_delete(v, 2);
    printc(v);
}

/**
* 测试map
*/

struct BigString {
    string s_;
    BigString(const string& s) : s_(s) {
        std::cout << std::format("BigString is constructed:{}\n", s) << std::endl;
    }
};

using Mymap = std::map<std::string, BigString>;

void printm(const Mymap& m) {
    for (const auto& [k, v] : m) {
        std::cout << std::format("key:{}, value:{}\n", k, v.s_);
    }
    std::cout << "\n";
}

TEST_CASE("Test CPP20 007")  {
    Mymap m;

    m.try_emplace("Miles", "Trumpet");
    m.try_emplace("Hendrix", "Guitar");
    m.try_emplace("Krupa", "Drums");
    m.try_emplace("Zappa", "Guitar");
    m.try_emplace("Liszt", "Piano");
    printm(m);

    cout << "\n";
    cout << "emplace(Hendrix)\n";
    m.emplace("Hendrix", "Singer");
    cout << "try_emplace(Zappa)\n";
    m.try_emplace("Zappa", "Composer");
    printm(m);
}

/**
* 测试unordered_map keys
*/

struct Coord {
    int x;
    int y;
};

using Coordmap = std::unordered_map<Coord, int>;

bool operator==(const Coord& lhs, const Coord& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}



namespace std {
    template<>
    struct hash<Coord> {
        size_t operator()(const Coord& c) const {
            return static_cast<size_t>(c.x)
                   + static_cast<size_t>(c.y);
        }
    };
}

void print_Coordmap(const Coordmap& m) {
    for (const auto& [k, v] : m) {
        std::cout << std::format("key:({} {}), value:{}\n", k.x, k.y, v);
    }
    std::cout << "\n";
}

TEST_CASE("Test CPP20 008")  {
    Coordmap m {
            { {0, 0}, 1 },
            { {0, 1}, 2 },
            { {2, 1}, 3 }
    };
    print_Coordmap(m);
}

/**
* 测试 set word
*/

using input_it = std::istream_iterator<std::string>;

TEST_CASE("Test CPP20 009")  {
    input_it it{std::cin};
    input_it end{};
    std::set<std::string> words;
    std::copy(it, end, std::inserter(words, words.begin()));

    for (const auto& w : words) {
        std::cout << std::format("{} ", w);
    }
    std::cout << std::endl;
}

/**
 * 测试rpn
 */

class RPN {

public:
    // process an operand/operator
    double op(const string & s) {
        if(is_numeric(s)) {
            double v{stod(s, nullptr)};
            deq_.push_front(v);
            return v;
        }
        else return optor(s);
    }

    // empty the stack
    void clear() {
        deq_.clear();
    }

    // print the stack
    string get_stack_string() const {
        string s{};
        for(auto v : deq_) {
            s += format("{} ", v);
        }
        return s;
    }
private:
    std::pair<double, double> pop_get2() {
        if (deq_.size() < 2) return {zero_, zero_};
        double v1{ deq_.front() };
        deq_.pop_front();
        double v2{ deq_.front() };
        deq_.pop_front();
        return {v1, v2};
    }

    bool is_numeric(const std::string& s) {
        for (auto& e : s) {
            if (e != '.' && !std::isdigit(e)) return false;
        }
        return true;
    }

    double optor(const std::string& op) {
        std::unordered_map<std::string, double(*)(double, double)> opmap{
                {"+", [](double r, double l) { return r + l; }},
                {"-", [](double r, double l) { return r - l; }},
                {"*", [](double r, double l) { return r * l; }},
                {"/", [](double r, double l) { return r / l; }}
        };
        if (opmap.find(op) == opmap.end()) return zero_;

        auto [l, r] = pop_get2();
        if (op == "/" && r == zero_) {
            deq_.push_front(inf_);
        } else {
            deq_.push_front(opmap[op](l, r));
        }
        return deq_.front();
    }
private:

    std::deque<double> deq_;
    constexpr static double zero_{0.0};
    constexpr static double inf_{std::numeric_limits<double>::infinity()};
};


TEST_CASE("Test CPP20 010")  {
    RPN rpn;
    vector<string> opv = {"9", "6", "*", "2", "3", "*", "+"};
    for (auto o : opv) {
        rpn.op(o);
        auto stack_str = rpn.get_stack_string();
        cout << format("{}：{}\n", o, stack_str);
    }
}

/**
* 测试seq
*/

template<typename T>
class Seq {
public:
    Seq(T start, T end) : start_{start}, end_{end}  {}

    class iterator {
    public:
        using iterator_concept  = std::forward_iterator_tag;
        using iterator_category = std::forward_iterator_tag;
        using value_type        = std::remove_cv_t<T>;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        explicit iterator(T pos) : value_{pos} {}

        T operator*() { return value_; }
        iterator& operator++() {
            ++value_;
            return *this;
        }

        iterator operator++(T) {
            iterator temp = *this;
            ++*this;
            return temp;
        }

        bool operator!=(const iterator& other) const {
            return value_ != other.value_;
        }

        bool operator==(const iterator& other) const {
            return value_ == other.value_;
        }

    private:
        T value_;
    };

    ///////////////////////////////////////////
    iterator begin() const { return iterator{start_}; }
    iterator end() const { return iterator{end_}; }
private:
    T start_;
    T end_;
};

TEST_CASE("Test CPP20 011")  {
    Seq<int> seq{1, 10};

    for (auto o : seq) {
        cout << format("{}\n", o);
    }
}

TEST_CASE("Test CPP20 012")  {
//    Seq<int> seq{1, 10};
    std::vector<int> seq{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto [min, max] = ranges::minmax_element(seq);
    std::cout << std::format("min:{}, max:{}\n", *min, *max);
}

/**
* 测试iterator-adaptor
*/
void printc2(const auto& v, const std::string_view s = "") {
    if (s.size()) { std::cout << std::format("{}\n", s); }
    for (auto e : v) {
        std::cout << std::format("{} ", e);
    }
    std::cout << std::endl;
}

TEST_CASE("Test CPP20 013")  {
    deque<int> d1{1, 2, 3, 4, 5};
    deque<int> d2(d1.size());
    std::copy(d1.begin(), d1.end(), d2.begin());
    printc2(d1);
    printc2(d2, "d2 copy: ");

    std::copy(d1.begin(), d1.end(), std::back_inserter(d2));
    printc2(d2, "d2 back_inserter: ");

    std::copy(d1.begin(), d1.end(), std::ostream_iterator<int>(cout));
    std::cout << std::endl;

    std::vector<std::string> vs;
    std::copy(std::istream_iterator<std::string>(cin), std::istream_iterator<std::string>(), std::back_inserter(vs));
    printc2(vs, "vs from istream:");
}