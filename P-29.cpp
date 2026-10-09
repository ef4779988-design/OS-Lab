#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    HANDLE hFile = CreateFileA(
        "async.bin", 
        GENERIC_WRITE, 
        0, 
        nullptr,
        CREATE_ALWAYS, 
        FILE_FLAG_OVERLAPPED, 
        nullptr
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        cerr << "CreateFile failed!\n";
        return 1;
    }

    OVERLAPPED ol{};
    ol.hEvent = CreateEventA(nullptr, TRUE, FALSE, nullptr);
    char buffer[1024] = "Asynchronous file write data packet.";

    WriteFile(hFile, buffer, sizeof(buffer), nullptr, &ol);

    cout << "I/O initiated. Doing computation in parallel...\n";

    WaitForSingleObject(ol.hEvent, INFINITE);
    cout << "Asynchronous write fully committed.\n";

    CloseHandle(ol.hEvent);
    CloseHandle(hFile);
    return 0;
}