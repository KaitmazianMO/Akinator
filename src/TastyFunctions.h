#ifndef TASTY_FUNCTIONS_H_INCLUDED
#define TASTY_FUNCTIONS_H_INCLUDED

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <exception>

typedef unsigned char uchar;
typedef const char *  cstring_t;

class NonCopyable
{
#if __cplusplus >= 201103L /* C++ 11 or newer */
    NonCopyable (const NonCopyable &)             = delete;
    NonCopyable &operator = (const NonCopyable &) = delete;
#else
    NonCopyable (const NonCopyable &obj);   // = is private
    NonCopyable &operator = (const NonCopyable &); // = is private
#endif

public: 
    NonCopyable() { }
};
                                        
char   *readFile    (cstring_t fileName);
size_t  getFileSize (FILE *file);
int     getLineLength (const char *line);
int     printLine (cstring_t line);

#define N_ELEMS( arr )    ( sizeof (arr) / sizeof (arr[0]) )

#endif // !TASTY_FUNCTIONS_H_INCLUDED
