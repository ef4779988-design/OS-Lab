#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex mtxA, mtxB;

void thread1() {
    lock_guard<mutex> lockA(mtxA);
    this_thread::sleep_for(chrono::milliseconds(50));
    lock_guard<mutex> lockB(mtxB);
}

void thread2() {
    lock_guard<mutex> lockB(mtxB);
    this_thread::sleep_for(chrono::milliseconds(50));
    lock_guard<mutex> lockA(mtxA);
}

int main() {
    thread t1(thread1);
    thread t2(thread2);

    t1.join();
    t2.join();
    return 0;
}