#pragma once
#pragma once

#ifndef __MEMORY_MODULE_HEADER
#define __MEMORY_MODULE_HEADER

#include <windows.h>

typedef void* HMEMORYMODULE;

typedef void* HMEMORYRSRC;

typedef void* HCUSTOMMODULE;

#ifdef __cplusplus
extern "C" {
#endif

    typedef LPVOID(*CustomAllocFunc)(LPVOID, SIZE_T, DWORD, DWORD, void*);
    typedef BOOL(*CustomFreeFunc)(LPVOID, SIZE_T, DWORD, void*);
    typedef HCUSTOMMODULE(*CustomLoadLibraryFunc)(LPCSTR, void*);
    typedef FARPROC(*CustomGetProcAddressFunc)(HCUSTOMMODULE, LPCSTR, void*);
    typedef void (*CustomFreeLibraryFunc)(HCUSTOMMODULE, void*);

    /**
     * Load EXE/DLL from memory location with the given size.
     *
     * All dependencies are resolved using default LoadLibrary/GetProcAddress
     * calls through the Windows API.
     */
    HMEMORYMODULE MemoryLoadLibrary(const void*, size_t);


    HMEMORYMODULE MemoryLoadLibraryEx(const void*, size_t,
        CustomAllocFunc,
        CustomFreeFunc,
        CustomLoadLibraryFunc,
        CustomGetProcAddressFunc,
        CustomFreeLibraryFunc,
        void*);

    /**
     * Get address of exported method. Supports loading both by name and by
     * ordinal value.
     */
    FARPROC MemoryGetProcAddress(HMEMORYMODULE, LPCSTR);

    /**
     * Free previously loaded EXE/DLL.
     */
    void MemoryFreeLibrary(HMEMORYMODULE);


    int MemoryCallEntryPoint(HMEMORYMODULE);

    HMEMORYRSRC MemoryFindResource(HMEMORYMODULE, LPCTSTR, LPCTSTR);


    HMEMORYRSRC MemoryFindResourceEx(HMEMORYMODULE, LPCTSTR, LPCTSTR, WORD);


    DWORD MemorySizeofResource(HMEMORYMODULE, HMEMORYRSRC);


    LPVOID MemoryLoadResource(HMEMORYMODULE, HMEMORYRSRC);


    int MemoryLoadString(HMEMORYMODULE, UINT, LPTSTR, int);


    int MemoryLoadStringEx(HMEMORYMODULE, UINT, LPTSTR, int, WORD);


    LPVOID MemoryDefaultAlloc(LPVOID, SIZE_T, DWORD, DWORD, void*);


    BOOL MemoryDefaultFree(LPVOID, SIZE_T, DWORD, void*);


    HCUSTOMMODULE MemoryDefaultLoadLibrary(LPCSTR, void*);


    FARPROC MemoryDefaultGetProcAddress(HCUSTOMMODULE, LPCSTR, void*);


    void MemoryDefaultFreeLibrary(HCUSTOMMODULE, void*);

#ifdef __cplusplus
}
#endif

#endif  // __MEMORY_MODULE_HEADER