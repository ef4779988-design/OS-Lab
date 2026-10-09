#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

using namespace std;

mutex queue_mtx;
condition_variable cv;
queue<function<void()>> tasks;
bool stop = false;

void worker_loop() {
    while (true) {
        unique_lock<mutex> lock(queue_mtx);
        cv.wait(lock, [] { return stop || !tasks.empty(); });
        if (stop && tasks.empty()) return;
        auto task = move(tasks.front());
        tasks.pop();
        lock.unlock();
        task();
    }
}

int main() {
    thread worker(worker_loop);
    {
        lock_guard<mutex> lock(queue_mtx);
        tasks.push([] { cout << "Task executed by thread pool worker.\n"; });
    }
    cv.notify_one();

    {
        lock_guard<mutex> lock(queue_mtx);
        stop = true;
    }
    cv.notify_all();
    worker.join();
    return 0;
}