#ifndef AKINATOR_H_INCLUDED
#define AKINATOR_H_INCLUDED

#include <string>

#include "Tree.h"
#include "DataBase.h"
#include "TastyFunctions.h"

typedef const char * cstring_t;

enum Question 
{
    ATTRIB = Tree::CurrNodeState::ATTRIB,
    OBJECT = Tree::CurrNodeState::OBJECT,
    
};

class Akinator : NonCopyable
{
public:
    Akinator (cstring_t attrBase);
   //~Akinator();

    int run();

private:
    void   ask (Question type)          const;
    void   getAnswer (std::string &ans) const;
    Child  matchNode (cstring_t answer) const;
    //bool   outAnswer (cstring_t ans)    const;
                                                    
    DataBase          m_attribBase;
    AttribTree        m_attribTree;                         
};

#endif // !AKINATOR_H_INCLUDED
