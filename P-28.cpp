#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    HANDLE hFile = CreateFileA(
        "guard_test.txt",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        nullptr, 
        CREATE_ALWAYS, 
        0, 
        nullptr
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        cerr << "File creation failed!\n";
        return 1;
    }

    if (LockFile(hFile, 0, 0, 100, 0)) {
        cout << "Byte range [0-100] locked successfully.\n";
        
        UnlockFile(hFile, 0, 0, 100, 0);
        cout << "Byte range unlocked.\n";
    } else {
        cerr << "LockFile failed!\n";
    }

    CloseHandle(hFile);
    return 0;
}