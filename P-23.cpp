#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    int x = 10;
    MEMORY_BASIC_INFORMATION mbi{};

    if (VirtualQuery(&x, &mbi, sizeof(mbi)) != 0) {
        cout << "Address: " << mbi.BaseAddress << "\n";
        cout << "Region Size: " << mbi.RegionSize << " bytes\n";
        cout << "State: " << ((mbi.State & MEM_COMMIT) ? "MEM_COMMIT" : "OTHER") << "\n";
    }

    return 0;
}