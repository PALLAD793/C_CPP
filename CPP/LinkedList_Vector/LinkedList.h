#ifndef AISDI_LINEAR_LINKEDLIST_H
#define AISDI_LINEAR_LINKEDLIST_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace aisdi
{

template <typename Type>
class LinkedList
{

public:
  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;
  using value_type = Type;
  using pointer = Type*;
  using reference = Type&;
  using const_pointer = const Type*;
  using const_reference = const Type&;

  class ConstIterator;
  class Iterator;
  class Node;
  using iterator = Iterator;
  using const_iterator = ConstIterator;

private:
  Node *first=nullptr, *last=nullptr, *newNode;
  size_type col_size=0;

public:
  LinkedList()
  {
    Node * guard = new Node();
    first = last = guard;
    guard->changeNextPtr(nullptr);
    guard->changePrevPtr(nullptr);
  }

  LinkedList(std::initializer_list<Type> l)
  : LinkedList()
  {
    for(auto it = l.begin(); it != l.end(); ++it)
        append(*it);

  }

  LinkedList(const LinkedList& other)
  : LinkedList()
  {
    for(ConstIterator it = other.begin(); it != other.end(); ++it)
    {
        this->append(*it);
    }

  }

  LinkedList(LinkedList&& other)
  :first(other.first)
  ,last(other.last)
  {
   other.first = nullptr;
   other.last = nullptr;

  }

  ~LinkedList()
  {
    if(first != nullptr)
    {
        while(first->getNext() != nullptr)
        {
            first = first->getNext();
            delete first->getPrev();
        }
        delete first;
    }
  }

  LinkedList& operator=(const LinkedList& other)
  {

    if(other.end() != this->end())
    {
        for(Node * ptr = this->first; ptr != this->last;)
        {
            Node * toDelete = ptr;
            ptr = ptr->getNext();
            delete toDelete;
        }
        this->first = this->last;
        col_size-=col_size;
        for(ConstIterator it = other.begin(); it != other.end(); ++it)
        {
            append(*it);
        }
    }
    return *this;
  }

  LinkedList& operator=(LinkedList&& other)
  {


    this->~LinkedList();
    this->first = other.first;
    this->last = other.last;
    this->col_size = other.col_size;
    other.last = nullptr;
    other.first = nullptr;
    other.col_size = 0;
    return *this;
  }

  bool isEmpty() const
  {
    return !col_size;
  }

  size_type getSize() const
  {
    return col_size;
  }

  void append(const Type& item)
  {
    if(first == last)
    {

        newNode = new Node(item);
        newNode->changeNextPtr(last);
        newNode->changePrevPtr(last->getPrev());
        last->changePrevPtr(newNode);
        first = newNode;
        first->changeNextPtr(last);
    }
    else
    {
        newNode = new Node(item);
        (last->getPrev())->changeNextPtr(newNode);
        newNode->changeNextPtr(last);
        newNode->changePrevPtr(last->getPrev());
        last->changePrevPtr(newNode);
    }
    col_size++;
  }

  void prepend(const Type& item)
  {

    newNode = new Node(item);
    newNode->changeNextPtr(first);
    newNode->changePrevPtr(first->getPrev());
    first->changePrevPtr(newNode);
    first = newNode;

    col_size++;
  }

  void insert(const const_iterator& insertPosition, const Type& item)
  {

    Iterator itInsertPosition(insertPosition);
    if(itInsertPosition.getCurrent()->getPrev() == nullptr)
    {
        prepend(item);
    }
    else
    {
        newNode = new Node(item);
        Iterator itBeforeInsertPosition = itInsertPosition-1;
        itBeforeInsertPosition.getCurrent()->changeNextPtr(newNode);
        itInsertPosition.getCurrent()->changePrevPtr(newNode);
        newNode->changeNextPtr(itInsertPosition.getCurrent());
        newNode->changePrevPtr(itBeforeInsertPosition.getCurrent());
        col_size++;
    }
  }

  Type popFirst()
  {

   if(first != last)
   {
        Iterator afterPop(this->begin());
        first = afterPop.getCurrent()->getNext();
        afterPop.getCurrent()->getNext()->changePrevPtr(nullptr);
        afterPop.getCurrent()->changeNextPtr(nullptr);
        col_size--;
        Type val = *(afterPop.getCurrent()->getPointerToValue());
        Node * toDelete = afterPop.getCurrent();
        delete toDelete;
        return val;
    }
    else throw std::logic_error("Pop first when empty");
  }

  Type popLast()
  {

   if(first != last)
   {
        ConstIterator itPop(this->end());
        --itPop;
        if(itPop.getCurrent()->getPrev() == nullptr)
        {
            last->changePrevPtr(nullptr);
            itPop.getCurrent()->changeNextPtr(nullptr);
            col_size--;
            first=last;
            Type val= *(itPop.getCurrent()->getPointerToValue());
            Node * toDelete = itPop.getCurrent();
            delete toDelete;
            return val;

        }
        else
        {
            last->changePrevPtr(itPop.getCurrent()->getPrev());
            itPop.getCurrent()->getPrev()->changeNextPtr(last);
            itPop.getCurrent()->changeNextPtr(nullptr);
            itPop.getCurrent()->changePrevPtr(nullptr);
            col_size--;
            Type val= *(itPop.getCurrent()->getPointerToValue());
            Node * toDelete = itPop.getCurrent();
            delete toDelete;
            return val;

        }

   }
   else throw std::logic_error("Pop last when empty");
  }

  void erase(const const_iterator& possition)
  {

    if(first != last && possition != this->end())
    {
        Iterator itErase(possition);
        if(itErase.getCurrent()->getPrev() == nullptr)
        {
            popFirst();
        }
        else
        {
            itErase.getCurrent()->getNext()->changePrevPtr(itErase.getCurrent()->getPrev());
            itErase.getCurrent()->getPrev()->changeNextPtr(itErase.getCurrent()->getNext());
            itErase.getCurrent()->changeNextPtr(nullptr);
            itErase.getCurrent()->changePrevPtr(nullptr);
            Node * toDelete = itErase.getCurrent();
            delete toDelete;
            --col_size;
        }
    }
    else if(first == last) throw std::out_of_range("Erase when empty");
    else throw std::out_of_range("Erase guard");
  }

  void erase(const const_iterator& firstIncluded, const const_iterator& lastExcluded)
  {

    Iterator itFirstIncluded(firstIncluded);
    Iterator itLastExcluded(lastExcluded);
    while(itFirstIncluded != itLastExcluded)
    {
        erase(itFirstIncluded++);

    }
   }



  iterator begin()
  {
    Iterator it = Iterator();
    it.setCurrent(first);
    return it;
  }

  iterator end()
  {

    Iterator it = Iterator();
    it.setCurrent(last);
    return it;

  }

  const_iterator cbegin() const
  {
    ConstIterator it = ConstIterator();
    it.setCurrent(first);
    return it;
  }

  const_iterator cend() const
  {

    ConstIterator it = ConstIterator();
    it.setCurrent(last);
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

template <typename Type>
class LinkedList<Type>::Node
{
public:
  using value_type = Type;
  using pointer = Type*;
  using reference = Type&;

  Node(const Type& item)
  {
    value = new Type(item);
  }
  Node()
  {
    value = nullptr;
  }

  ~Node()
  {
    if(value != nullptr)
      delete value;
  }

  void changeNextPtr(Node* new_point)
  {
    next = new_point;
  }

  void changePrevPtr(Node* new_point)
  {
    prev = new_point;
  }

  pointer getPointerToValue()
  {
    return value;
  }

  Node* getNext()
  {
    return next;
  }

  Node* getPrev()
  {
    return prev;
  }

private:
   Node *next, *prev;
   pointer value;
};

template <typename Type>
class LinkedList<Type>::ConstIterator
{
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = typename LinkedList::value_type;
  using difference_type = typename LinkedList::difference_type;
  using pointer = typename LinkedList::const_pointer;
  using reference = typename LinkedList::const_reference;


  explicit ConstIterator()
  {}

  void setCurrent(Node* newCurrent)
  {
    current = newCurrent;
  }
  Node* getCurrent()
  {
    return current;
  }
  reference operator*() const
  {
    if(this->current->getNext() != nullptr)
        return *(this->current->getPointerToValue());
    else throw std::out_of_range("Guard_value");
  }

  ConstIterator& operator++()
  {
    if(current != nullptr && current->getNext() != nullptr)
    {
        current = current->getNext();
        return *this;
    }
    else throw std::out_of_range("FAIL");
  }

  ConstIterator operator++(int)
  {
    ConstIterator prevIter = *this;
    ++(*this);
    return prevIter;
  }

  ConstIterator& operator--()
  {
    if(current != nullptr && current->getPrev() != nullptr)
    {
        current = current->getPrev();
        return *this;
    }
    else throw std::out_of_range("FAIL");
  }

  ConstIterator operator--(int)
  {
    ConstIterator postIter = *this;
    --(*this);
    return postIter;
  }

  ConstIterator operator+(difference_type d) const
  {
    ConstIterator ptr = *this;
    if(d>0)
    {
        while(d>0)
        {
            ++ptr;
            --d;
        }
    }
    else
    {
        while(d<0)
        {
            --ptr;
            ++d;
        }
    }
    return ptr;
  }

  ConstIterator operator-(difference_type d) const
  {
    ConstIterator ptr = *this;
    if(d>0)
    {
        while(d>0)
        {
            --ptr;
            --d;
        }
    }
    else
    {
        while(d<0)
        {
            ++ptr;
            ++d;
        }
    }
    return ptr;
  }

  bool operator==(const ConstIterator& other) const
  {
    return (this->current == other.current);
  }

  bool operator!=(const ConstIterator& other) const
  {
    return (this->current != other.current);
  }
  private:
  Node *current;
};

template <typename Type>
class LinkedList<Type>::Iterator : public LinkedList<Type>::ConstIterator
{
public:
  using pointer = typename LinkedList::pointer;
  using reference = typename LinkedList::reference;

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

  Iterator operator+(difference_type d) const
  {
    return ConstIterator::operator+(d);
  }

  Iterator operator-(difference_type d) const
  {
    return ConstIterator::operator-(d);
  }

  reference operator*() const
  {
    // ugly cast, yet reduces code duplication.
    return const_cast<reference>(ConstIterator::operator*());
  }
};

}

#endif // AISDI_LINEAR_LINKEDLIST_H
