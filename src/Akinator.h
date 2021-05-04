#ifndef AKINATOR_H_INCLUDED
#define AKINATOR_H_INCLUDED

#include <string>

#include "Tree.h"
#include "DataBase.h"
#include "TastyFunctions.h"

typedef const char * cstring_t;

const char * const POSITIVE_ANSWERS[]
{
    "yes",
    "yep",
    "yeah",
    "sure",
    "certainly",
};

const char * const NEGATIVE_ANSWERS[]
{
    "no",
    "nope",
    "not",
};


enum Question 
{
    ATTRIB = Tree::CurrNodeState::ATTRIB,
    OBJECT = Tree::CurrNodeState::OBJECT,
    ADD_NEW_OBJECT,
    NAME_OF_OBJECT,
    OBJECT_TO_FIND,
    DIFFERENCE,
    CONTINUE,
    
    GAME_MODE,
};

enum GameMode
{
    OUT = -1, UNKNOWN_MODE,
    GUESSING = 1, INFO, COMPARE,
};

class Akinator : NonCopyable
{
public:
    Akinator (cstring_t attrBase);
   //~Akinator();

    int run();

private:
    void     ask (Question type)       const;
    void     getPosNegAnswer()         const;
    void     getGameMode()             const;
    void     getObjectCharacteristic() const;
    void     getRealObject()           const;
    Child    matchAnswer()             const;
    GameMode identifyGameMode()        const;  
    bool     isCorrectGameMode()       const;
    bool     isCorrectAnswer()         const;
    bool     isPositiveAnswer()        const;
    bool     isNegativeAnswer()        const;

    void     outGameMenu()           const;
    void     outNotSuccessMessage()  const;
    void     outSuccessMessage()     const;
    void     outAnswerErrorMessage() const;

    bool startGuessingMode();
    void newObject();

    bool startInfoMode() const;
    void outObjectAttributes (
        const std::string &objName,
        const std::vector<const AttrNode *> &attribs, 
        const size_t attrBeg = 0   
    ) const;

    bool startCompareMode() const;
    int outSameObjectsAttributes (
        const std::string &firstObjName,
        const std::vector<const AttrNode *> &firstObjAttribs,
        const std::string &secondObjName, 
        const std::vector<const AttrNode *> &secondObjAttribs
    ) const;

    mutable std::string m_answer;

    DataBase          m_attribBase;
    AttribTree        m_attribTree;                         
};

#endif // !AKINATOR_H_INCLUDED
