#include <iostream>
#include <thread>
#include <windows.h>

using namespace std;

void pinnedWorker() {
    DWORD_PTR mask = 1;
    DWORD_PTR prev = SetThreadAffinityMask(GetCurrentThread(), mask);
    if (prev != 0) {
        cout << "Thread successfully bound to Core 0.\n";
    } else {
        cerr << "SetThreadAffinityMask failed!\n";
    }
}

int main() {
    cout << "Available hardware cores: " << thread::hardware_concurrency() << "\n";

    thread t(pinnedWorker);
    t.join();

    return 0;
}