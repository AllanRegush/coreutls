#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdint.h>

#define DAYSINMILLISECONDS 86400000
#define HOURSINMILLISECONDS 3600000
#define MINUTESINMILLISECONDS 60000
#define SECONDSINMILLISECONDS 1000

static void
Writef(const char *Format, ...)
{
    char Buffer[1028];
    
    va_list Args;
    va_start(Args, Format);
    uint32_t Length = wvsprintf(Buffer, Format, Args);
    va_end(Args);
    
    DWORD UnWritable;
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE),
              Buffer, Length, &UnWritable, 0);
}


void __cdecl
mainCRTStartup(void)
{
    uint64_t uptime = GetTickCount64();
    uint32_t days = uptime / DAYSINMILLISECONDS;
    uptime %= DAYSINMILLISECONDS;
    uint32_t hours = uptime / HOURSINMILLISECONDS;
    uptime %= HOURSINMILLISECONDS;
    uint32_t minutes = uptime / MINUTESINMILLISECONDS;
    uptime %= MINUTESINMILLISECONDS;
    uint32_t seconds = uptime / SECONDSINMILLISECONDS;
    uptime %= SECONDSINMILLISECONDS;
    Writef("Days: %d, Hours: %d, Minutes: %d, Seconds: %d", days, hours, minutes,  seconds);
    ExitProcess(0);
}