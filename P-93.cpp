#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void dummy_task() {
}

int main() {
    auto t0 = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) {
        thread t(dummy_task);
        t.join();
    }
    auto t1 = chrono::high_resolution_clock::now();
    chrono::duration<double> t_pthread = t1 - t0;

    cout << "Time taken for 10,000 pthreads creation and joining: " << t_pthread.count() << " seconds[cite: 40].\n";
    return 0;
}