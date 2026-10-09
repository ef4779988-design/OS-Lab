#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    void* base = VirtualAlloc(nullptr, 1024 * 1024, MEM_RESERVE, PAGE_NOACCESS);
    if (!base) {
        cerr << "VirtualAlloc reserve failed!\n";
        return 1;
    }

    cout << "Reserved 1 MB address space at: " << base << "\n";

    int* page = (int*)VirtualAlloc(base, 4096, MEM_COMMIT, PAGE_READWRITE);
    if (!page) {
        cerr << "VirtualAlloc commit failed!\n";
        VirtualFree(base, 0, MEM_RELEASE);
        return 1;
    }

    page[0] = 42;
    cout << "Committed memory value: " << page[0] << "\n";

    VirtualFree(base, 0, MEM_RELEASE);
    return 0;
}