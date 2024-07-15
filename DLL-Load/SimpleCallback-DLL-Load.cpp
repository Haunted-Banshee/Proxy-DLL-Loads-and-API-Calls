#include <windows.h>
#include <stdio.h>


extern "C" VOID CALLBACK SimpleCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_WORK Work);

PVOID pLoadLibraryA;

typedef struct CONTEXT_STRUCT {
    char* DllName;
    PVOID pLoadLibraryA;
};

typedef int(WINAPI* LPFN_MESSAGEBOX)(HWND, LPCTSTR, LPCTSTR, UINT);
PVOID pMessageBox;

int main() {


    CONTEXT_STRUCT Context;
    Context.DllName = (char*)"user32.dll";
    Context.pLoadLibraryA = GetProcAddress(GetModuleHandleA("kernel32"), "LoadLibraryA");


    PTP_WORK ptpWork = CreateThreadpoolWork(SimpleCallback, &Context, NULL);

    SubmitThreadpoolWork(ptpWork);

    Sleep(1000);

    printf("user32.dll should be loaded.\n");

    pMessageBox = GetProcAddress(GetModuleHandleA("user32"), "MessageBoxA");
    printf("pMessageBox -> 0x%x", pMessageBox);

    ((LPFN_MESSAGEBOX)pMessageBox)(NULL,
        TEXT("Test"),
        TEXT("MessageBox"),
        MB_OK | MB_ICONINFORMATION);

    CloseThreadpoolWork(ptpWork);

    return 0;
}
