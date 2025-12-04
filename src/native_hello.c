#define WIN32_NO_STATUS
#include <windows.h>
#include <winternl.h>

#pragma comment(lib, "ntdll.lib")


static const wchar_t* MESSAGE = L"\r\nHello Native\r\n";
static const LONG DISPLAY_TIME_MS = 5000;

void SleepNative(LONG ms)
{
    LARGE_INTEGER interval;
    interval.QuadPart = -((LONGLONG)ms * 10000);
    NtDelayExecution(FALSE, &interval);
}

void Display(const wchar_t* msg)
{
    UNICODE_STRING u;
    RtlInitUnicodeString(&u, msg);
    NtDisplayString(&u);
}

void NtProcessStartup(void* arg)
{
    UNREFERENCED_PARAMETER(arg);

    Display(MESSAGE);
    SleepNative(DISPLAY_TIME_MS);

    NtTerminateProcess((HANDLE)-1, 0);
}
