#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int main(int argc, char **argv)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for(int i = 1; i < argc; i++)
    {
        int Length = sizeof(argv[i]) / sizeof(char);
        WriteConsole(hConsole, argv[i], Length, 0, 0);
    }
    CloseHandle(hConsole);
    return 0;
}