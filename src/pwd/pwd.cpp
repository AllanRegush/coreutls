#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma function(strlen)
inline int 
strlen(char *str)
{
    int count = 0;
    
    if (str == 0) 
    {
        return count;
    }
    
    for (char *str_ptr = str; *str_ptr != '\0'; ++str_ptr)
    {
        ++count;
    }
    
    return count;
}


void __cdecl
mainCRTStartup(void)
{
    TCHAR NPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, NPath);
    const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteConsole(hConsole, NPath, strlen(NPath), 0, 0);
    CloseHandle(hConsole);
    
    ExitProcess(0);
}