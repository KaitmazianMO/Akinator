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
    NAME_OF_NEW_OBJECT,
    DIFFERENCE,
    
    GAME_MODE,
};

enum GameMode
{
    UNKNOWN_MODE = -1, OUT = 0,
    GUESSING, INFO, COMPARE,
};

class Akinator : NonCopyable
{
public:
    Akinator (cstring_t attrBase);
   //~Akinator();

    int run();

private:
    void     ask (Question type)       const;
    void     getAnswer()               const;
    void     getGameMode()             const;
    void     getObjectCharacteristic() const;
    Child    matchAnswer()             const;
    GameMode identifyGameMode()        const;  
    bool     isCorrectAnswer()         const;
    bool     isPositiveAnswer()        const;
    bool     isNegativeAnswer()        const;

    void     outGameMenu()          const;
    void     outNotSuccessMessage() const;
    void     outSuccessMessage()    const;

    void newObject();

    void startGuessingMode();
    void startInfoMode() const;
    void startCompareMode() const;
    void outAnswerErrorMessage() const;

    mutable std::string m_answer;

    DataBase          m_attribBase;
    AttribTree        m_attribTree;                         
};

#endif // !AKINATOR_H_INCLUDED
