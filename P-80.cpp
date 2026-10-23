#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;
long long dot = 0;
vector<int> A = {1, 2, 3, 4, 5, 6};
vector<int> B = {10, 20, 30, 40, 50, 60};

void add_part(int start, int end) {
    long long p = 0;
    for (int i = start; i < end; ++i) {
        p += A[i] * B[i];
    }
    lock_guard<mutex> lock(mtx);
    dot += p;
}

int main() {
    thread t1(add_part, 0, 3);
    thread t2(add_part, 3, 6);
    t1.join();
    t2.join();
    cout << "Safe Dot Product: " << dot << "\n";
    return 0;
}