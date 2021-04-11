#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        WriteConsole(hConsole, "NEEDS AN ARG", 12, 0,0);
        return 1;
    }
    
    CreateFileA(argv[1], 0, 0, 0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);
    return 0;
}