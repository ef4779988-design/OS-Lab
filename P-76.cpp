#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

const int ARRAY_SIZE = 10000000;
vector<long long> A(ARRAY_SIZE, 1);
long long partial_sums[8] = {0};

void worker(int t, int num_threads) {
    long long chunk_size = (ARRAY_SIZE + num_threads - 1) / num_threads;
    long long start = t * chunk_size;
    long long end = min((long long)ARRAY_SIZE, (t + 1) * chunk_size);
    
    long long sum = 0;
    for (long long i = start; i < end; ++i) {
        sum += A[i];
    }
    partial_sums[t] = sum;
}

int main() {
    int T = 4;
    vector<thread> threads;
    for (int t = 0; t < T; ++t) {
        threads.emplace_back(worker, t, T);
    }
    for (auto& th : threads) {
        th.join();
    }
    long long parallel_sum = 0;
    for (int t = 0; t < T; ++t) {
        parallel_sum += partial_sums[t];
    }
    cout << "Parallel Sum: " << parallel_sum << "\n";
    return 0;
}