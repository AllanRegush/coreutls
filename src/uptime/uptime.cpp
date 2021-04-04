#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdint.h>

#define DAYSINMILLISECONDS 86400000
#define HOURSINMILLISECONDS 3600000
#define MINUTESINMILLISECONDS 60000
#define SECONDSINMILLISECONDS 1000

int main(void)
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
    printf("Days: %d, Hours: %d, Minutes: %d, Seconds: %d", days, hours, minutes,  seconds);
    return 0;
}