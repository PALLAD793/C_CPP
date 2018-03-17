#ifndef AISDI_LINEAR_VECTOR_H
#define AISDI_LINEAR_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <cstring>

namespace aisdi
{

template <typename Type>
class Vector
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
  using iterator = Iterator;
  using const_iterator = ConstIterator;

private:
  size_type capacity = 64; // minimum 2
  size_type vec_size=0;
  pointer tab;
  char* buf;

public:
  Vector()
  {
    buf = new char[capacity*sizeof(Type)];
    tab = reinterpret_cast<pointer>(buf);
  }

  Vector(std::initializer_list<Type> l)
  :Vector()
  {

    for(const Type* it = l.begin(); it != l.end(); ++it)
    {
        append(*it);
    }
  }

  Vector(const Vector& other)
  :Vector()
  {

    for(ConstIterator it = other.begin(); it != other.end(); ++it)
    {
        this->append(*it);
    }
  }

  Vector(Vector&& other)
  :Vector()
  {
    tab = other.tab;
    vec_size = other.vec_size;
    other.tab = nullptr;
    other.buf = nullptr;
  }

  ~Vector()
  {
    if(tab != nullptr)
    {
        for(size_type i=0; i<vec_size; i++)
        {
            tab[i].~Type();
        }
        delete[] buf;
    }
  }

  Vector& operator=(const Vector& other)
  {

    if(tab != other.tab)
    {

        vec_size -= vec_size;
        for(ConstIterator it = other.begin(); it != other.end(); ++it)
        {
            append(*it);
        }
    }
    return *this;
  }

  Vector& operator=(Vector&& other)
  {

    if(tab != nullptr)
    {
        for(size_type i=0; i<vec_size; i++)
        {
            tab[i].~Type();
        }
        delete[] buf;
    }

    buf=other.buf;
    tab = other.tab;
    vec_size = other.vec_size;
    other.tab = nullptr;
    other.buf = nullptr;

    return *this;
  }

  void allocTable(size_type cap)
  {
    capacity = cap;
    char* tmp= new char[capacity*sizeof(Type)];
    Type* t1 = reinterpret_cast<Type*>(tmp);
    std::memcpy(t1, buf, vec_size*sizeof(Type));  	
    for(size_type i=0; i<vec_size; i++)
    {
        tab[i].~Type();
    }

    delete[] buf;
    buf = tmp;
    tab = t1;
  }

  bool isEmpty() const
  {
   return !vec_size;
  }

  size_type getSize() const
  {
    return vec_size;
  }

  void append(const Type& item)
  {
    new (tab+vec_size)Type(item);
    ++vec_size;

    if(vec_size == capacity-1) allocTable(capacity*2);
  }

  void prepend(const Type& item)
  {
    
    ++vec_size;
    new (tab+vec_size)Type(*(tab+vec_size-1));
    for(size_type i = vec_size-1; i>0; --i)
    {
        *(tab+i) = *(tab+i-1);
    }
    *tab = item;

    if(vec_size == capacity-1) allocTable(capacity*2);
  }

  void insert(const const_iterator& insertPosition, const Type& item)
  {

    if(insertPosition == end())
    {
        append(item);
    }
    else
    {
        new(tab+vec_size)Type(*(tab+vec_size-1));
        Iterator it = end()-1;
        for(; it != insertPosition; --it)
        {
            *it = *(it-1);
        }
        ++vec_size;
        *it = item;

        if(vec_size == capacity-1) allocTable(capacity*2);
    }
  }

  Type popFirst()
  {

    if(vec_size != 0)
    {
        Type val = *(begin());
        for(Iterator it=begin(); it != end()-1; ++it)
        {
            *it = *(it+1);
        }
        (*(tab+vec_size-1)).~Type();
        --vec_size;
        return val;
    }
    else throw std::logic_error("Pop first empty");
  }

  Type popLast()
  {

    if(vec_size != 0)
    {
        Type val = *(tab+vec_size-1);
        (*(tab+vec_size-1)).~Type();
        --vec_size;
        return val;
    }
    else throw std::logic_error("Pop last empty");
  }

  void erase(const const_iterator& possition)
  {

    if(vec_size != 0 || possition != end())
    {
        if(possition == begin())
        {
            popFirst();
        }
        else if(possition == end()-1) popLast();
        else
        {
            for(Iterator it = possition; it != end()-1; ++it)
            {
                *(it) = *(it+1);
            }
            --vec_size;
            (*(tab+vec_size)).~Type();
        }
    }
    else throw std::out_of_range("Erase when empty or end");
  }

  void erase(const const_iterator& firstIncluded, const const_iterator& lastExcluded)
  {

    if(vec_size != 0 || firstIncluded != end())
    {
        if(firstIncluded != lastExcluded)
        {
            Iterator firstIn = firstIncluded;
            for(Iterator lastEx = lastExcluded; lastEx != end(); ++lastEx)
            {
                *(firstIn) = *(lastEx);
                ++firstIn;
            }
            while(firstIn != end())
            {
                (*(tab+vec_size-1)).~Type();
                --vec_size;
            }


        }
    }
    else throw std::out_of_range("Erase many when empty or end");
  }

  iterator begin()
  {
    iterator it(*this);
    it.setCurrent(tab);
    return it;
  }

  iterator end()
  {
    iterator it(*this);
    it.setCurrent(tab+vec_size);
    return it;
  }

  const_iterator cbegin() const
  {
   const_iterator it(*this);
   it.setCurrent(tab);
   return it;
  }

  const_iterator cend() const
  {
    const_iterator it(*this);
    it.setCurrent(tab+vec_size);
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
class Vector<Type>::ConstIterator
{
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = typename Vector::value_type;
  using difference_type = typename Vector::difference_type;
  using pointer = typename Vector::const_pointer;
  using reference = typename Vector::const_reference;

private:
  pointer current=nullptr;
  const Vector<Type>& vect;

public:
  explicit ConstIterator()
  {}

  ConstIterator(const Vector<Type>& vec)
  :vect(vec)
  {
  }

  void setCurrent(pointer newCurrent)
  {
    current = newCurrent;
  }

  pointer getCurrent()
  {
    return current;
  }

  reference operator*() const
  {
    if(current >= vect.tab && current < vect.tab+vect.vec_size)
      return *(this->current);
    else throw std::out_of_range("Operator*");
  }

  ConstIterator& operator++()
  {
    if(current != (vect.tab+vect.vec_size) )
    {
        setCurrent(current+1);
        return *this;
    }
    else throw std::out_of_range("Increment");
  }

  ConstIterator operator++(int)
  {
    ConstIterator prevIt = *this;
    ++(*this);
    return prevIt;
  }

  ConstIterator& operator--()
  {
    if(current != vect.tab)
    {
        setCurrent(current-1);
        return *this;
    }
    else throw std::out_of_range("Decrement");
  }

  ConstIterator operator--(int)
  {
    ConstIterator prevIt = *this;
    --(*this);
    return prevIt;
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

    return(this->current == other.current);
  }

  bool operator!=(const ConstIterator& other) const
  {

    return (this->current != other.current);
  }

};

template <typename Type>
class Vector<Type>::Iterator : public Vector<Type>::ConstIterator
{
public:
  using pointer = typename Vector::pointer;
  using reference = typename Vector::reference;

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

#endif // AISDI_LINEAR_VECTOR_H
