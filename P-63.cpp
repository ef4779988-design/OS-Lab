#include <iostream>
#include <thread>
#include <shared_mutex>

using namespace std;

shared_mutex rw_mtx;
int shared_data = 42;

void reader() {
    shared_lock<shared_mutex> r_lock(rw_mtx);
    cout << "Read data: " << shared_data << "\n";
}

void writer() {
    unique_lock<shared_mutex> w_lock(rw_mtx);
    shared_data = 100;
    cout << "Data updated to 100\n";
}

int main() {
    thread t1(reader);
    thread t2(writer);
    thread t3(reader);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}