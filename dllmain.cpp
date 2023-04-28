#include <Windows.h>
#include <iostream>
#include <vector>
#include <thread>
#include <conio.h>


using ull = unsigned long long;
using namespace std;


ull *source_points_address;
ull *skill_points_address;
ull *home_memory_points_address;

vector<ull *> all_addresses;

int default_value = 1000;
int increasing_value = 1000;


void *get_address_by_offsets(void *start_address, vector<ull> offsets) {
    for (int i = 0; i < offsets.size() - 1; i++) {
        start_address = (void *) *(ull *) ((char *) start_address + offsets[i]);
//        cout << hex << start_address << endl;
//        _getch();
    }
//    cout << "========================\n";
    return (char *) start_address + offsets[offsets.size() - 1];
}


void updateConsole() {
    system("cls");
    cout << "STATS:\n";
    cout << "Skill points: " << dec << *skill_points_address << endl;
    cout << "Source points: " << dec << *source_points_address << endl << endl;
    cout << "MENU:\n";
    cout << "0 - Uninjection\n";
    cout << "1 - Increase source points\n";
    cout << "2 - Increase skill points\n";
    cout << "3 - Increase home memory\n";
    cout << "8 - Set all values to default (1000)\n";
    cout << "9 - See pointers and values\n";
}


void value_increase(int i, const string &name) {
//    cout << "Increasing " << increasing_value << " to " << name << " points" << endl;
    (*(all_addresses[i])) += increasing_value;
    Sleep(1000);
    updateConsole();
}

int main() {
    constexpr int VK_0 = 0x30;
    constexpr int VK_1 = 0x31;
    constexpr int VK_2 = 0x32;
    constexpr int VK_3 = 0x33;
    constexpr int VK_4 = 0x34;
    constexpr int VK_5 = 0x35;
    constexpr int VK_6 = 0x36;
    constexpr int VK_7 = 0x37;
    constexpr int VK_8 = 0x38;
    constexpr int VK_9 = 0x39;


    constexpr int VK_A = 0x41;
    constexpr int VK_B = 0x42;
    constexpr int VK_C = 0x43;
    constexpr int VK_D = 0x44;
    constexpr int VK_E = 0x45;
    constexpr int VK_F = 0x46;
    constexpr int VK_G = 0x47;
    constexpr int VK_H = 0x48;
    constexpr int VK_I = 0x49;
    constexpr int VK_J = 0x4A;
    constexpr int VK_K = 0x4B;
    constexpr int VK_L = 0x4C;
    constexpr int VK_M = 0x4D;
    constexpr int VK_N = 0x4E;
    constexpr int VK_O = 0x4F;
    constexpr int VK_P = 0x50;
    constexpr int VK_Q = 0x51;
    constexpr int VK_R = 0x52;
    constexpr int VK_S = 0x53;
    constexpr int VK_T = 0x54;
    constexpr int VK_U = 0x55;
    constexpr int VK_V = 0x56;
    constexpr int VK_W = 0x57;
    constexpr int VK_X = 0x58;
    constexpr int VK_Y = 0x59;
    constexpr int VK_Z = 0x5A;


    void *program_start_address = GetModuleHandleA("Control_DX11.exe");
    vector<ull> source_points_offsets{0x0123D420, 0x58, 0x100, 0x1B0, 0x100, 0x378, 0x8, 0x148};
    vector<ull> skill_points_offsets{0x01245B70, 0x28, 0x3D0, 0x30, 0x28, 0x68, 0x188, 0x2E8};
    vector<ull> home_memory_points_offsets{0x0123D420, 0x40, 0x40, 0x348, 0x20, 0x68, 0x90, 0x550};

    source_points_address = (ull *) get_address_by_offsets(program_start_address, source_points_offsets);
    skill_points_address = (ull *) get_address_by_offsets(program_start_address, skill_points_offsets);
    home_memory_points_address = (ull *) get_address_by_offsets(program_start_address, home_memory_points_offsets);

    all_addresses = {source_points_address, skill_points_address, home_memory_points_address};

//    Sleep(10000);
    updateConsole();

    while (true) {
        if (GetAsyncKeyState(VK_0) & 1)
            break;

        else if (GetAsyncKeyState(VK_1) & 1) {
            value_increase(0, "source");
        } else if (GetAsyncKeyState(VK_2) & 1) {
            value_increase(1, "skill");
        } else if (GetAsyncKeyState(VK_3) & 1) {
            value_increase(2, "home memory");
        } else if (GetAsyncKeyState(VK_8) & 1) {
            for (ull *address: all_addresses) {
                (*address) = default_value;
            }
            cout << "All values seted to default\n";
            Sleep(2000);
            updateConsole();
        } else if (GetAsyncKeyState(VK_9) & 1) {
            cout << "Skill: " << hex << skill_points_address << " = " << dec << *skill_points_address << endl;
            cout << "Source: " << hex << source_points_address << " = " << dec << *source_points_address << endl;
            cout << "Home memory: " << hex << home_memory_points_address << " = " << dec << *home_memory_points_address
                 << endl;

            Sleep(5000);
            updateConsole();
        }
        Sleep(10);
    }
}


void __stdcall MainThread(HMODULE instance) {
    AllocConsole();
    FILE *fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    std::ios_base::sync_with_stdio(false);

    main();

    std::cout << "Uninjecting..." << std::endl;
    fclose(fp);
    FreeConsole();
    FreeLibraryAndExitThread(instance, 0);
}


int __stdcall DllMain(const HMODULE instance, const unsigned long reasonForCall, const void *) {
    if (reasonForCall == DLL_PROCESS_ATTACH)
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) MainThread, instance, 0, nullptr));

    return 1;
}
