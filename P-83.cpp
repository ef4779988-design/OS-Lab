#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex m1, m2;
condition_variable cv1, cv2;
queue<int> Q1, Q2;

void stage1(int n) {
    for (int i = 0; i < n; ++i) {
        unique_lock<mutex> lock(m1);
        Q1.push(i);
        cv1.notify_one();
    }
    unique_lock<mutex> lock(m1);
    Q1.push(-1);
    cv1.notify_one();
}

void stage2() {
    while (true) {
        unique_lock<mutex> lock(m1);
        cv1.wait(lock, [] { return !Q1.empty(); });
        int x = Q1.front();
        Q1.pop();
        lock.unlock();

        unique_lock<mutex> lock2(m2);
        if (x == -1) {
            Q2.push(-1);
            cv2.notify_one();
            break;
        }
        Q2.push(x * x);
        cv2.notify_one();
    }
}

void stage3() {
    long long s = 0;
    while (true) {
        unique_lock<mutex> lock(m2);
        cv2.wait(lock, [] { return !Q2.empty(); });
        int y = Q2.front();
        Q2.pop();
        lock.unlock();

        if (y == -1) break;
        s += y;
    }
    cout << "Pipeline Sum: " << s << "\n";
}

int main() {
    thread t1(stage1, 5);
    thread t2(stage2);
    thread t3(stage3);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}