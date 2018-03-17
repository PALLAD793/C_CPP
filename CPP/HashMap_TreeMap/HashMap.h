#ifndef AISDI_MAPS_HASHMAP_H
#define AISDI_MAPS_HASHMAP_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <functional>

#define SIZE 56789

namespace aisdi
{

template <typename KeyType, typename ValueType>
class HashMap
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
  Node* table[SIZE] = {};
  size_type hashMapSize = 0;
  std::hash<key_type> hashFnc;

public:
  class ConstIterator;
  class Iterator;
  using iterator = Iterator;
  using const_iterator = ConstIterator;

  HashMap()
  {}

  HashMap(std::initializer_list<value_type> list)
  {
    for(auto it = list.begin(); it != list.end(); ++it)
    {
        (*this)[it->first] = it->second;
    }
  }

  HashMap(const HashMap& other)
  {
    for(Iterator it = other.begin(); it != other.end(); ++it)
    {
        (*this)[it->first] = it->second;
    }
  }

  HashMap(HashMap&& other)
  {
    for(size_type i = 0; i<SIZE; ++i)
    {
        table[i] = other.table[i];
        other.table[i] = nullptr;
    }
    hashMapSize = other.hashMapSize;
    other.hashMapSize = 0;
  }

  ~HashMap()
  {
    for(size_type i = 0; i<SIZE; ++i)
    {
        Node* toRemove = table[i];
        while(toRemove != nullptr && toRemove->getNext() != nullptr)
        {
            toRemove = toRemove->getNext();
	    delete toRemove->getPrev();
	    toRemove->changePrevPtr(nullptr);
            --hashMapSize;
        }
        if(toRemove != nullptr)
        {
	    delete toRemove;
            --hashMapSize;
        }
	toRemove = nullptr;
	table[i] = nullptr;
    }
  }

  HashMap& operator=(const HashMap& other)
  {
        if(this != &other)
        {

	    for(size_type i = 0; i<SIZE; ++i)
	    {
		Node* toRemove = table[i];
		while(toRemove != nullptr && toRemove->getNext() != nullptr)
		{
		    toRemove = toRemove->getNext();
		    delete toRemove->getPrev();
		    toRemove->changePrevPtr(nullptr);
		    --hashMapSize;
		}
		if(toRemove != nullptr)
		{
		    delete toRemove;
		    --hashMapSize;
		}
		toRemove = nullptr;
		table[i] = nullptr;
	    }

	
        for(Iterator it = other.begin(); it != other.end(); ++it)
        {
            (*this)[it->first] = it->second;
        }
    }
    return *this;
  }

  HashMap& operator=(HashMap&& other)
  {

    if(this != &other)
    {

	for(size_type i = 0; i<SIZE; ++i)
    {
        Node* toRemove = table[i];
        while(toRemove != nullptr && toRemove->getNext() != nullptr)
        {
            toRemove = toRemove->getNext();
	    delete toRemove->getPrev();
	    toRemove->changePrevPtr(nullptr);
            --hashMapSize;
        }
        if(toRemove != nullptr)
        {
	    delete toRemove;
            --hashMapSize;
        }
	toRemove = nullptr;
	table[i] = nullptr;
    }	

        for(size_type i = 0; i<SIZE; ++i)
        {
            table[i] = other.table[i];
            other.table[i] = nullptr;
        }
        hashMapSize = other.hashMapSize;
        other.hashMapSize = 0;
    }
    return *this;
  }

  bool isEmpty() const
  {
   return !hashMapSize;
  }

  mapped_type& operator[](const key_type& key)
  {
    size_type hashed = hashFnc(key)%SIZE;

    if(table[hashed] != nullptr)
    {
        Node* findNode = table[hashed];
        while(findNode->getPair().first != key && findNode->getNext() != nullptr)
        {
            findNode = findNode->getNext();
        }

        if(findNode->getPair().first != key)
        {
            Node* newNode = new Node(key);
            findNode->changeNextPtr(newNode);
            newNode->changePrevPtr(findNode);
            ++hashMapSize;
            return newNode->getValue();
        }
        else
        {
            return findNode->getValue();
        }

    }
    else
    {
        Node* newNode = new Node(key);
        table[hashed] = newNode;
        ++hashMapSize;
        return newNode->getValue();
    }
  }

  const mapped_type& valueOf(const key_type& key) const
  {
    ConstIterator it(*this);
    it.setCurrent((find(key)).getCurrent());

    if(it.getCurrent() != nullptr)
    {
        return it.getCurrent()->getValue();
    }
    else throw std::out_of_range("ValueOf");
  }

  mapped_type& valueOf(const key_type& key)
  {
    Iterator it(*this);
    it.setCurrent((find(key)).getCurrent());

    if(it.getCurrent() != nullptr)
    {
        return it.getCurrent()->getValue();
    }
    else throw std::out_of_range("ValueOf");
  }

  const_iterator find(const key_type& key) const
  {
    size_type hashed = hashFnc(key)%SIZE;

    Node* temp = table[hashed];

    if(temp != nullptr)
    {
        while(temp != nullptr && temp->getPair().first != key)
        {
            temp = temp->getNext();
        }
    }

    ConstIterator it(*this);
    it.setCurrent(temp);

    return it;
  }

  iterator find(const key_type& key)
  {
    size_type hashed = hashFnc(key)%SIZE;

    Node* temp = table[hashed];

    if(temp != nullptr)
    {
        while(temp != nullptr && temp->getPair().first != key)
        {
            temp = temp->getNext();
        }
    }

    Iterator it(*this);
    it.setCurrent(temp);

    return it;
  }

  void remove(const key_type& key)
  {
  //  (void)key;
  //  throw std::runtime_error("TODO");
    remove(find(key));
  }

  void remove(const const_iterator& it)
  {
  //  (void)it;
  //  throw std::runtime_error("TODO");
    Node* toRemove = it.getCurrent();
    if(toRemove != nullptr)
    {
	size_type hashed = hashFnc(toRemove->getPair().first)%SIZE;
	if(table[hashed] == toRemove)
	{
	    table[hashed] = toRemove->getNext();
	}
        if(toRemove->getPrev() != nullptr)
        {
            toRemove->getPrev()->changeNextPtr(toRemove->getNext());
        }
        if(toRemove->getNext() != nullptr)
        {
            toRemove->getNext()->changePrevPtr(toRemove->getPrev());
        }
	delete toRemove;
	toRemove = nullptr;
        --hashMapSize;
    }
    else throw std::out_of_range("Remove");
  }

  size_type getSize() const
  {
    //throw std::runtime_error("TODO");
    return hashMapSize;
  }

  bool operator==(const HashMap& other) const
  {
  //  (void)other;
  //  throw std::runtime_error("TODO");
    if(this->hashMapSize == other.hashMapSize)
    {
        if(hashMapSize == 0) return 1;
        ConstIterator checkH(other);
        checkH.setCurrent(other.cbegin().getCurrent());
        ConstIterator it(*this);
        while(checkH.getCurrent() != nullptr)
        {
            Node* found = this->find(checkH->first).getCurrent();
            if(found == nullptr) return 0;
            it.setCurrent(found);
            if(checkH->second != it->second) return 0;
            ++checkH;
        }
        return 1;
     }
     else return 0;
  }

  bool operator!=(const HashMap& other) const
  {
    return !(*this == other);
  }

  iterator begin()
  {
    //throw std::runtime_error("TODO");
    Iterator it(*this);
    if(hashMapSize != 0)
    {
        size_type i=0;
        while(i < SIZE && table[i] == nullptr)
        {
            ++i;
        }
        it.setCurrent(table[i]);
    }
    return it;
  }

  iterator end()
  {
    //throw std::runtime_error("TODO");
    Iterator it(*this);
    return it;
  }

  const_iterator cbegin() const
  {
    //throw std::runtime_error("TODO");
    ConstIterator it(*this);
    if(hashMapSize != 0)
    {
        size_type i=0;
        while(i < SIZE && table[i] == nullptr)
        {
            ++i;
        }
        it.setCurrent(table[i]);
    }
    return it;
  }

  const_iterator cend() const
  {
  //  throw std::runtime_error("TODO");
    ConstIterator it(*this);
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
class HashMap<KeyType, ValueType>::Node
{
public:
  using key_type = KeyType;
  using mapped_type = ValueType;
  using value_type = std::pair<const key_type, mapped_type>;
  using size_type = std::size_t;
  using reference = value_type&;
  using const_reference = const value_type&;


  Node(const key_type& key)
  :value(key, mapped_type())
  {
  }

  ~Node()
  {
  }

  mapped_type& getValue()
  {
    return value.second;
  }

  void changeNextPtr(Node* new_point)
  {
    next = new_point;
  }

  void changePrevPtr(Node* new_point)
  {
    prev = new_point;
  }

  const_reference getPair()
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
   Node *next=nullptr, *prev=nullptr;
   value_type value;
};

template <typename KeyType, typename ValueType>
class HashMap<KeyType, ValueType>::ConstIterator
{
public:
  using reference = typename HashMap::const_reference;
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = typename HashMap::value_type;
  using pointer = const typename HashMap::value_type*;

private:
  const HashMap<KeyType, ValueType>& myMap;
  Node* current=nullptr;
  std::hash<key_type> hashFnc;

public:

  explicit ConstIterator()
  {}

  ConstIterator(const HashMap<KeyType, ValueType>& mapRef)
  :myMap(mapRef)
  {}

/*  ConstIterator(const ConstIterator& other)
  {
    (void)other;
    throw std::runtime_error("TODO");
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
    //throw std::runtime_error("TODO");
    if(current != nullptr)
    {
        if(current->getNext() != nullptr)
        {
            current = current->getNext();
        }
        else
        {
            size_type hashed = hashFnc(current->getPair().first)%SIZE;
            ++hashed;
            while(hashed < SIZE-1 && myMap.table[hashed] == nullptr)
            {
                ++hashed;
            }

            current = myMap.table[hashed];
        }
        return *this;
    }
    else throw std::out_of_range("Increment");
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
   if(current != nullptr)
   {
        if(current->getPrev() != nullptr)
        {
            current = current->getPrev();
        }
        else
        {
            size_type hashed = hashFnc(current->getPair().first)%SIZE;
            --hashed;
            while(hashed > 0 && myMap.table[hashed] == nullptr)
            {
                --hashed;
            }

            if(myMap.table[hashed] != nullptr)
            {
                Node* temp = myMap.table[hashed];
                while(temp->getNext() != nullptr)
                {
                    temp = temp->getNext();
                }

                current = temp;
            }
            else throw std::out_of_range("Decrement");
        }
    }
    else
    {
        size_type i=SIZE-1;
        while(i>0 && myMap.table[i] == nullptr)
        {
            --i;
        }

        if(myMap.table[i] != nullptr)
        {
            Node* temp = myMap.table[i];
            while(temp->getNext() != nullptr)
            {
                temp = temp->getNext();
            }
            current = temp;
        }
        else throw std::out_of_range("Decrement");
    }
    return *this;
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
    //throw std::runtime_error("TODO");
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
  //  (void)other;
   // throw std::runtime_error("TODO");
   return (this->current == other.current);
  }

  bool operator!=(const ConstIterator& other) const
  {
    return !(*this == other);
  }
};

template <typename KeyType, typename ValueType>
class HashMap<KeyType, ValueType>::Iterator : public HashMap<KeyType, ValueType>::ConstIterator
{
public:
  using reference = typename HashMap::reference;
  using pointer = typename HashMap::value_type*;

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

#endif /* AISDI_MAPS_HASHMAP_H */
