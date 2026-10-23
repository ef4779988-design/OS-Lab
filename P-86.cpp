#include <iostream>

using namespace std;

int main() {
    double p = 0.9;
    int N_max = 16;
    for (int N = 1; N <= N_max; ++N) {
        double S = 1.0 / ((1.0 - p) + (p / N));
        cout << "N: " << N << " | Speedup: " << S << "\n";
    }
    return 0;
}