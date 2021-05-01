#include "Akinator.h"

#include <iostream>
#include <cstring>

Akinator::Akinator (cstring_t attrBase) try :
    m_attribTree (), 
    m_attribBase (attrBase)
{
    m_attribTree.buildTree (m_attribBase.getData());
}
catch (const std::exception &ex)
{
    printf ("ERROR::AKINATOR::CONSTRUCTING_ERROR\n%s\n", ex.what());
}

void Akinator::outGameMenu() const
{
    printf ("You can chose 3 game modes:\n");
    printf ("  [1] - Akinator tries to gues your character\n");
    printf ("  [2] - Akinator tells you about your character\n");
    printf ("  [3] - Akinator compare two characters\n");
    printf ("To chose the mode, just write the bracket number before the mode\n");
    printf ("To out the game write -1\n");
}

int Akinator::run()
{                          
    using namespace Tree;
    
    std::string answer;
    GameMode gameMode = UNKNOWN_MODE;

    printf ("Akinator greets you!\n");
    while (true)
    {
        outGameMenu();
        ask (Question::GAME_MODE);
        getGameMode();
        gameMode = identifyGameMode();

        switch (gameMode)
        {                          
        case GUESSING:
            startGuessingMode();
            break;

        //case INFO:
        //    startInfoMode();
        //    break;
        //
        //case COMPARE:
        //    startCompareMode();
        //    break;
        
        case UNKNOWN_MODE:
            printf ("I can't identify the game mode, please, follow the rules.\n");
            break;

        case OUT:
            return 0;

        default:
            return 666;
        }
    }
    return 0;
}

void Akinator::startGuessingMode()
{
    using namespace Tree;

    Child childType         = N_CHILDREN;
    CurrNodeState nodeState = CurrNodeState::ATTRIB;
    while (true)
    {
        ask (Question (CurrNodeState::ATTRIB));
        getAnswer();
        childType = matchAnswer();
        if (childType == N_CHILDREN) return;

        nodeState = m_attribTree.climbDown (childType);

        if (nodeState == CurrNodeState::OBJECT)
        {
            ask (Question (CurrNodeState::OBJECT));
            getAnswer();
            if (isPositiveAnswer())
            {
                outSuccessMessage();
                return;
            }
            else if (isNegativeAnswer())
            {
                ask (Question::ADD_NEW_OBJECT);
                getAnswer();
                if (isPositiveAnswer())
                {
                    newObject(); 
                }                    
                else
                {
                    outNotSuccessMessage();
                }
                return;
            }
            else
            {
                printf ("Some shit happend\n");
                return;
            }
        }
    }
}

void Akinator::newObject()
{
    ask (Question::NAME_OF_NEW_OBJECT);
    getObjectCharacteristic();
    auto newObjName = m_answer;
    auto oldObjName = m_attribTree.getCurrAttrib();

    ask (Question::DIFFERENCE);
    getObjectCharacteristic();
    auto newAttrib = m_answer;

    auto &newAttrNode = m_attribTree.getRealCurrNodeReference();

    newAttrNode.setKey (newAttrib);
    newAttrNode.newChild (Child::CONFORMING,     newObjName);
    newAttrNode.newChild (Child::NON_CONFORMING, oldObjName);
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

        case Question::GAME_MODE:
            std::cout << "What game mode do you prefer?\n";
            break;                                            
        
        case Question::ADD_NEW_OBJECT:
            std::cout << "Do you want to uodate my character base?\n";
            break;

        case Question::DIFFERENCE:
            std::cout << "What the difference between " << m_answer << " and " << m_attribTree.getCurrAttrib() << "?\n";
            std::cout << "The " << m_answer << " in contradistinction to " << m_attribTree.getCurrAttrib() << "..\n";
                                                        
        default:
            std::cout << "ERROR::UNKNOWN_QUESTION_TYPE : " << type << std::endl;
            return;
    }
}

Child Akinator::matchAnswer() const
{
    if (isPositiveAnswer())
        return Child::CONFORMING;
                                  
    if (isNegativeAnswer())
        return Child::NON_CONFORMING;

    return N_CHILDREN;
}

GameMode Akinator::identifyGameMode() const
{
    if (OUT <= std::stoi (m_answer) && std::stoi (m_answer) <= COMPARE)
        return GameMode (std::stoi (m_answer));
    
    return UNKNOWN_MODE;
}

void Akinator::getAnswer() const
{
    while (true)
    {
    std::getline (std::cin, m_answer);
    if (isCorrectAnswer())
        return;
    else 
        outAnswerErrorMessage();
    }
}

void Akinator::getGameMode() const
{
    std::getline (std::cin, m_answer);
}

void Akinator::getObjectCharacteristic() const
{
    std::getline (std::cin, m_answer);    
}

void Akinator::outAnswerErrorMessage() const
{
    printf ("I can't identify your asnwer\n"
            "The correst answers are %s, %s and others.\n",
            POSITIVE_ANSWERS[0], NEGATIVE_ANSWERS[0]);
}

bool Akinator::isPositiveAnswer() const
{
    for (int i = 0; i < N_ELEMS (POSITIVE_ANSWERS); ++i)
        if (strstr (m_answer.c_str(), POSITIVE_ANSWERS[i]))
            return true;
            
    return false;
}

bool Akinator::isNegativeAnswer() const
{
    for (int i = 0; i < N_ELEMS (NEGATIVE_ANSWERS); ++i)
        if (strstr (m_answer.c_str(), NEGATIVE_ANSWERS[i]))
            return true;
            
    return false;
}

bool Akinator::isCorrectAnswer() const
{
    return isPositiveAnswer() || isNegativeAnswer();
}

void Akinator::outSuccessMessage() const
{
    printf ("Thank you for the game. Do you want to try other modes?\n");
}

void Akinator::outNotSuccessMessage() const
{
    printf ("Thank you for the game. I hope next time i'll be better.\n");
}
