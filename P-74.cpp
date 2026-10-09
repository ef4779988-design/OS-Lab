#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

using namespace std;

atomic<bool> stop_requested_flag(false);

void worker() {
    while (!stop_requested_flag.load()) {
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << "Stop requested, worker cleaning up.\n";
}

int main() {
    thread my_thread(worker);
    this_thread::sleep_for(chrono::milliseconds(200));
    
    stop_requested_flag.store(true);
    my_thread.join();
    
    return 0;
}