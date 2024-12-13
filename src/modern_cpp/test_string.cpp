#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <cassert>
#include <iostream>
#include <string>
#include <regex>

using namespace  std;
TEST_CASE("test string case01") {
    string str = "abc";
    assert(str.length() == 3);
    assert(str < "xyz");
    assert(str.substr(0, 1) == "a");
    assert(str[1] == 'b');
    assert(str.find("1") == string::npos);
    assert(str + "d" == "abcd");
}

TEST_CASE("test string case02") {

    auto str = "std string"s;
    assert(str.length() > 0);
    assert("time"s.size() == 4);
}

TEST_CASE("test string case03") {
    auto str = R"(nier:automata)";

    auto str1 = R"(char""'')";
    auto str2 = R"(\r\n\t\")";
    auto str3 = R"(\\\$)";
    auto str4 = "\\\\\\$";

    auto str5 = R"==(R"(xxx)")==";

    cout << str1 << endl;
    cout << str2 << endl;
    cout << str3 << endl;
    cout << str4 << endl;
    cout << str5 << endl;
}

TEST_CASE("test string case04") {
    assert(stoi("42") == 42);
    assert(stol("253") == 253L);
    assert(stod("2.0") == 2.0);

    assert(to_string(1984) == "1984");
}

class my_string_view final {
private:
    const char* m_data = nullptr;
    size_t m_size = 0;
public:
    my_string_view() = default;
    ~my_string_view() = default;

    my_string_view(const string& str)
        : m_data(str.data()), m_size(str.size()) {
    }
public:
    size_t size() const {
        return m_size;
    }
    const char* data() const {
        return m_data;
    }
};

TEST_CASE("test string case05") {
    string str1 = "abc";
    my_string_view sv(str1);
    cout << sv.data() << endl;
}