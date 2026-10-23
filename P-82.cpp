#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

using namespace std;

const int K = 5;
int B[K];
int in = 0, out = 0, count_val = 0;
mutex m;
condition_variable notFull, notEmpty;

void producer(int n) {
    for (int i = 0; i < n; ++i) {
        unique_lock<mutex> lock(m);
        notFull.wait(lock, [] { return count_val < K; });
        B[in] = i;
        in = (in + 1) % K;
        count_val++;
        notEmpty.notify_one();
    }
    unique_lock<mutex> lock(m);
    notFull.wait(lock, [] { return count_val < K; });
    B[in] = -1;
    in = (in + 1) % K;
    count_val++;
    notEmpty.notify_one();
}

void consumer() {
    while (true) {
        unique_lock<mutex> lock(m);
        notEmpty.wait(lock, [] { return count_val > 0; });
        int x = B[out];
        out = (out + 1) % K;
        count_val--;
        notFull.notify_one();
        if (x == -1) break;
    }
}

int main() {
    thread p(producer, 10);
    thread c(consumer);
    p.join();
    c.join();
    cout << "Producer-Consumer finished.\n";
    return 0;
}