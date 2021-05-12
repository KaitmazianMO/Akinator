#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <iostream>
#include <exception>
#include <string>
#include <assert.h>
#include <fstream>
#include <vector>
#include <algorithm>

#include "VisualStudioWarnings.h"

//---------------------------------------------------------------

template <typename T, size_t sz>
struct Node
{
    static constexpr size_t m_nChildrenMax = sz; 
                                           
    Node & operator = (const Node &node) = delete;
    Node (const Node &node)              = delete;
    
    Node ();
    Node (Node *parent);
    Node (const T &key, Node *parent);
    
    Node *newChild (size_t nChild, const T& key);
    Node *newChild();

    template <typename NodeT>
    friend void removeNode (NodeT *&node);
    template <typename NodeT>
    friend void removeSubTree (NodeT *&root);


    /* template <typename inerationFunctionT, typename ... ArgsT> */
    template <typename ... ArgsT>
    void walk (void (*iteration)(const Node *node, ArgsT & ... args), ArgsT & ... args) const;

    const Node * const & operator [] (size_t n) const;
          Node *       & operator [] (size_t n);
    const Node *         getChild (size_t n) const;
          Node *         getChild (size_t n);
          Node *&        getChildReference (size_t n);

    void      setKey (const T& key);
    const T & getKey()        const;
    const T & getParentKey()  const;
    int       getImageIndex() const;
    size_t    getDepth()      const;
    Node    * getParent()     const;
    size_t    nChildren()     const;
    bool      isLeaf()        const;
    
    const Node *find (const T &key) const;
    size_t      trace (std::vector<const Node *> &track) const;

    void graphvisTreeGenerate (const char *fileName) const;

    T            m_key;
    Node<T, sz> *m_parent;
    Node<T, sz> *m_childen[sz];
};

template <typename T, size_t sz, typename IterationFunctionT, typename ... ArgsT>
void modify (Node<T, sz> *&root, IterationFunctionT iteration, ArgsT & ... args);

//---------------------------------------------------------------

template <typename T, size_t sz>
Node<T, sz>::Node() :
    m_key(),
    m_parent (nullptr),
    m_childen()
{}

//---------------------------------------------------------------

template <typename T, size_t sz>
Node<T, sz>::Node (Node *parent) :
    m_key(),
    m_parent (parent),
    m_childen()
{}

//---------------------------------------------------------------

template <typename T, size_t sz>
Node<T, sz>::Node (const T &key, Node *parent) :
    m_key (key),
    m_parent (parent),
    m_childen()
{}

//---------------------------------------------------------------

template <typename T, size_t sz>    
Node<T, sz> *Node<T, sz>::newChild (size_t nChild, const T& key)
{
    if (nChild >= m_nChildrenMax)
    {
        throw std::runtime_error ("Invalid index: " + std::to_string (nChild));
    }
    if (m_childen[nChild] != nullptr)
    {
        throw std::runtime_error ("Child with index " + std::to_string (nChild) + " is already allocated");
    }

    return m_childen[nChild] = new Node (key, this);
}

//---------------------------------------------------------------

template <typename T, size_t sz>
template <typename ... ArgsT>
void Node<T, sz>::walk (void (*iteration)(const Node<T, sz> *node, ArgsT & ... args), ArgsT & ... args) const
{
    iteration (this, args...);
    for (int i = 0; i < m_nChildrenMax; ++i)
    {
        if ((*this)[i])
        { 
            (*this)[i]->walk (iteration, args...);
        }
    }
}

template <typename T, size_t sz, typename IterationFunctionT, typename ... ArgsT>
void modify (Node<T, sz> *&root, IterationFunctionT iteration, ArgsT & ... args)
{
    if (root)
    { 
        for (int i = 0; i < Node<T, sz>::m_nChildrenMax; ++i)
        {
            if (root->getChildReference (i))
            { 
                modify (root->getChildReference (i), iteration);
            }
        }    
        iteration (root, args...);
    }
}
                                                           
//---------------------------------------------------------------

template <typename T, size_t sz>
void __getNodeWithEqualKey (const Node<T, sz> *iterNode, const T &key, const Node<T, sz> *&getNode)
{
    if (iterNode && iterNode->getKey() == key)
        getNode = iterNode;
}

template <typename T, size_t sz>
const Node<T, sz> *Node<T, sz>::find (const T &key) const
{
    const Node<T, sz> *found = nullptr;
    walk (__getNodeWithEqualKey<T, sz>, key, found);

    return found;
}

//---------------------------------------------------------------

template <typename T, size_t sz>    
Node<T, sz> *Node<T, sz>::newChild()
{
    for (size_t i = 0; i < m_nChildrenMax; ++i)
    {
        if (m_childen[i] == nullptr)
            return m_childen[i] = new Node (this);
    }

    throw std::runtime_error ("All children are already alocated"); 
}

template <typename NodeT>
void removeNode (NodeT *&node)
{
    delete node;
    node = nullptr;
}

template <typename NodeT>
void removeSubTree (NodeT *&root)
{
    modify (root, removeNode<NodeT>);
}

//---------------------------------------------------------------

template <typename T, size_t sz>
const Node<T, sz> * const & Node<T, sz>::operator [] (size_t n) const
{
    assert (n < m_nChildrenMax && "Out of node range");

    return m_childen[n];
}

//---------------------------------------------------------------

template <typename T, size_t sz>
Node<T, sz> *& Node<T, sz>::operator [] (size_t n)
{
    assert (n < m_nChildrenMax && "Out of node range");

    return m_childen[n];
}

//---------------------------------------------------------------

template <typename T, size_t sz>
void Node<T, sz>::setKey (const T& key)
{
    m_key = key;
}

//---------------------------------------------------------------

template <typename T, size_t sz>
const Node<T, sz> *Node<T, sz>::getChild (size_t n) const
{
    return (*this)[n];
}

//---------------------------------------------------------------
                                                                   
template <typename T, size_t sz>
Node<T, sz> *Node<T, sz>::getChild (size_t n)
{
    return (*this)[n];
}

//---------------------------------------------------------------

template <typename T, size_t sz>
Node<T, sz> *&Node<T, sz>::getChildReference (size_t n)
{
    return (*this)[n];
}

//---------------------------------------------------------------

template <typename T, size_t sz>
Node<T, sz> *Node<T, sz>::getParent() const
{
    return m_parent;    
}

//---------------------------------------------------------------

template <typename T, size_t sz>    
const T& Node<T, sz>::getKey() const 
{
    return m_key;
}

//---------------------------------------------------------------

template <typename T, size_t sz>    
const T &Node<T, sz>::getParentKey() const
{
    assert (m_parent && "Getting key from nullptr parent");
    return m_parent->getKey();
}

//---------------------------------------------------------------

template <typename T, size_t sz>    
size_t Node<T, sz>::getDepth() const
{
    size_t count = 0;
    auto curr = this; 
    while (curr)
    {
        curr = curr->m_parent;
        ++count;
    }

    return count;
}

template <typename T, size_t sz>    
bool Node<T, sz>::isLeaf() const
{
    for (int i = 0; i < m_nChildrenMax; ++i)
    {
        if (m_childen[i] != nullptr)
            return false;
    }
    return true;
}

//--------------------------------------------------------------- 

template <typename T, size_t sz> 
size_t Node<T, sz>::nChildren() const
{
    size_t n = 0;
    for (int i = 0; i < m_nChildrenMax; ++i)
    {
        if ((*this)[i] != nullptr) ++n;
    }

    return n;
}

//---------------------------------------------------------------

template <typename T, size_t sz>
size_t Node<T, sz>::trace (std::vector<const Node<T, sz> *> &track) const
{
    const Node   *curr  = this;
    const size_t  depth = getDepth();

    track.resize (depth);
    for (size_t i = 0; i < depth; ++i)
    {
        track[depth - i - 1] = curr;
        curr = curr->m_parent;
    }
    
    return depth;
}

//---------------------------------------------------------------

template <typename T, size_t sz>
int Node<T, sz>::getImageIndex() const
{
    for (int i = 0; i < m_nChildrenMax; ++i)
    {
        if (m_parent && m_parent->getChild(i) == this)
            return i;
    }
    return -1;
}

//---------------------------------------------------------------
//     GraphViz addition
//---------------------------------------------------------------

template <typename T, size_t sz>
void graphVizNodeCreate (const Node <T, sz> *node, std::ofstream &src)
{
    if (!node) return;

    src << "\t""node" << node << " [label = \"" << node->getKey() << "\"];" "\n";
    if (node->m_parent)
    {
        src << "\t""node" << node->m_parent << " -- "
            <<     "node" << node << '\n';
    }
}

//---------------------------------------------------------------

template <typename T, size_t sz> 
void Node<T, sz>::graphvisTreeGenerate (const char *fileName) const
{
    assert (fileName);

    std::ofstream graphvisCode (fileName);
    if (!graphvisCode)
    {
        std::cout << "Can't open the file " << fileName << '\n' 
            << "GraphViz code generation was stopped" << '\n';
    }

    graphvisCode << "graph \"\"" << '\n'
        << "{" << '\n';

    walk (graphVizNodeCreate<T, sz>, graphvisCode);

    graphvisCode << "}" << '\n';
}

//---------------------------------------------------------------

#endif // !NODE_H_INCLUDED
