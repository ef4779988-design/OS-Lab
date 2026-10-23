#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

void thread_main(int id) {
    cout << "User thread " << id << " running in process ID: " << getpid() << "\n";
}

int main() {
    int k = 3;
    for (int i = 0; i < k; ++i) {
        thread_main(i);
    }
    return 0;
}