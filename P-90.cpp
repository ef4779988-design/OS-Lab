#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<pair<int, double>> measured_data = {
        {2, 1.8},
        {4, 3.2},
        {8, 5.5}
    };

    for (const auto& pair : measured_data) {
        int N = pair.first;
        double s_meas = pair.second;
        
        double f = ((1.0 / s_meas) - (1.0 / N)) / (1.0 - (1.0 / N));
        cout << "N: " << N << " | Measured Speedup: " << s_meas << " | Estimated Serial Fraction (f): " << f << "\n";
    }

    return 0;
}