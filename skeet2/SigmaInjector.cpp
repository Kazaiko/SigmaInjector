#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#pragma comment(lib, "winmm.lib")

LPVOID ntOpenFile = GetProcAddress(LoadLibraryW(L"ntdll"), "NtOpenFile");

static void VACBypass(HANDLE hProcess) {
    if (ntOpenFile) {
        char originalBytes[5];
        memcpy(originalBytes, ntOpenFile, 5);
        WriteProcessMemory(hProcess, ntOpenFile, originalBytes, 5, NULL);
        printf("VAC bypassed successfully.");
    }
}

static void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

static DWORD GetProcessByName(const char* lpProcessName) {
    char lpCurrentProcessName[255] = { 0 };
    PROCESSENTRY32 ProcList{};
    ProcList.dwSize = sizeof(ProcList);
    const HANDLE hProcList = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcList == INVALID_HANDLE_VALUE)
        return -1;
    if (!Process32First(hProcList, &ProcList))
        return -1;
    wcstombs_s(nullptr, lpCurrentProcessName, ProcList.szExeFile, sizeof(lpCurrentProcessName) - 1);
    lpCurrentProcessName[sizeof(lpCurrentProcessName) - 1] = '\0';
    if (lstrcmpA(lpCurrentProcessName, lpProcessName) == 0)
        return ProcList.th32ProcessID;
    while (Process32Next(hProcList, &ProcList)) {
        wcstombs_s(nullptr, lpCurrentProcessName, ProcList.szExeFile, sizeof(lpCurrentProcessName) - 1);
        lpCurrentProcessName[sizeof(lpCurrentProcessName) - 1] = '\0';
        if (lstrcmpA(lpCurrentProcessName, lpProcessName) == 0)
            return ProcList.th32ProcessID;
    }
    return -1;
}

int main() {
    HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(102), L"WAV");
    if (hRes) {
        HGLOBAL hMem = LoadResource(NULL, hRes);
        if (hMem) {
            LPVOID pRes = LockResource(hMem);
            DWORD resSize = SizeofResource(NULL, hRes);
            if (pRes) {
                PlaySound((LPCWSTR)pRes, NULL, SND_MEMORY | SND_ASYNC | SND_LOOP);
            }
        }
    }

    SetConsoleTitle(L"Skeet Skeet #1 Cheat                                                                      (SIGMA MALE PROGRAM)                                                             ");

    const char* lpDLLName = "skeet.dll";
    const char* lpProcessName = "csgo.exe";
    char lpFullDLLPath[MAX_PATH];
    SetConsoleOutputCP(CP_UTF8);

    SetColor(12);
    std::cout << "                                                                                                                  \n";
    std::cout << "                                                                                                                  \n";
    std::cout << "                                                                                                                  \n";
    std::cout << "                                                                                                                  \n";
    std::cout << u8"                                    ██████   ██ ▄█▀ ▓█████  ▓█████  ▄▄▄█████▓                                   \n";
    std::cout << u8"                                  ▒██    ▒   ██▄█▒  ▓█   ▀  ▓█   ▀  ▓  ██▒ ▓▒                                   \n";
    std::cout << u8"                                  ░ ▓██▄    ▓███▄░  ▒███    ▒███    ▒ ▓██░ ▒░                                   \n";
    std::cout << u8"                                    ▒   ██▒ ▓██ █▄  ▒▓█  ▄  ▒▓█  ▄  ░ ▓██▓ ░                                    \n";
    std::cout << u8"                                  ▒██████▒▒ ▒██▒ █▄ ░▒████▒ ░▒████▒   ▒██▒ ░                                    \n";
    std::cout << u8"                                  ▒ ▒▓▒ ▒ ░ ▒ ▒▒ ▓▒ ░░ ▒░ ░ ░░ ▒░ ░   ▒ ░░                                      \n";
    std::cout << u8"                                  ░ ░▒  ░ ░ ░ ░▒ ▒░  ░ ░  ░  ░ ░  ░     ░                                       \n";
    std::cout << u8"                                  ░  ░  ░   ░ ░░ ░     ░       ░      ░                                         \n";
    std::cout << u8"                                        ░   ░  ░       ░  ░    ░  ░                                             \n";
    std::cout << u8"                                                                                                                \n";
    std::cout << u8"                                                                                                                \n";
    std::cout << u8"                             ╔════════════════════════════════════════════════════╗                             \n";
    std::cout << u8"                             ║              Version 2.0 - By Kazaiko              ║                             \n";
    std::cout << u8"                             ╚════════════════════════════════════════════════════╝                             \n";
    SetColor(7);

    SetColor(11);
    std::cout << "Waiting for process: " << lpProcessName << "...\n";
    SetColor(7);

    DWORD dwProcessID = -1;
    while (dwProcessID == (DWORD)-1) {
        dwProcessID = GetProcessByName(lpProcessName);
        if (dwProcessID == (DWORD)-1) {
            SetColor(12);
            std::cout << "Process not found.\r";
            SetColor(7);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    SetColor(10);
    std::cout << "\nProcess found.\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));

    if (!GetFullPathNameA(lpDLLName, MAX_PATH, lpFullDLLPath, nullptr)) {
        SetColor(12);
        std::cout << "Error: Could not get the full path of the DLL.\n";
        SetColor(7);
        return -1;
    }

    const HANDLE hTargetProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessID);
    if (hTargetProcess == nullptr) {
        SetColor(12);
        std::cout << "Error: Could not open the target process. Ensure you are running as administrator.\n";
        SetColor(7);
        return -1;
    }

    VACBypass(hTargetProcess);

    VirtualAllocEx(hTargetProcess, (LPVOID)0x43310000, 0x2FC000u, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    VirtualAllocEx(hTargetProcess, 0, 0x1000u, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    const LPVOID lpPathAddress = VirtualAllocEx(hTargetProcess, nullptr, lstrlenA(lpFullDLLPath) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (lpPathAddress == nullptr) {
        SetColor(12);
        std::cout << "Error: Could not allocate memory in the target process.\n";
        SetColor(7);
        CloseHandle(hTargetProcess);
        return -1;
    }

    SetColor(10);
    std::cout << "\nMemory allocated in target process at: " << std::hex << (uintptr_t)lpPathAddress << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));

    if (!WriteProcessMemory(hTargetProcess, lpPathAddress, lpFullDLLPath, lstrlenA(lpFullDLLPath) + 1, nullptr)) {
        SetColor(12);
        std::cout << "Error: Could not write the DLL path to the target process memory.\n";
        SetColor(7);
        CloseHandle(hTargetProcess);
        return -1;
    }
    std::cout << "DLL path written successfully.\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));

    const HMODULE hModule = GetModuleHandleA("kernel32.dll");
    if (hModule == INVALID_HANDLE_VALUE || hModule == nullptr)
        return -1;

    const FARPROC lpFunctionAddress = GetProcAddress(hModule, "LoadLibraryA");
    if (lpFunctionAddress == nullptr) {
        SetColor(12);
        printf("An error occurred when trying to get \"LoadLibraryA\" address.\n");
        SetColor(7);
        return -1;
    }

    printf("LoadLibraryA address at 0x%X\n", (UINT)(uintptr_t)lpFunctionAddress);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    const HANDLE hThreadCreationResult = CreateRemoteThread(hTargetProcess, nullptr, 0, (LPTHREAD_START_ROUTINE)lpFunctionAddress, lpPathAddress, 0, nullptr);
    if (hThreadCreationResult == INVALID_HANDLE_VALUE) {
        SetColor(12);
        std::cout << "Error: Could not create a remote thread in the target process.\n";
        SetColor(7);
        CloseHandle(hTargetProcess);
        return -1;
    }

    SetColor(11);
    std::cout << "DLL injected successfully!\n";
    std::this_thread::sleep_for(std::chrono::seconds(10));

    SetColor(7);
    return 0;
}
