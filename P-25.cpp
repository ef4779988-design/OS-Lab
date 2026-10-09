#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex m1, m2;

void threadA() {
    m1.lock();
    cout << "Thread A locked Mutex 1, waiting for Mutex 2...\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    m2.lock();

    m1.unlock();
    m2.unlock();
}

void threadB() {
    m2.lock();
    cout << "Thread B locked Mutex 2, waiting for Mutex 1...\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    m1.lock();

    m1.unlock();
    m2.unlock();
}

int main() {
    thread t1(threadA);
    thread t2(threadB);

    t1.join();
    t2.join();

    return 0;
}