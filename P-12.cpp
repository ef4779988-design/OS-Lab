#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int counter = 0;
mutex m;

void add() {
    for (int i = 0; i < 1000; ++i) {
        lock_guard<mutex> lock(m);
        ++counter;
    }
}

int main() {
    thread t1(add);
    thread t2(add);

    t1.join();
    t2.join();

    cout << "Final counter: " << counter << "\n";
    return 0;
}