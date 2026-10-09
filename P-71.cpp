#include <iostream>
#include <future>

using namespace std;

int heavy_calc(int x) {
    return x * 2;
}

int main() {
    future<int> fut = async(launch::async, heavy_calc, 21);
    int res = fut.get();
    cout << "Async result: " << res << "\n";
    return 0;
}