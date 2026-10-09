#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

atomic<int> counter{0};

void atomic_worker() {
    for (int i = 0; i < 10000; ++i) {
        counter.fetch_add(1, memory_order_relaxed);
    }
}

int main() {
    thread t1(atomic_worker);
    thread t2(atomic_worker);

    t1.join();
    t2.join();

    cout << "Final Atomic Counter: " << counter << "\n";
    return 0;
}