//
// Created by liwenjie on 2025/3/15.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
#include <format>
#include <thread>
#include <mutex>
#include <future>
#include <cmath>
#include <list>
#include <numeric>

TEST_CASE("Test Concurrent 001") {

    std::cout << std::format("Hello concurrent program!") << std::endl;
}


void hello() {
    std::cout << "hello world!" << std::endl;
}

TEST_CASE("Test Concurrent 002") {
    std::thread t{hello};
    t.join();
}

TEST_CASE("Test Concurrent 003") {
    auto n = std::thread::hardware_concurrency();
    std::cout << std::format("hardware_concurrency: {}", n) << std::endl;
}

TEST_CASE("Test Concurrent 004") {
    std::thread t{[]() { std::cout << "Test Concurrent 004" << std::endl; }};
    t.join();
}

// 函数对象

struct func{
    int& m_i;
    func(int& i) : m_i{i} {}

    void operator()(int n) const {
        for (auto j = 0; j <= n; ++j) {
            m_i += j;
        }
    }
};

TEST_CASE("Test Concurrent 005") {
    int n = 0;
    std::thread t{func{n}, 100};
    t.join();
    std::cout << std::format("n: {}", n) << std::endl;
    // CHECK(n == 5050);
}


// RAII

void f2() {
    throw std::runtime_error("test f2()");
}

class thread_guard {
    std::thread& t;
    public:
        explicit thread_guard(std::thread& t_) : t{t_} {}
        ~thread_guard() {
            std::puts("~thread_guard");
            if (t.joinable()) {
                t.join();
            }
        }
        thread_guard(thread_guard const&) = delete;
        thread_guard& operator=(thread_guard const&) = delete;
};

void f() {
    int n = 0;
    std::thread t{func{n}, 100};
    thread_guard g{t};
    f2();
}

TEST_CASE("Test Concurrent 006") {
    try {
        f();
    } catch (const std::exception& e) {
        std::cout << std::format("{}", e.what()) << std::endl;
    }

    // f();
}

// test std::this_thread()
TEST_CASE("Test Concurrent 007") {
    std::cout << std::this_thread::get_id() << std::endl;

    std::thread t{[]() {
        std::cout << std::this_thread::get_id() << std::endl;
    }};

    t.join();
    // f();
}

using namespace std::chrono_literals;

TEST_CASE("Test Concurrent 008") {

//    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::this_thread::sleep_for(3s);
}

TEST_CASE("Test Concurrent 009") {
    // 获取当前时间点
    auto now = std::chrono::system_clock::now();

    // 设置要等待的时间点为当前时间点之后的5秒
    auto wakeup_time = now + 5s;

    // 输出当前时间
    auto now_time = std::chrono::system_clock::to_time_t(now);
    std::cout << "Current time:\t\t" << std::put_time(std::localtime(&now_time), "%H:%M:%S") << std::endl;

    // 输出等待的时间点
    auto wakeup_time_time = std::chrono::system_clock::to_time_t(wakeup_time);
    std::cout << "Waiting until:\t\t" << std::put_time(std::localtime(&wakeup_time_time), "%H:%M:%S") << std::endl;

    // 等待到指定的时间点
    std::this_thread::sleep_until(wakeup_time);

    // 输出等待结束后的时间
    now = std::chrono::system_clock::now();
    now_time = std::chrono::system_clock::to_time_t(now);
    std::cout << "Time after waiting:\t" << std::put_time(std::localtime(&now_time), "%H:%M:%S") << std::endl;
}

TEST_CASE("Test Concurrent 010") {
    std::thread t{[]() {
        std::cout << std::this_thread::get_id() << std::endl;
    }};

    std::cout << t.joinable() << std::endl;

    std::thread t2{std::move(t)};
    std::cout << t.joinable() << std::endl;
    std::cout << t2.joinable() << std::endl;
//    t.join();
    t2.join();

}

TEST_CASE("Test Concurrent 011") {
    std::thread t;
    std::cout << t.joinable() << std::endl;

    std::thread t2{[]() {}};

    t = std::move(t2);
    std::cout << t.joinable() << std::endl;
    std::cout << t2.joinable() << std::endl;
    t.join();
//    t2.join();

}

// call once

void init() {
    std::cout << "Do Something" << std::endl;
}

void worker(std::once_flag &flag) {
    std::call_once(flag, init);
}

TEST_CASE("Test Concurrent 012")  {
    std::once_flag flag;
    std::thread t1(worker, std::ref(flag));
    std::thread t2(worker, std::ref(flag));

    t1.join();
    t2.join();
}

// C++20 jthread
TEST_CASE("Test Concurrent 013")  {

}


/////////////////////////////////////////////////////////////////////////
// async
static constexpr int MAX = 10e8;
static double sum = 0;

void worker100(int min, int max) {
    for (int i = min; i < max; ++i) {
        sum += sqrt(i);
    }
}

TEST_CASE("Test Concurrent 100")  {
    sum = 0;
    auto f1 = std::async(std::launch::async, worker100, 0,MAX);
    std::cout << "Async task triggered" << std::endl;
    f1.wait();
    std::cout << "Async task finished, sum is:" << sum << std::endl;
}

// async lambda
TEST_CASE("Test Concurrent 101")  {
    double result = 0;
    auto f1 = std::async(std::launch::async, [&result]() {
        for (int i = 0; i < MAX; ++i) {
            result += sqrt(i);
        }
    });
    f1.wait();
    std::cout << "Async task finished, sum is:" << result << std::endl;
}

class Worker {
public:
    Worker(int min, int max) : min_{min}, max_{max}, result_{0} {}

    void Work() {
        for (int i = min_; i < max_; ++i) {
            result_ += sqrt(i);
        }
//        return result_;
    }

    double GetResult() {
        return result_;
    }

private:
    int min_;
    int max_;
    double result_;
};

TEST_CASE("Test Concurrent 102")  {
    Worker w(0, MAX);
    auto f1 = std::async(std::launch::async, &Worker::Work, &w);
    std::cout << "Async task triggered" << std::endl;
    f1.wait();
    std::cout << "Async task finished, sum is:" << w.GetResult() << std::endl;
}

// 共享数据

std::mutex mtx_200;
void f_200() {
    mtx_200.lock();
    std::cout << std::this_thread::get_id() << "\n";
    mtx_200.unlock();
}

void f_201() {
    std::lock_guard<std::mutex> lc{mtx_200};
    std::cout << std::this_thread::get_id() << "\n";

}

TEST_CASE("Test Concurrent 200") {
    std::vector<std::thread> threads;
    for (int i = 0; i < 100; ++i) {
//        threads.emplace_back(f_200);
        threads.emplace_back(f_201);
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

std::mutex m;

void add_to_list(int n, std::list<int>& list) {
    std::vector<int> numbers(n + 1);
    std::iota(numbers.begin(), numbers.end(), 0);
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);

    {
        std::lock_guard<std::mutex> lc{ m };
        list.push_back(sum);
    }
}
void print_list(const std::list<int>& list) {
    std::lock_guard<std::mutex> lc{ m };
    for (const auto& i : list) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

TEST_CASE("Test Concurrent 201") {
    std::list<int> list;
    for (int i = 0; i < 10; ++i) {
        std::thread t1{ add_to_list,i,std::ref(list) };
        std::thread t2{ add_to_list,i,std::ref(list) };
        std::thread t3{ print_list,std::cref(list) };
        std::thread t4{ print_list,std::cref(list) };
        t1.join();
        t2.join();
        t3.join();
        t4.join();
    }
}

//////////////////////////////

//std::mutex mtx_202;

//void thread_function(int id) {
//    if (mtx_202.try_lock()) {
//        std::cout << "线程：" << id << " 获得锁" << std::endl;
//        // 临界区代码
//        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 模拟临界区操作
//
//
//        mtx_202.unlock(); // 解锁
//
//        std::cout << "线程：" << id << " 释放锁" << std::endl;
//    } else {
//        std::cout << "线程：" << id << " 尝试获得锁失败" << std::endl;
//    }
//}

std::mutex mtx_202;
std::mutex cout_mtx;  // 专门用于保护cout输出

void thread_function(int id) {
    bool locked = mtx_202.try_lock();

    {
        std::lock_guard<std::mutex> cout_guard(cout_mtx);
        if (locked) {
            std::cout << "线程：" << id << " 获得锁" << std::endl;
        } else {
            std::cout << "线程：" << id << " 尝试获得锁失败" << std::endl;
            return;
        }
    }

    try {
        // 临界区代码
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    catch (...) {
        mtx_202.unlock();
        throw;
    }

    mtx_202.unlock();

    std::lock_guard<std::mutex> cout_guard(cout_mtx);
    std::cout << "线程：" << id << " 释放锁" << std::endl;
}

TEST_CASE("Test Concurrent 202") {
    std::thread t1{ thread_function, 1};
    std::thread t2{ thread_function, 2};
    t1.join();
    t2.join();
}

///////////////////////////////////////////////
int global_counter = 0;
thread_local int thread_local_counter = 0;

void print_counters(){
    std::cout << "global：" << global_counter++ << '\n';
    std::cout << "thread_local：" << thread_local_counter++ << '\n';
}

TEST_CASE("Test Concurrent 203") {
    std::thread{ print_counters }.join();
    std::thread{ print_counters }.join();
}
