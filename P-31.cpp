#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    char* page = (char*)VirtualAlloc(nullptr, 4096, MEM_COMMIT, PAGE_READWRITE);
    if (!page) {
        cerr << "VirtualAlloc failed!\n";
        return 1;
    }

    page[0] = 'A';
    cout << "Normal write successful. Value: " << page[0] << "\n";

    DWORD oldProtect;
    if (VirtualProtect(page, 4096, PAGE_READONLY, &oldProtect)) {
        cout << "Page protections successfully changed to READ-ONLY at hardware level.\n";
    }

    VirtualFree(page, 0, MEM_RELEASE);
    return 0;
}