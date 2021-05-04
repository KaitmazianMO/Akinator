#include "Akinator.h"

#include <iostream>
#include <cstring>
#include <vector>

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
                                                                
    GameMode gameMode = UNKNOWN_MODE;  
    bool isContinue = true;
                                                                
    printf ("Akinator greets you!\n");                          
    while (isContinue)                                                
    {                                                           
        outGameMenu();                                          
        ask (Question::GAME_MODE);                              
        gameMode = identifyGameMode();                          
        m_attribTree.restoreCurrNode();                         
                                                                
        switch (gameMode)                                       
        {                                                       
        case GUESSING:                                          
            isContinue = startGuessingMode();                                
            break;                                              
                                                                
        case INFO:                                              
            isContinue = startInfoMode();                                    
            break;                                              
                                                                
        case COMPARE:                                           
            isContinue = startCompareMode();                                 
            break;                                              
                                                                
        case UNKNOWN_MODE:
            printf ("I can't identify the game mode, please, follow the rules.\n");
            break;

        case OUT:
            return 0;

        default:
            return 666;
        }
    }
    printf ("Thank you for choosing my Aknator!\n");

    return 0;
}

bool Akinator::startGuessingMode()
{
    using namespace Tree;

    Child childType         = N_CHILDREN;
    CurrNodeState nodeState = CurrNodeState::ATTRIB;
    while (true)
    {
        ask (Question (CurrNodeState::ATTRIB));
        childType = matchAnswer();
        if (childType == N_CHILDREN) break;

        nodeState = m_attribTree.climbDown (childType);

        if (nodeState == CurrNodeState::OBJECT)
        {
            ask (Question (CurrNodeState::OBJECT));
            if (isPositiveAnswer())
            {
                outSuccessMessage();
                break;
            }
            else if (isNegativeAnswer())
            {
                ask (Question::ADD_NEW_OBJECT);
                if (isPositiveAnswer())
                {
                    newObject(); 
                }                    
                else
                {
                    outNotSuccessMessage();
                }
                break;
            }
            else
            {
                printf ("Some shit happend\n");
                break;
            }
        }
    }

    ask (Question::CONTINUE);
    return isPositiveAnswer();
        
}

void Akinator::newObject()
{
    ask (Question::NAME_OF_OBJECT);
    auto newObjName = m_answer;
    auto oldObjName = m_attribTree.getCurrAttrib();

    ask (Question::DIFFERENCE);
    auto newAttrib = m_answer;

    auto &newAttrNode = m_attribTree.getRealCurrNodeReference();

    newAttrNode.setKey (newAttrib);
    newAttrNode.newChild (Child::CONFORMING,     newObjName);
    newAttrNode.newChild (Child::NON_CONFORMING, oldObjName);

    printf ("Than ypu for new character!\n");
}

bool Akinator::startInfoMode() const
{
    ask (Question::OBJECT_TO_FIND);
    auto objNode = m_attribTree.getCurrNode();

    std::vector <const AttrNode *> track;
    objNode && objNode->trace (track);

    outObjectAttributes (m_answer, track);

    ask (Question::CONTINUE);
    return isPositiveAnswer();
}

void Akinator::outObjectAttributes (
    const std::string &objName,
    const std::vector<const AttrNode *> &attribs,
    const size_t attrBeg
) const
{
    bool first = true;
    for (size_t i = attrBeg; i < attribs.size(); ++i)
    {     
        if (attribs[i]->getParent())
        {
            if (first) printf ("%s is ", objName.c_str());  
            
            if (!first) printf (", "); 
            if (attribs[i]->getImageIndex() == NON_CONFORMING)
                printf ("not ");
            printf ("%s", attribs[i]->getParentKey().c_str());
        
            first = false;
        }
    }       
    printf (".\n");
}

bool Akinator::startCompareMode() const
{
    ask (Question::OBJECT_TO_FIND);
    auto firstObjNode = m_attribTree.getCurrNode();            
    
    ask (Question::OBJECT_TO_FIND);
    auto secondObjNode = m_attribTree.getCurrNode();   
    
    std::vector <const AttrNode *>       firstObjAttributeTrack; 
    firstObjNode && firstObjNode->trace (firstObjAttributeTrack);        
    
    std::vector <const AttrNode *>         secondObjAttributeTrack;
    secondObjNode && secondObjNode->trace (secondObjAttributeTrack);    

    int nSame = outSameObjectsAttributes (
        firstObjNode->getKey(), firstObjAttributeTrack, 
        secondObjNode->getKey(), secondObjAttributeTrack
    );
    if (nSame) printf ("But..\n");
    outObjectAttributes (firstObjNode->getKey(),  firstObjAttributeTrack,  nSame);                                
    outObjectAttributes (secondObjNode->getKey(), secondObjAttributeTrack, nSame);

    ask (Question::CONTINUE);
    return isPositiveAnswer();
}

int Akinator::outSameObjectsAttributes (
    const std::string &firstObjName,
    const std::vector<const AttrNode *> &firstObjAttribs,
    const std::string &secondObjName, 
    const std::vector<const AttrNode *> &secondObjAttribs
) const
{
    int nSame = 0;
    bool first = true;
    while (firstObjAttribs[nSame] == secondObjAttribs[nSame])
    { 
        if (firstObjAttribs[nSame]->getImageIndex() == secondObjAttribs[nSame]->getImageIndex())
        {
            if (firstObjAttribs[nSame]->getParent())
            {
                if (first) printf ("%s and %s are both ", firstObjName.c_str(), secondObjName.c_str());

                if (!first) printf (", ");
                if (firstObjAttribs[nSame]->getImageIndex() == NON_CONFORMING) printf ("not ");
                    printf ("%s", firstObjAttribs[nSame]->getParentKey().c_str());
                first = false;
            }
            ++nSame;
        }
    }
    if (!first) printf (".\n");

    return nSame;
}

void Akinator::ask (Question type) const
{
    switch (type)
    {
        case Question::ATTRIB:
            std::cout << "Is " << m_attribTree.getCurrAttrib() << "?\n";
            getPosNegAnswer();
            break;

        case Question::GAME_MODE:
            std::cout << "What game mode do you prefer?\n";
            getGameMode();
            break;                                            
        
        case Question::ADD_NEW_OBJECT:
            std::cout << "Do you want to update my character base?\n";
            getPosNegAnswer();
            break;

        case Question::OBJECT:
            std::cout << "Is it " << m_attribTree.getCurrAttrib() << "?\n";
            getPosNegAnswer(); // was getObjectCharacteristic();
            break;

        case Question::NAME_OF_OBJECT:
            std::cout << "Who was it?\n";
            getObjectCharacteristic();
            break;

        case Question::OBJECT_TO_FIND:
            std::cout << "Who is it?\n";
            getRealObject();
            break;

        case Question::DIFFERENCE:
            std::cout << "What the difference between \'" << m_answer << "\' and \'" << m_attribTree.getCurrAttrib() << "\'?\n";
            std::cout << "The " << m_answer << " in contradistinction to " << m_attribTree.getCurrAttrib() << "..\n";
            getObjectCharacteristic();
            break;

        case Question::CONTINUE:
            std::cout << "Do you want to play again?\n";
            getPosNegAnswer();
            break;
                                                        
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
    if (isCorrectGameMode())
        return GameMode (std::strtol (m_answer.c_str(), NULL, 10));
    
    return UNKNOWN_MODE;
}

void Akinator::getPosNegAnswer() const
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
    while (true)
    {
        std::getline (std::cin, m_answer);
        if (isCorrectGameMode())
            break;
        else
            printf ("Incorrect game mode \'%s\'. Write a game mode number.\n", m_answer.c_str());
    }
}

void Akinator::getObjectCharacteristic() const
{
    std::getline (std::cin, m_answer);    
}

void Akinator::getRealObject() const
{
    const AttrNode *found = nullptr;
    while (true)
    {
        getObjectCharacteristic();
        found = m_attribTree.find (m_answer);
        if (!found)
        { 
            printf ("I can't find this character. Try others.\n");
        }
        else
        {
            m_attribTree.setCurrNode (found);
            break;
        }
    }
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

bool Akinator::isCorrectGameMode() const
{
    return OUT <= std::strtol (m_answer.c_str(), NULL, 10) &&
                  std::strtol (m_answer.c_str(), NULL, 10) <= COMPARE;
}

void Akinator::outSuccessMessage() const
{
    printf ("Thank you for the game.\n");
}

void Akinator::outNotSuccessMessage() const
{
    printf ("Thank you for the game. I hope next time i'll be better.\n");
}
