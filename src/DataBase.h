#ifndef DATA_BASE_H_INCLUDED
#define DATA_BASE_H_INCLUDED

#include "TastyFunctions.h"

const char * const ATTRIB_BASE_FILE_PATH = "../res/AttribBase.txt";

class DataBase : NonCopyable
{
public:
    DataBase (cstring_t dataBaseFileName);
   ~DataBase();

    char       *getData()     const { return m_buffer;       };
    const char *getFileName() const { return m_baseFileName; };

private:
    cstring_t  m_baseFileName;
    char      *m_buffer;
};

#endif // !DATA_BASE_H_INCLUDED
