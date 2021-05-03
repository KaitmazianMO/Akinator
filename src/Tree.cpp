#include "Tree.h"
#include <string.h>
#include <assert.h>
#include <fstream>

static char         *getAttrib  (char *attribData);
static char         *nextAttrib (char *attribData);
static Tree::Command getCommand (const char *attr);
template <typename T, size_t sz>
static void buildNode (const Node<T, sz> *node, std::ofstream &base);


AttribTree::AttribTree() :
    m_root          (nullptr), 
    m_currNode      (m_root),
    m_currNodeState (Tree::CurrNodeState::ATTRIB)
{ }

void AttribTree::buildTree (char *attribData) 
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

void AttribTree::rebuildBase (const char *baseFile) const
{
    assert (baseFile);
    std::ofstream base (baseFile);

    base << m_root->getKey() << '\n';
    for (int i = 0; i < m_root->m_nChildrenMax; ++i)
        buildNode (m_root->getChild (i), base);
}

const AttrNode *AttribTree::find (const std::string &obj) const
{
    return m_root->find (obj);
}

template <typename T, size_t sz>
static void buildNode (const Node<T, sz> *node, std::ofstream &base)
{
    if (node)
    { 
        base << "{\n";
        base << node->getKey() << '\n';

    for (int i = 0; i < node->m_nChildrenMax; ++i)
        buildNode (node->getChild (i), base);
    
    base << "}\n"; 
    }               
}

Tree::CurrNodeState AttribTree::climbDown (Child type)
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

AttrNode &AttribTree::getRealCurrNodeReference()
{
    return *(*m_currNode->m_parent)[m_currNode->getImageIndex()];
}

void AttribTree::restoreCurrNode()
{
    m_currNode = m_root;
    m_currNodeState = Tree::CurrNodeState::ATTRIB;
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
