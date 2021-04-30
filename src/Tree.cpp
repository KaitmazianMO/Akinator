#include "Tree.h"
#include <string.h>
#include <assert.h>

static char         *getAttrib  (char *attribData);
static char         *nextAttrib (char *attribData);
static Tree::Command getCommand (const char *attr);

AttribTree::AttribTree() :
    m_root          (nullptr), 
    m_currNode      (m_root),
    m_currNodeState (Tree::CurrNodeState::ATTRIB)
{ }

void AttribTree::build (char *attribData) 
{
    using namespace Tree;

    if (m_root == nullptr)
        m_root = new AttrNode (nullptr);

    auto currNode = &m_root;
    for (char *attrib = getAttrib (attribData); attrib; attrib = nextAttrib (attrib))
    {
        Command cmd = getCommand (attrib);
        switch (cmd)
        {
            case Command::INIT_THE_CURR_NODE_CHILD: 
                *currNode = (*currNode)->newChild();
                break;

            case Command::CLIMB_THE_CURR_NODE:
                *currNode = (*currNode)->getParent();
                break;

            case Command::SET_THE_CURR_NODE_ATTRIB:
                (*currNode)->setKey (std::move (std::string (attrib, getLineLength (attrib))));
                break;
        }
    }

    m_currNode = m_root;
}

Tree::CurrNodeState AttribTree::move (Child type)
{
    m_currNode = m_currNode->getChild((type));
    if (m_currNode->isLeaf())
        m_currNodeState = Tree::CurrNodeState::OBJECT;
    else
        m_currNodeState = Tree::CurrNodeState::ATTRIB;
    
    return m_currNodeState;
}
                     
const std::string  & AttribTree::getCurrAttrib() const
{
    return m_currNode->getKey();
}

static char *getAttrib (char *attribData)
{
    assert (attribData);

    attribData += strspn (attribData, " \t\r\n\0");

    return (*attribData != '\0') ? attribData : nullptr;
}

static char *nextAttrib (char *attribData)
{
    attribData = strchr (attribData, '\n');
    if (attribData == nullptr)
        return nullptr;

    return getAttrib (attribData);
}

static Tree::Command getCommand (const char *attr)
{          
    assert (attr);
    if (*attr == '{')
        return Tree::Command::INIT_THE_CURR_NODE_CHILD;

    else if (*attr == '}')
        return Tree::Command::CLIMB_THE_CURR_NODE;

    return Tree::Command::SET_THE_CURR_NODE_ATTRIB;
}