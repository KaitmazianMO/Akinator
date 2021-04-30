#include "TastyFunctions.h"
#include <assert.h>
#include <sys/stat.h>

size_t getFileSize (FILE *file)
{
    if (!file) return 0;

    struct stat file_info = {};
    fstat (_fileno (file), &file_info);

    return file_info.st_size;
}

char *readFile (cstring_t fileName)
{
    if (!fileName) return nullptr;

    FILE *file = fopen (fileName, "rb");
    if (!file) return nullptr;

    const size_t fileSize = getFileSize (file);
    if (fileSize == 0) return nullptr;
    
    char *sourse = nullptr;
    try {
        sourse = new char [fileSize + 1] {};
    } catch (const std::exception) {
        return nullptr;
    }

    fread (sourse, sizeof (*sourse), fileSize, file);
    
    fclose (file);
    return sourse;
}

int printLine (cstring_t line)
{
    return printf ("%.*s", getLineLength (line), line);
}

int getLineLength (const char *line)
{
    if (!line) return -1;
    
    size_t len = 0;
    while (line[len] != '\r' &&
           line[len] != '\n' &&
           line[len] != '\0')
        ++len;

    return len;
}

