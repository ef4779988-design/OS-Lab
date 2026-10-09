#include <iostream>
#include <thread>
#include <vector>

using namespace std;

int counter = 0;

void increment_routine() {
    for (int i = 0; i < 10000; ++i) {
        counter++;
    }
}

int main() {
    thread t1(increment_routine);
    thread t2(increment_routine);

    t1.join();
    t2.join();

    cout << "Final Unsafe Counter: " << counter << "\n";
    return 0;
}