#define WIN32_LEAN_AND_MEAN
#include <windows.h>

inline static
int StringLength(char* str)
{
    int count = 0;
    
    for(char *char_ptr = str; *char_ptr != '\0'; char_ptr++) 
    {
        count++;
    }
    
    return count;
}


inline static 
void StringCopy(char *Dest, char *Src, int Size)
{
    for (int I = 0; I < Size; ++I)
    {
        Dest[I] = Src[I];
    }
}

/*
 Note(Allan): This is really bad. I should fix this up later on.
*/
inline static
char **CommandLineToArgvA(LPSTR Args, int *ArgCount)
{
    char **Strings = 0;
    
    for(char *Char = Args; *Char != '\0'; ++Char)
    {
        if (*Char  == ' ')
        {
            while(*Char == ' ' && *Char != '\0') 
            {
                ++Char;
            }
            char *Peek = Char + 1;
            if (*Peek != '\0' && *Peek != '\n')
                ++*ArgCount;
        }
    }
    ++*ArgCount;
    Strings = (char **)VirtualAlloc(0, *ArgCount * sizeof(char *), 
                                    MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    int Length = 0;
    int Index = 0;
    char *Start = Args;
    char *Char = Args;
    for(;;)
    {
        if (*Char == ' ' || *Char == '\0')
        {
            Strings[Index] = (char *)VirtualAlloc(0, (Length + 1)* sizeof(char),
                                                  MEM_COMMIT | MEM_RESERVE, 
                                                  PAGE_READWRITE);
            StringCopy(Strings[Index], Start, Length);
            Strings[Index][Length] = 0;
            
            Length = 0;
            ++Index;
            if (*Char == ' ')
            {
                while (*Char == ' ')
                {
                    ++Char;
                }
                Start = Char;
                continue;
            }
            else
            {
                break;
            }
        }
        ++Length;
        ++Char;
    }
    return Strings;
}

inline static 
void Write(const char *Message, int Length)
{
    DWORD Written;
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), Message, Length, &Written, 0);
}

inline static
void Writef(const char *Format, ...)
{
    char Buffer[1028];
    va_list Args;
    va_start(Args, Format);
    unsigned int Length = wvsprintf(Buffer, Format, Args);
    va_end(Args);
    DWORD Written;
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE),
              Buffer, Length, &Written, 0);
}

void __cdecl 
mainCRTStartup(void)
{
    int ArgCount = 0;
    char **Arguments = CommandLineToArgvA(GetCommandLineA(), &ArgCount);
    if(ArgCount != 2)
    {
        char* Message = "Usage: cat.exe <file>";
        int Length = StringLength(Message);
        Write(Message, Length);
        ExitProcess(0);
    } 
    
    HANDLE File = CreateFileA(Arguments[1],
                              GENERIC_READ,
                              FILE_SHARE_READ,
                              0,
                              OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL,
                              0);
    
    if (File == INVALID_HANDLE_VALUE)
    {
        // TODO: Log here
    }
    
    LARGE_INTEGER FileSize;
    if (! GetFileSizeEx(File, &FileSize))
    {
        // TODO: Log Here
        CloseHandle(File);
        ExitProcess(2);
    }
    
    void *FileBuffer = VirtualAlloc(0, (int) FileSize.QuadPart, 
                                    MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    if(!FileBuffer)
    {
        // TODO: Log or Assert.
    }
    DWORD Written;
    if (! ReadFile(File,
                   FileBuffer,
                   (DWORD) FileSize.QuadPart,
                   &Written, 0))
    {
        // TODO: Log here
        CloseHandle(File);
        ExitProcess(2);
    }
    
    CloseHandle(File);
    
    Write((char *)FileBuffer, Written);
    
    ExitProcess(0);
}

