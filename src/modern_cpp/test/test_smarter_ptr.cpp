#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


#include <iostream>
#include <cassert>
#include <memory>
using namespace std;

template<class T, class... Args>
std::unique_ptr<T> my_make_unique(Args&&... args) {
        return  std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

TEST_CASE("Testing Modern CPP") {
    cout << "Hello" << endl;
}

TEST_CASE("Test SP Case01") {

    unique_ptr<int> ptr1(new int(10));
    assert(*ptr1 == 10);
    assert(ptr1 != nullptr);

    unique_ptr<string> ptr2(new string("hello"));
    assert(*ptr2 == "hello");
    assert(ptr2->size() == 5);

    //ptr1++;
    //ptr2 += 2;

    //unique_ptr<int> ptr3;
    //*ptr3 = 42;

    auto ptr3 = make_unique<int>(42);
    assert(ptr3 && *ptr3 == 42);

    auto ptr4 = make_unique<string>("god of war");
    assert(!ptr4->empty());

    auto ptr5 = my_make_unique<long>(100L);
    assert(*ptr5 == 100);
}

TEST_CASE("Test SP Case02"){

    auto ptr1 = make_unique<int>(42);
    assert(ptr1 && *ptr1 == 42);

    auto ptr2 = std::move(ptr1);
    assert(!ptr1 && ptr2);
}

TEST_CASE("Test SP Case04"){

    shared_ptr<int> ptr1(new int(10));
    assert(*ptr1);

    shared_ptr<string> ptr2(new string("Hello"));
    assert(*ptr2 == "Hello");

    auto ptr3 = make_shared<int>(42);
    assert(ptr3 && *ptr3 == 42);

    auto ptr4 = make_shared<string>("zela");
    assert(!ptr4->empty());

}

TEST_CASE("Test SP Case04") {
//    using namespace std;

    auto ptr1 = make_shared<int>(42);
    assert(ptr1 && ptr1.unique() );

    auto ptr2 = ptr1;
    assert(ptr1 && ptr2);

    assert(ptr1 == ptr2);
    assert(!ptr1.unique() && ptr1.use_count() == 2);
    assert(!ptr2.unique() && ptr2.use_count() == 2);

    auto sp1 = std::make_shared<int>(5);
    std::cout << std::boolalpha;
    std::cout << "sp1.unique() == " << sp1.unique() << '\n';

    std::shared_ptr<int> sp2 = sp1;
    std::cout << "sp1.unique() == " << sp1.unique() << '\n';
}

class Node final {
public:
    using this_type = Node;
    using shared_type = std::weak_ptr<this_type>;

public:
    shared_type  next;

public:
    Node() = default;
    ~Node() {
        std::cout << "node dtor" << std::endl;
    }
};

TEST_CASE("Test SP Case05") {
    auto n1 = make_shared<Node>();
    auto n2 = make_shared<Node>();

    assert(n1.use_count() == 1);
    assert(n2.use_count() == 1);

    n1->next = n2;
    n2->next = n1;

    assert(n1.use_count() == 1);
    assert(n2.use_count() == 1);

    if (!n1->next.expired()) {
        auto ptr = n1->next.lock();
        assert(ptr == n2);
    }
}