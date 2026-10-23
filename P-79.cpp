#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>

using namespace std;

const int N = 1000000;
vector<int> A(N, 42);
vector<int> lmax(4, 0);

void local_max(int t, int T) {
    int c = (N + T - 1) / T;
    int start = t * c;
    int end = min(N, (t + 1) * c);
    int m = A[start];
    for (int i = start; i < end; ++i) {
        m = max(m, A[i]);
    }
    lmax[t] = m;
}

int main() {
    int T = 4;
    vector<thread> threads;
    for (int t = 0; t < T; ++t) {
        threads.emplace_back(local_max, t, T);
    }
    for (auto& th : threads) {
        th.join();
    }
    int M = lmax[0];
    for (int t = 1; t < T; ++t) {
        M = max(M, lmax[t]);
    }
    cout << "Maximum element: " << M << "\n";
    return 0;
}