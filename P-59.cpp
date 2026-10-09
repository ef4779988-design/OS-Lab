#include <iostream>
#include <thread>

using namespace std;

void worker_fn() {
    cout << "Thread executing automatically.\n";
}

int main() {
    thread t(worker_fn);
    t.join(); // Standard thread ke liye join() zaroori hai
    return 0;
}