#include <iostream>
#include <thread>
#include <windows.h>

using namespace std;

HANDLE sem;

void task(int id) {
    WaitForSingleObject(sem, INFINITE);
    cout << "Thread " << id << " acquired semaphore quota.\n";
    ReleaseSemaphore(sem, 1, nullptr);
}

int main() {
    sem = CreateSemaphoreA(nullptr, 3, 3, nullptr);
    if (sem == nullptr) {
        cerr << "Semaphore creation failed!\n";
        return 1;
    }

    thread t1(task, 1);
    thread t2(task, 2);

    t1.join();
    t2.join();
    
    CloseHandle(sem);
    return 0;
}