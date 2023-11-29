#include <atomic>
#include <thread>
#include <iostream>
#include <cassert>

using namespace std;

std::atomic<bool> x, y, z;


void func_1() {

    x.store(true, std::memory_order_relaxed);
}

void func_2() 
{
    y.store(true, std::memory_order_relaxed);
}

void func_3() {

    while (!y.load(std::memory_order_relaxed))
        ;
    
    if (x.load(std::memory_order_relaxed)) {
        z = true;
    }

    assert(z);
}

int main() 
{
    for (int i = 0; i < 10000; ++i) {
        x = false;
        y = false;
        z = false;
        std::thread thread_1(func_1);
        std::thread thread_2(func_2);
        std::thread thread_3(func_3);
        thread_1.join();
        thread_2.join();
        thread_3.join();
    }

}
