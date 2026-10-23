#include <iostream>
#include <vector>
#include <cmath>
#include <thread>

using namespace std;

const int N = 1000000;
vector<double> A(N, 1.5), B(N, 2.0), C(N, 0.0);

void chunk_worker(int t, int T) {
    int c = (N + T - 1) / T;
    int start = t * c;
    int end = min(N, (t + 1) * c);
    for (int i = start; i < end; ++i) {
        C[i] = A[i] * B[i] + sin(A[i]);
    }
}

int main() {
    int T = 4;
    vector<thread> threads;
    for (int t = 0; t < T; ++t) {
        threads.emplace_back(chunk_worker, t, T);
    }
    for (auto& th : threads) {
        th.join();
    }
    cout << "Vector expression computed successfully.\n";
    return 0;
}