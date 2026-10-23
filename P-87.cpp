#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

void worker_chunk(const vector<long long>& A, long long start, long long end, long long& result) {
    long long sum = 0;
    for (long long i = start; i < end; ++i) {
        sum += A[i];
    }
    result = sum;
}

int main() {
    int n = 10000000;
    vector<long long> A(n, 1);
    double f = 0.10;
    long long n_ser = f * n;

    auto t0 = chrono::high_resolution_clock::now();
    long long s_ser = 0;
    for (long long i = 0; i < n_ser; ++i) {
        s_ser += A[i];
    }

    int T = 4;
    long long s_par = 0;
    long long chunk_size = (n - n_ser + T - 1) / T;
    vector<thread> threads;
    vector<long long> partial_sums(T, 0);

    for (int t = 0; t < T; ++t) {
        long long start = n_ser + t * chunk_size;
        long long end = min((long long)n, n_ser + (t + 1) * chunk_size);
        threads.emplace_back(worker_chunk, cref(A), start, end, ref(partial_sums[t]));
    }

    for (auto& th : threads) {
        th.join();
    }

    for (int t = 0; t < T; ++t) {
        s_par += partial_sums[t];
    }

    auto t1 = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = t1 - t0;

    cout << "Total Sum: " << (s_ser + s_par) << " | Time: " << elapsed.count() << "s\n";
    return 0;
}