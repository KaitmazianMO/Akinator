#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <string>

#include "Node.h"
#include "TastyFunctions.h"

namespace Tree 
{
    enum class CurrNodeState
    {
        ATTRIB = 0,
        OBJECT
    };

    enum class Command
    {                       
        INIT_THE_CURR_NODE_CHILD = '{',  /* Conformity node initializes first */
        CLIMB_THE_CURR_NODE      = '}',
        SET_THE_CURR_NODE_ATTRIB = 'û'   /* Û */
    };
}

enum Child
{
    CONFORMING = 0,
    NON_CONFORMING,
    N_CHILDREN
};

using AttrNode = Node<std::string, static_cast<size_t> (Child::N_CHILDREN)>; 

class AttribTree : NonCopyable
{
public:
    AttribTree();
   ~AttribTree() 
   { 
       m_root->graphvisTreeGenerate("../res/AttribTree.txt");
       rebuildBase("../res/AttribBase(Constructed).txt");
   };
    
    const AttrNode     *find        (const std::string &obj) const;
    void                setCurrNode (const AttrNode *node) const;
    const AttrNode     *getCurrNode () const;
    void                buildTree   (char *attribData);
    void                rebuildBase (const char *baseFile) const; /* Terrible realisation :/ */
    Tree::CurrNodeState climbDown   (Child type);
    const std::string  &getCurrAttrib() const;
    void                restoreCurrNode();
    AttrNode           &getRealCurrNodeReference();
    

private:
    AttrNode               *m_root;
    mutable const AttrNode *m_currNode;
    Tree::CurrNodeState     m_currNodeState;
};

#endif // !TREE_H_INCLUDED
