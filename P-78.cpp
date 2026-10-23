#include <iostream>
#include <vector>
#include <thread>

using namespace std;

const int N = 256;
vector<vector<double>> A(N, vector<double>(N, 1.0));
vector<vector<double>> B(N, vector<double>(N, 1.0));
vector<vector<double>> C(N, vector<double>(N, 0.0));

void block_mul(int t, int T) {
    int r = (N + T - 1) / T;
    int start = t * r;
    int end = min(N, (t + 1) * r);
    for (int i = start; i < end; ++i) {
        for (int j = 0; j < N; ++j) {
            double s = 0;
            for (int k = 0; k < N; ++k) {
                s += A[i][k] * B[k][j];
            }
            C[i][j] = s;
        }
    }
}

int main() {
    int T = 4;
    vector<thread> threads;
    for (int t = 0; t < T; ++t) {
        threads.emplace_back(block_mul, t, T);
    }
    for (auto& th : threads) {
        th.join();
    }
    cout << "Matrix multiplication completed.\n";
    return 0;
}