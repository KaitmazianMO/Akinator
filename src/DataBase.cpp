#include <stdio.h>
#include <assert.h>

#include "DataBase.h"      
#include "TastyFunctions.h"


DataBase::DataBase (cstring_t dataBaseFileName) :
    m_baseFileName (dataBaseFileName), m_buffer (readFile (dataBaseFileName))
{ 
    if (!m_buffer)
        throw std::exception ("Data base constuction failed");
}

DataBase::~DataBase()
{
    delete [] m_buffer;
    m_buffer       = nullptr;
    m_baseFileName = nullptr;
}