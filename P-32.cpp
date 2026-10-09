#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

using namespace std;

int main() {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) {
        cerr << "Snapshot failed!\n";
        return 1;
    }

    PROCESSENTRY32 pe{};
    pe.dwSize = sizeof(PROCESSENTRY32);

    int count = 0;
    if (Process32First(snap, &pe)) {
        do {
            count++;
            cout << "PID: " << pe.th32ProcessID << "\t" << pe.szExeFile << "\n";
            if (count >= 5) break;
        } while (Process32Next(snap, &pe));
    }

    CloseHandle(snap);
    return 0;
}