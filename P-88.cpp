#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

void worker_sum(const vector<long long>& A, long long start, long long end, long long& result) {
    long long sum = 0;
    for (long long i = start; i < end; ++i) {
        sum += A[i];
    }
    result = sum;
}

int main() {
    int n = 10000000;
    vector<long long> A(n, 1);

    double t1_time = 0;
    for (int T = 1; T <= 8; ++T) {
        auto start_time = chrono::high_resolution_clock::now();

        vector<thread> threads;
        vector<long long> partial_sums(T, 0);
        long long chunk_size = (n + T - 1) / T;

        for (int t = 0; t < T; ++t) {
            long long start = t * chunk_size;
            long long end = min((long long)n, (t + 1) * chunk_size);
            threads.emplace_back(worker_sum, cref(A), start, end, ref(partial_sums[t]));
        }

        for (auto& th : threads) {
            th.join();
        }

        auto end_time = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end_time - start_time;
        double t_T = elapsed.count();

        if (T == 1) {
            t1_time = t_T;
        }

        double speedup = t1_time / t_T;
        double efficiency = speedup / T;

        cout << "T: " << T << " | Time: " << t_T << "s | Speedup: " << speedup << " | Efficiency: " << efficiency << "\n";
    }

    return 0;
}