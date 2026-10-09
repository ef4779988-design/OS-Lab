#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;
condition_variable cv;
bool latch_released = false;

void worker() {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [] { return latch_released; });
    cout << "Worker running benchmarks after latch release.\n";
}

int main() {
    thread t(worker);
    cout << "Preparing shared memory...\n";
    
    {
        lock_guard<mutex> lock(mtx);
        latch_released = true;
    }
    cv.notify_all();

    t.join();
    return 0;
}