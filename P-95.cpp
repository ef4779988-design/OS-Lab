#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;

void cpu_bound_worker(int id) {
    double val = 0;
    for (int i = 0; i < 1000000; ++i) {
        val += i;
    }
}

int main() {
    int num_cores = thread::hardware_concurrency();
    if (num_cores == 0) num_cores = 4;

    auto t0 = chrono::high_resolution_clock::now();
    vector<thread> threads_ok;
    for (int i = 0; i < num_cores; ++i) {
        threads_ok.emplace_back(cpu_bound_worker, i);
    }
    for (auto& th : threads_ok) {
        th.join();
    }
    auto t1 = chrono::high_resolution_clock::now();
    chrono::duration<double> time_ok = t1 - t0;

    auto t2 = chrono::high_resolution_clock::now();
    vector<thread> threads_over;
    for (int i = 0; i < 4 * num_cores; ++i) {
        threads_over.emplace_back(cpu_bound_worker, i);
    }
    for (auto& th : threads_over) {
        th.join();
    }
    auto t3 = chrono::high_resolution_clock::now();
    chrono::duration<double> time_over = t3 - t2;

    cout << "Normal threads time: " << time_ok.count() << "s\n";
    cout << "Oversubscribed threads time: " << time_over.count() << "s\n";
    return 0;
}