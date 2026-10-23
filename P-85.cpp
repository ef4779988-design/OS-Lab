#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <omp.h>

using namespace std;

void task_x() {
    double val = 0;
    for (int i = 0; i < 5000000; ++i) {
        val += sqrt(i);
    }
}

void task_y() {
    vector<int> vec(500000, 5);
    sort(vec.begin(), vec.end());
}

int main() {
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            task_x();
        }
        #pragma omp section
        {
            task_y();
        }
    }
    cout << "OpenMP sections executed successfully.\n";
    return 0;
}