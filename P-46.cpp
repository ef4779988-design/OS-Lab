#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int shared_data = 0;
mutex mtx; 

void reader(int id) {
    lock_guard<mutex> lock(mtx); 
    cout << "Reader " << id << " read value: " << shared_data << endl;
}

void writer(int id, int value) {
    lock_guard<mutex> lock(mtx); 
    shared_data = value;
    cout << "Writer " << id << " updated value to: " << shared_data << endl;
}

int main() {
    thread w1(writer, 1, 42); 
    w1.join();
    
    thread r1(reader, 1), r2(reader, 2); 
    r1.join(); 
    r2.join();
    
    thread w2(writer, 2, 99); 
    w2.join();
    
    thread r3(reader, 3); 
    r3.join();
    
    return 0;
}
