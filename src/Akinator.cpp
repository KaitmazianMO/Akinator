#include "Akinator.h"

#include <iostream>

Akinator::Akinator (cstring_t attrBase) try :
    m_attribTree (), 
    m_attribBase (attrBase)
{
    m_attribTree.build (m_attribBase.getData());
}
catch (const std::exception &ex)
{
    printf ("ERROR::AKINATOR::CONSTRUCTING_ERROR\n%s\n", ex.what());
}

int Akinator::run()
{                          
    using namespace Tree;
    
    std::string answer;
    auto child     = Child::NON_CONFORMING;
    auto currState = Tree::CurrNodeState::ATTRIB;
    while (true)
    {
        ask (Question (CurrNodeState::ATTRIB));
        getAnswer (answer);
        child = matchNode (answer.c_str());
        currState = m_attribTree.move (child);
        switch (currState)
        {
            case CurrNodeState::ATTRIB:
                continue;
    
            case CurrNodeState::OBJECT:
                ask (Question (Tree::CurrNodeState::OBJECT));
                getAnswer (answer);
                return 0;
        }
    }
    return 0;
}

void Akinator::ask (Question type) const
{
    switch (type)
    {
        case Question::ATTRIB:
            std::cout << "Is " << m_attribTree.getCurrAttrib() << "?\n";
            break;

        case Question::OBJECT:
            std::cout << "Is it " << m_attribTree.getCurrAttrib() << "?\n";
            break;
    }
}

Child Akinator::matchNode (cstring_t ans) const
{
    if (strstr (ans, "yes"))
        return Child::CONFORMING;

    return Child::NON_CONFORMING;
}

void Akinator::getAnswer (std::string &ans) const
{
    std::getline (std::cin, ans);
}