#define WIN32_LEAN_AND_MEAN
#include <windows.h>

inline
int StringLength(char* str)
{
    int count = 0;
    
    for(char *char_ptr = str; *char_ptr != '\0'; char_ptr++) 
    {
        count++;
    }
    
    return count;
}

inline 
char **CommandLineToArgvA(LPSTR Args,int *ArgCount)
{
    char **Strings;
    int Length = 0;
    char *word_ptr = Args;
    for(char *char_ptr = Args; *char_ptr != '\0'; char_ptr++)
    {
        if (*char_ptr == ' ')
        {
            ++*ArgCount;
        }
    }
    
    Strings = VirtualAlloc(0, ArgCount * sizeof(*Strings), 
                           MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    
    return Strings;
}

inline
void Write(const char *Message, int Length)
{
    DWORD Ignored;
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), Message, Length, &Ignored, 0);
}

void __cdecl 
mainCRTStartup(void)
{
    int ArgCount = 0;
    LPSTR Args = GetCommandLineA();
    int ArgsLength = StringLength(Args);
    Write(Args, ArgsLength + 1);
    char **Arguments = CommandLineToArgvA(GetCommandLineA(), &ArgCount);
    if(ArgCount != 2)
    {
        char* Message = "Usage: cat.exe <file>";
        const int Length = StringLength(Message);
        Write(Message, Length);
        ExitProcess(0);
    }
    
    int y = *(int *)0x0000;
    
    y++;
    
    HANDLE hFile = CreateFileA(&Args[1],
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
        //return 2;
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
        //return 2;
    }
    
    CloseHandle(hFile);
    
    Write((char *)buffer, bytesWritten);
    
    //return 0;
}

