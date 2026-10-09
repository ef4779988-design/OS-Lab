#include <iostream>
#include <future>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    future<double> task = async(launch::async, []() {
        this_thread::sleep_for(chrono::seconds(1));
        return 3.14159;
    });

    cout << "Main thread continues work while async task computes...\n";

    double result = task.get();

    cout << "Result received: " << result << "\n";
    return 0;
}