#include <iostream>
#include <vector>

using namespace std;

int main() {
    double p = 0.9;
    for (int N = 1; N <= 8; ++N) {
        double s_amdahl = 1.0 / ((1.0 - p) + (p / N));
        double s_gustafson = N - (1.0 - p) * (N - 1.0);
        cout << "N: " << N << " | Amdahl: " << s_amdahl << " | Gustafson: " << s_gustafson << "\n";
    }
    return 0;
}