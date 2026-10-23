#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void busy(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

int main() {
    int work[] = {100, 400, 100, 400};
    thread t0(busy, work[0]);
    thread t1(busy, work[1]);
    thread t2(busy, work[2]);
    thread t3(busy, work[3]);

    t0.join();
    t1.join();
    t2.join();
    t3.join();

    cout << "Unequal workloads completed.\n";
    return 0;
}