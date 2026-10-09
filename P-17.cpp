#include <iostream>
#include <thread>
#include <vector>
#include <windows.h>

using namespace std;

HANDLE startEvent;

void worker(int id) {
    WaitForSingleObject(startEvent, INFINITE);
    cout << "Worker " << id << " triggered!\n";
}

int main() {
    startEvent = CreateEventA(nullptr, TRUE, FALSE, nullptr);
    if (startEvent == nullptr) {
        cerr << "Event creation failed!\n";
        return 1;
    }

    vector<thread> workers;
    for (int i = 1; i <= 3; ++i) {
        workers.emplace_back(worker, i);
    }

    cout << "Waiting 1 second before broadcasting start signal...\n";
    Sleep(1000);

    SetEvent(startEvent);

    for (auto& t : workers) {
        t.join();
    }

    CloseHandle(startEvent);
    return 0;
}