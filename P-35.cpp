#include <iostream>
#include <thread>
#include <vector>

using namespace std;

thread_local int localVal = 0;

void run(int offset) {
    localVal += offset;
    cout << "Thread ID: " << this_thread::get_id() << " | localVal = " << localVal << "\n";
}

int main() {
    thread t1(run, 10);
    thread t2(run, 20);
    thread t3(run, 30);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}