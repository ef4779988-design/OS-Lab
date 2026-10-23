#include <iostream>
#include <thread>
#include <vector>
#include <cmath>
#include <algorithm>

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
    thread p1(task_x);
    thread p2(task_y);
    p1.join();
    p2.join();
    cout << "Both independent tasks executed concurrently.\n";
    return 0;
}