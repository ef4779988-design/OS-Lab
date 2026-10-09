#include <iostream>
#include <thread>

using namespace std;

thread_local int txn_id = 0;

void run(int val) {
    txn_id += val;
    cout << "Thread ID: " << this_thread::get_id() << " | txn_id = " << txn_id << "\n";
}

int main() {
    thread t1(run, 10);
    thread t2(run, 20);

    t1.join();
    t2.join();
    return 0;
}