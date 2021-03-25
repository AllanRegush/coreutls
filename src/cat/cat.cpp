#define WIN32_LEAN_AND_MEAN
#include <windows.h>


inline
int strlen(char* str)
{
    int count = 0;
    
    for(char *char_ptr = str; *char_ptr != '\0'; char_ptr++) 
    {
        count++;
    }
    
    return count;
}

inline
void Write(const char *Message, int Length)
{
    const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteConsole(hConsole, Message, Length, 0, 0);
    CloseHandle(hConsole);
}

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        const char* Message = "Usage: cat.exe <file>";
        const int Length = strlen(Message);
        Write(Message, Length);
        return 1;
    }
    
    HANDLE hFile = CreateFileA(argv[1],
                               GENERIC_READ,
                               FILE_SHARE_READ,
                               0,
                               OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL,
                               0);
    
    if (hFile == INVALID_HANDLE_VALUE)
    {
        // TODO: Log here
    }
    
    LARGE_INTEGER lFileSize;
    if (! GetFileSizeEx(hFile, &lFileSize))
    {
        // TODO: Log Here
        CloseHandle(hFile);
        return 2;
    }
    
    void *buffer = VirtualAlloc(0, (int) lFileSize.QuadPart, 
                                MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    if(!buffer)
    {
        // TODO: Log or Assert.
    }
    DWORD bytesWritten;
    if (! ReadFile(hFile,
                   buffer,
                   (DWORD) lFileSize.QuadPart,
                   &bytesWritten, 0))
    {
        // TODO: Log here
        CloseHandle(hFile);
        return 2;
    }
    
    CloseHandle(hFile);
    
    Write((char *)buffer, bytesWritten);
    
    return 0;
}