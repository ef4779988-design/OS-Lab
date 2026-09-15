#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    STARTUPINFOA si{};
    PROCESS_INFORMATION pi{};
    si.cb = sizeof(si);

    char command[] = "cmd.exe /C echo I am the child";

    if (CreateProcessA(
        nullptr,
        command,
        nullptr,
        nullptr,
        FALSE,
        0,
        nullptr,
        nullptr,
        &si,
        &pi)) {
        
        cout << "I am the parent\n";

        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    }
    return 0;
}