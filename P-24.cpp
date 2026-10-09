#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    STARTUPINFOA si{};
    PROCESS_INFORMATION pi{};
    si.cb = sizeof(si);

    char command[] = "cmd.exe /C exit 42";

    if (CreateProcessA(nullptr, command, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)) {
        WaitForSingleObject(pi.hProcess, INFINITE);

        DWORD exitCode = 0;
        GetExitCodeProcess(pi.hProcess, &exitCode);

        cout << "Child process exited with code: " << exitCode << "\n";

        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    } else {
        cerr << "CreateProcess failed!\n";
    }

    return 0;
}