#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;
condition_variable cv;
int arrival_count = 0;
const int num_threads = 2;

void custom_barrier() {
    unique_lock<mutex> lock(mtx);
    arrival_count++;
    if (arrival_count >= num_threads) {
        arrival_count = 0;
        cv.notify_all();  
    } else {
        cv.wait(lock, [] { return arrival_count == 0; });
    }
}

void worker(int id) {
    cout << "Worker " << id << " reached phase 1.\n";
    custom_barrier();
    cout << "Worker " << id << " proceeding to phase 2.\n";
}

int main() {
    thread t1(worker, 1);
    thread t2(worker, 2);

    t1.join();
    t2.join();
    return 0;
}