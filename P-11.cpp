#include <iostream>
#include <thread>

using namespace std;

void worker() {
    cout << "Worker thread is running\n";
}

int main() {
    thread t(worker);

    cout << "Main thread is running\n";

    t.join();
    return 0;
}