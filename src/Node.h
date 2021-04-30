#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <iostream>
#include <exception>
#include <string>
#include <assert.h>
#include <fstream>
#include <vector>
#include <algorithm>

//---------------------------------------------------------------

template <typename T, size_t sz>
struct Node
{
    static constexpr size_t m_nChildrenMax = sz; 
                                           
    Node & operator = (const Node &node) = delete;
    Node (const Node &node)              = delete;
    
    Node();
    Node (Node *parent);
    Node (const T &key, Node *parent);
    
    Node *newChild (size_t nChild, const T& key);
    Node *newChild();

    template <typename ... ArgsT>
    void walk (void (*iteration)(const Node *node, ArgsT & ... args), ArgsT & ... args) const;

    const Node * const & operator [] (size_t n) const;
          Node *       & operator [] (size_t n);
    const Node *         getChild (size_t n) const;
          Node *         getChild (size_t n);

    void     setKey (const T& key);
    const T &getKey() const;
    int      getPreimageIndex() const;
    size_t   getDepth() const;
    Node    *getParent() const;
    
    size_t   trace (std::vector<Node *> &track) const;
    size_t   nChildren() const;
    bool     isLeaf() const;

    void graphvisTreeGenerate (const char *fileName) const;

    T            m_key;
    Node<T, sz> *m_parent;
    Node<T, sz> *m_childen[sz];
};

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
Node<T, sz> *Node<T, sz>::newChild()
{
    for (size_t i = 0; i < m_nChildrenMax; ++i)
    {
        if (m_childen[i] == nullptr)
            return m_childen[i] = new Node (this);
    }

    throw std::runtime_error ("All children are already alocated"); 
}

//---------------------------------------------------------------

template <typename T, size_t sz>
const Node<T, sz> * const & Node<T, sz>::operator [] (size_t n) const
{
    if (n >= m_nChildrenMax)
    {
        throw std::runtime_error ("Invalid index: " + std::to_string (n));
    }

    return m_childen[n];
}

//---------------------------------------------------------------

template <typename T, size_t sz>
Node<T, sz> *& Node<T, sz>::operator [] (size_t n)
{
    if (n >= m_nChildrenMax)
    {
        throw std::runtime_error ("Invalid index: " + std::to_string (n));
    }

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
size_t Node<T, sz>::trace (std::vector<Node<T, sz> *> &track) const
{
    Node  *curr  = m_parent;
    size_t count = getDepth() - 1;

    track.resize (count);
    for (int i = count - 1; i >= 0; --i)
    {
        track[i] = curr;
        curr = curr->m_parent;
    }
    
    return count;
}

//---------------------------------------------------------------

template <typename T, size_t sz>
int Node<T, sz>::getPreimageIndex() const
{
    for (int i = 0; i < m_nChildrenMax; ++i)
    {
        if (m_parent->getChild(i) == this)
            return i;
    }
    return -1;
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
