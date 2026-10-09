#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void logger() {
    for (int i = 0; i < 2; ++i) {
        cout << "Logging buffer to disk...\n";
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    thread t(logger);
    t.detach();
    this_thread::sleep_for(chrono::seconds(2));
    return 0;
}