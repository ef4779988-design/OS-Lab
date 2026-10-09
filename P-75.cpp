#include <iostream>
#include <thread>
#include <mutex>
#include <algorithm>

using namespace std;

mutex forks[2];

void dine(int left_id, int right_id) {
    int first = min(left_id, right_id);
    int second = max(left_id, right_id);

    unique_lock<mutex> l1(forks[first]);
    unique_lock<mutex> l2(forks[second]);

    cout << "Philosopher eating with ordered locks.\n";
}

int main() {
    thread t(dine, 0, 1);
    t.join();
    return 0;
}