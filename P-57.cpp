#include <iostream>
#include <thread>

using namespace std;

void worker(int val, int& ref_val) {
    val += 10;
    ref_val += 10;
}

int main() {
    int val = 5;
    int ref_val = 5;

    thread t(worker, val, ref(ref_val));
    t.join();

    cout << "After join - val: " << val << ", ref_val: " << ref_val << "\n";
    return 0;
}