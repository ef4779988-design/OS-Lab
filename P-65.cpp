#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtxA, mtxB;

void transfer_funds() {
    scoped_lock lock(mtxA, mtxB);
    cout << "Transferred funds safely without deadlock.\n";
}

int main() {
    thread t(transfer_funds);
    t.join();
    return 0;
}