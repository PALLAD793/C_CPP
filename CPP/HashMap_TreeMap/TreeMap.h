#ifndef AISDI_MAPS_TREEMAP_H
#define AISDI_MAPS_TREEMAP_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <algorithm>

namespace aisdi
{

template <typename KeyType, typename ValueType>
class TreeMap
{
public:
  using key_type = KeyType;
  using mapped_type = ValueType;
  using value_type = std::pair<const key_type, mapped_type>;
  using size_type = std::size_t;
  using reference = value_type&;
  using const_reference = const value_type&;

private:
  class Node;
  Node* root=nullptr;
  size_type nodeAmount=0;

  Node* nastepnik(Node* bigger)
  {
    if(bigger->getLeftSon() == nullptr)
	return bigger;
    Node* nastepny = bigger->getLeftSon();
    while(nastepny->getRightSon() != nullptr)
    {
        nastepny = nastepny->getRightSon();
    }

    Node* par, *left, *right;
    par = bigger->getParent();
    left = bigger->getLeftSon();
    right = bigger->getRightSon();
    if(par != nullptr)
    {
        if(par->getRightSon() == bigger)
        {
            par->setRightSon(nastepny);
        }
        else
        {
            par->setLeftSon(nastepny);
        }
    }
    if(left != nastepny)
    {
        left->setParent(nastepny);
    }
    else
    {
        left->setParent(par);
    }
    right->setParent(nastepny);
    if(left != nastepny)
    {
        bigger->setParent(nastepny->getParent());
    }
    else
    {
        bigger->setParent(nastepny);
    }

    bigger->setRightSon(nastepny->getRightSon());
    bigger->setLeftSon(nastepny->getLeftSon());

    if(nastepny->getParent() != bigger && nastepny->getParent() != nullptr)
    {
        if(nastepny->getParent()->getRightSon() == nastepny)
        {
            nastepny->getParent()->setRightSon(bigger);
        }
        else
        {
            nastepny->getParent()->setLeftSon(bigger);
        }
    }

    nastepny->setParent(par);

    nastepny->getLeftSon()->setParent(bigger);
    nastepny->setLeftSon(left);

    nastepny->setRightSon(right);

    if(nastepny->getLeftSon() != nullptr)
    {
        return nastepnik(nastepny);
    }
    else
    {
        return nastepny;
    }
  }

  void visitDelete(Node* rt)
  {
    if(rt != nullptr)
    {
	visitDelete(rt->getLeftSon());
        visitDelete(rt->getRightSon());
	delete rt;
    }
    else return;
  }

  void visitCopy(Node* rt)
  {
    if(rt != nullptr)
    {
	(*this)[rt->getPair().first] = rt->getPair().second;
	visitCopy(rt->getLeftSon());
        visitCopy(rt->getRightSon());
    }
    else return;
  }

public:
  class ConstIterator;
  class Iterator;
  using iterator = Iterator;
  using const_iterator = ConstIterator;

  TreeMap()
  {
  }

  ~TreeMap()
  {

    if(root != nullptr)
    {
    	visitDelete(root);
	root = nullptr;
    }

  }

  TreeMap(std::initializer_list<value_type> list)
  {
    for(auto it = list.begin(); it != list.end(); ++it)
    {
        (*this)[it->first] = it->second;
    }
  }

  TreeMap(const TreeMap& other)
  {

    visitCopy(other.root);

  }

  TreeMap(TreeMap&& other)
  {
    root = other.root;
    nodeAmount = other.nodeAmount;
    other.root = nullptr;
    other.nodeAmount = 0;
  }

  TreeMap& operator=(const TreeMap& other)
  {
    if(this->root != other.root)
    {
	if(root != nullptr) visitDelete(this->root);
	root = nullptr;
        nodeAmount = 0;

	visitCopy(other.root);
    }
    return *this;
  }

  TreeMap& operator=(TreeMap&& other)
  {
    if(this != &other)
    {
	if(root != nullptr) visitDelete(this->root);
        root = other.root;
        nodeAmount = other.nodeAmount;
        other.root = nullptr;
        other.nodeAmount = 0;
    }
    return *this;
  }

  bool isEmpty() const
  {
    return !nodeAmount;
  }

  mapped_type& operator[](const key_type& key)
  {
    Node* findNode=root, *prev;
    key_type addKey = key;
    if(root == nullptr)
    {
        Node* newNode = new Node(addKey);
        root = newNode;

        findNode = root;
        ++nodeAmount;
    }
    else
    {
        while(findNode != nullptr && findNode->getPair().first != key)
        {
            prev = findNode;
            if(findNode->getPair().first < key)
            {
                findNode = findNode->getRightSon();
            }
            else
            {
                findNode = findNode->getLeftSon();
            }
        }
        if(findNode == nullptr)
        {
            Node* newNode = new Node(addKey);
            if(prev->getPair().first < key)
            {
                prev->setRightSon(newNode);
                newNode->setParent(prev);
                ++nodeAmount;

            }
            else
            {
                prev->setLeftSon(newNode);
                newNode->setParent(prev);
                ++nodeAmount;
            }
            findNode = newNode;
        }

    }

    return findNode->getValue();
  }

  const mapped_type& valueOf(const key_type& key) const
  {
    ConstIterator valueOf(*this);
    valueOf.setCurrent((this->find(key)).getCurrent());
    if(valueOf.getCurrent() == nullptr)
    {
        throw std::out_of_range("valueOf");
    }
    return valueOf->second;
  }

  mapped_type& valueOf(const key_type& key)
  {
    Iterator valueOf(*this);
    valueOf.setCurrent((this->find(key)).getCurrent());
    if(valueOf.getCurrent() == nullptr)
    {
        throw std::out_of_range("valueOf");
    }
    return valueOf->second;
  }

  const_iterator find(const key_type& key) const
  {

    ConstIterator it(*this);
    Node* findNode = root;

    while(findNode != nullptr && findNode->getPair().first != key)
    {
        if(findNode->getPair().first < key)
        {
            findNode = findNode->getRightSon();
        }
        else
        {
            findNode = findNode->getLeftSon();
        }

    }
    it.setCurrent(findNode);
    return it;
  }

  iterator find(const key_type& key)
  {

    Iterator it(*this);
    Node* findNode = root;

    while(findNode != nullptr && findNode->getPair().first != key)
    {
        if(findNode->getPair().first < key)
        {
            findNode = findNode->getRightSon();
        }
        else
        {
            findNode = findNode->getLeftSon();
        }

    }
    it.setCurrent(findNode);
    return it;
  }

  void remove(const key_type& key)
  {

    remove(find(key));
  }

  void remove(const const_iterator& it)
  {

    Node* toRemove = it.getCurrent();
    if(it == cend())
        throw std::out_of_range("Remove");
    else
    {

        if(nodeAmount == 1)
        {
            root = nullptr;
            --nodeAmount;
            delete toRemove;
            return;
        }

        if(toRemove->getLeftSon() == nullptr && toRemove->getRightSon() == nullptr)
        {
            if(toRemove == root)
            {
                root = nullptr;
            }
            if(toRemove == toRemove->getParent()->getLeftSon())
            {
                toRemove->getParent()->setLeftSon(nullptr);
            }
            else
            {
                toRemove->getParent()->setRightSon(nullptr);
            }

            --nodeAmount;
            delete toRemove;
            return;
        }

        if(toRemove->getLeftSon() != nullptr && toRemove->getRightSon() == nullptr)
        {
            if(toRemove != root)
            {
                if(toRemove == toRemove->getParent()->getLeftSon())
                {
                    toRemove->getParent()->setLeftSon(toRemove->getLeftSon());
                }
                else
                {
                    toRemove->getParent()->setRightSon(toRemove->getLeftSon());
                }
            }
            else
            {
                root = toRemove->getLeftSon();
            }

            --nodeAmount;
            delete toRemove;
            return;
        }

        if(toRemove->getLeftSon() == nullptr && toRemove->getRightSon() != nullptr)
        {
            if(toRemove != root)
            {
                if(toRemove == toRemove->getParent()->getLeftSon())
                {
                    toRemove->getParent()->setLeftSon(toRemove->getRightSon());
                }
                else
                {
                    toRemove->getParent()->setRightSon(toRemove->getRightSon());
                }
            }
            else
            {
                root = toRemove->getRightSon();
            }

            --nodeAmount;
           delete toRemove;
            return;
        }

        if(toRemove->getLeftSon() != nullptr && toRemove->getRightSon() != nullptr)
        {
            toRemove = nastepnik(toRemove);
            --nodeAmount;
            delete toRemove;
            return;
        }
    }
  }

  size_type getSize() const
  {
    return nodeAmount;
  }

  bool operator==(const TreeMap& other) const
  {
   // (void)other;
   // throw std::runtime_error("TODO");
   if(this->nodeAmount == other.nodeAmount)
   {
        if(nodeAmount == 0) return 1;
        ConstIterator checkT(other);
        checkT.setCurrent(other.cbegin().getCurrent());
        ConstIterator it(*this);
        while(checkT.getCurrent() != nullptr)
        {
            Node* found = this->find(checkT->first).getCurrent();
            if(found == nullptr) return 0;
            it.setCurrent(found);
            if(checkT->second != it->second) return 0;
            ++checkT;
        }
        return 1;
    }
    else return 0;
}

  bool operator!=(const TreeMap& other) const
  {
    return !(*this == other);
  }

  iterator begin()
  {
    //throw std::runtime_error("TODO");
    Node* findNode = root;
    if(findNode != nullptr)
    {
        while(findNode->getLeftSon() != nullptr)
        {
            findNode = findNode->getLeftSon();
        }
    }
    Iterator it(*this);
    it.setCurrent(findNode);
    return it;
  }

  iterator end()
  {
    //throw std::runtime_error("TODO");
    Node* findNode = root;
    if(findNode != nullptr)
    {
        while(findNode != nullptr)
        {
            findNode = findNode->getRightSon();
        }
    }
    Iterator it(*this);
    it.setCurrent(findNode);
    return it;
  }

  const_iterator cbegin() const
  {
    //throw std::runtime_error("TODO");
    Node* findNode = root;
    if(findNode != nullptr)
    {
        while(findNode->getLeftSon() != nullptr)
        {
            findNode = findNode->getLeftSon();
        }
    }
    ConstIterator it(*this);
    it.setCurrent(findNode);
    return it;
  }

  const_iterator cend() const
  {
    //throw std::runtime_error("TODO");
    Node* findNode = root;
    if(findNode != nullptr)
    {
        while(findNode != nullptr)
        {
            findNode = findNode->getRightSon();
        }
    }
    ConstIterator it(*this);
    it.setCurrent(findNode);
    return it;
  }

  const_iterator begin() const
  {
    return cbegin();
  }

  const_iterator end() const
  {
    return cend();
  }
};

template <typename KeyType, typename ValueType>
class TreeMap<KeyType, ValueType>::Node
{
public:
  using key_type = KeyType;
  using mapped_type = ValueType;
  using value_type = std::pair<const key_type, mapped_type>;
  using size_type = std::size_t;
  using reference = value_type&;
  using const_reference = const value_type&;

private:
  Node* leftSon = nullptr;
  Node* rightSon = nullptr;
  Node* parent = nullptr;
  value_type values;

public:

  Node(const key_type key)
  : values(key, mapped_type())
  {
  }

  ~Node()
  {
   // values.~pair();
   //values.second.~mapped_type();
  }

  Node* getLeftSon()
  {
    return leftSon;
  }

  Node* getRightSon()
  {
    return rightSon;
  }

  Node* getParent()
  {
    return parent;
  }

  void setLeftSon(Node* son)
  {
    leftSon = son;
  }

  void setRightSon(Node* son)
  {
    rightSon = son;
  }

  void setParent(Node* newParent)
  {
    parent = newParent;
  }

  void setKey(key_type& k)
  {
    values.first = k;
  }

  mapped_type& getValue()
  {
    return values.second;
  }

  const_reference getPair()
  {
    return values;
  }
};

template <typename KeyType, typename ValueType>
class TreeMap<KeyType, ValueType>::ConstIterator
{
private:
  Node* current;
  const TreeMap<KeyType, ValueType>& myTree;
public:
  using reference = typename TreeMap::const_reference;
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = typename TreeMap::value_type;
  using pointer = const typename TreeMap::value_type*;

  explicit ConstIterator()
  {}

  ConstIterator(const TreeMap<KeyType, ValueType>& tree)
  : myTree(tree)
  {
  }

/*  ConstIterator(const ConstIterator& other)
  : current(other.current)
  {
   // (void)other;
   // throw std::runtime_error("TODO");
  }*/

  void setCurrent(Node* cur)
  {
    current = cur;
  }

  Node* getCurrent() const
  {
    return current;
  }

  ConstIterator& operator++()
  {
   // throw std::runtime_error("TODO");
   if(current == nullptr)
   {
    throw std::out_of_range("Decrement");
   }
   else
   {
        if(current->getRightSon() != nullptr)
        {
            current = current->getRightSon();
            while(current->getLeftSon() != nullptr)
            {
                current = current->getLeftSon();
            }
            return *this;
        }
        else
        {
            Node* findNode = myTree.root;
            while(findNode->getRightSon() != nullptr)
            {
                findNode = findNode->getRightSon();
            }
            if(findNode == current)
            {
                current = myTree.cend().current;
                return *this;
            }
            findNode = current;
            while(findNode->getParent() != nullptr && findNode != findNode->getParent()->getLeftSon())
            {
                findNode = findNode->getParent();
            }
            findNode = findNode->getParent();
            current = findNode;
            return *this;
        }
   }

  }

  ConstIterator operator++(int)
  {
    //throw std::runtime_error("TODO");
    ConstIterator prev = *this;
    ++(*this);
    return prev;
  }

  ConstIterator& operator--()
  {
   // throw std::runtime_error("TODO");
    if(current == nullptr && myTree.root != nullptr)
    {
        Node* findNode = myTree.root;
        while(findNode->getRightSon() != nullptr)
        {
            findNode = findNode->getRightSon();
        }
        current = findNode;
        return *this;
    }
    else if(this->current != (myTree.cbegin()).current)
    {
        if(this->current->getLeftSon() != nullptr)
        {
            current = current->getLeftSon();
            return *this;
        }
        else
        {
            Node* findNode = current;
            findNode = findNode->getParent();
            while(findNode != myTree.cbegin().current)
            {
                if(findNode->getLeftSon() != nullptr)
                {
                    findNode = findNode->getLeftSon();
                    current = findNode;
                    return *this;
                }
                else
                {
                    findNode = findNode->getParent();
                }
            }
            return *this;
        }
    }
    else throw std::out_of_range("Decrement");

  }

  ConstIterator operator--(int)
  {
    //throw std::runtime_error("TODO");
    ConstIterator prev = *this;
    --(*this);
    return prev;
  }

  reference operator*() const
  {
   // throw std::runtime_error("TODO");
    if(this->current != nullptr)
    {
      return this->current->getPair();
    }
    else throw std::out_of_range("Operator*");
  }

  pointer operator->() const
  {
    return &this->operator*();
  }

  bool operator==(const ConstIterator& other) const
  {
 //   (void)other;
   // throw std::runtime_error("TODO");
   return (this->current == other.current);
  }

  bool operator!=(const ConstIterator& other) const
  {
    return !(this->current == other.current);
  }
};

template <typename KeyType, typename ValueType>
class TreeMap<KeyType, ValueType>::Iterator : public TreeMap<KeyType, ValueType>::ConstIterator
{
public:
  using reference = typename TreeMap::reference;
  using pointer = typename TreeMap::value_type*;

  explicit Iterator()
  {}

  Iterator(const ConstIterator& other)
    : ConstIterator(other)
  {}

  Iterator& operator++()
  {
    ConstIterator::operator++();
    return *this;
  }

  Iterator operator++(int)
  {
    auto result = *this;
    ConstIterator::operator++();
    return result;
  }

  Iterator& operator--()
  {
    ConstIterator::operator--();
    return *this;
  }

  Iterator operator--(int)
  {
    auto result = *this;
    ConstIterator::operator--();
    return result;
  }

  pointer operator->() const
  {
    return &this->operator*();
  }

  reference operator*() const
  {
    // ugly cast, yet reduces code duplication.
    return const_cast<reference>(ConstIterator::operator*());
  }
};

}

#endif /* AISDI_MAPS_MAP_H */
