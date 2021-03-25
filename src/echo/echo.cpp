#define WIN32_LEAN_AND_MEAN
#include <windows.h>

inline 
int strlen(char *str)
{
    int count = 0;
    for(char *char_ptr = str; *char_ptr != '\0'; ++char_ptr)
    {
        count++;
    }
    return count;
}


int main(int argc, char **argv)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for(int i = 1; i < argc; i++)
    {
        int Length = strlen(argv[i]);
        WriteConsole(hConsole, argv[i], Length, 0, 0);
        if (i + 1 < argc) {
            WriteConsole(hConsole, " ", 1, 0, 0);
        }
    }
    CloseHandle(hConsole);
    return 0;
}