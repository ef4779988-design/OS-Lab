#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

using namespace std;

atomic<bool> keep_running(true);
atomic<long long> counter(0);

void counting_worker() {
    while (keep_running) {
        counter++;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

int main() {
    thread t(counting_worker);
    
    cout << "Kernel threads running. Counter is active while other tasks might block.\n";
    this_thread::sleep_for(chrono::milliseconds(100));
    
    keep_running = false;
    t.join();
    
    cout << "Final Counter Value: " << counter << "\n";
    return 0;
}