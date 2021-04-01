#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int strlen(char *str)
{
    int count = 0;
    
    for (char *str_ptr = str; *str_ptr != '\0'; ++str_ptr)
    {
        ++count;
    }
    
    return count;
}


int main(int argc, char **argv)
{
    if (argc != 3) 
    {
        const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        const char *Message = "Need three arguments";
        WriteConsole(hConsole, Message, strlen(Message), 0, 0);
        CloseHandle(hConsole);
        return 1;
    }
    
    if (!CopyFile(argv[1], argv[2], 0)) 
    {
        const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        const char *Message = "Could not copy"; 
        WriteConsole(hConsole, Message, strlen(Message), 0, 0);
        WriteConsole(hConsole, argv[1], strlen(argv[1]), 0, 0);
        CloseHandle(hConsole);
        return 1;
    }
    
    return 0;
}