#include <iostream>
#include <thread>
#include <vector>
#include <windows.h>

using namespace std;

HANDLE sem;

void worker(int id) {
    WaitForSingleObject(sem, INFINITE);

    cout << "Thread " << id << " acquired resource.\n";
    Sleep(1000);
    cout << "Thread " << id << " releasing resource.\n";

    ReleaseSemaphore(sem, 1, nullptr);
}

int main() {
    sem = CreateSemaphoreA(nullptr, 2, 2, nullptr);
    if (sem == nullptr) {
        cerr << "Semaphore creation failed!\n";
        return 1;
    }

    vector<thread> threads;
    for (int i = 1; i <= 4; ++i) {
        threads.emplace_back(worker, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    CloseHandle(sem);
    return 0;
}