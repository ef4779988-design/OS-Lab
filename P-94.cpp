#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void worker(int id) {
    cout << "Thread ID: " << id << "\n";
    this_thread::sleep_for(chrono::seconds(5));
}

int main() {
    thread t1(worker, 1);
    thread t2(worker, 2);
    t1.join();
    t2.join();
    return 0;
}