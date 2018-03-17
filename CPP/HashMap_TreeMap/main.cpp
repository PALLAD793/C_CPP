#include <cstddef>
#include <cstdlib>
#include <string>
#include <chrono>
#include <iostream>
#include <set>
#include <random>

#include "TreeMap.h"
#include "HashMap.h"

namespace
{

template <typename K, typename V>
using tMap = aisdi::TreeMap<K, V>;
template <typename K, typename V>
using hMap = aisdi::HashMap<K, V>;

void chooseKey(int table[], std::size_t repeatCount)
{
  std::set<int> mySet;
  std::set<int>::iterator it;
  std::size_t amount = 0, i = 0;

  std::default_random_engine generator;
  std::normal_distribution<double> distribution(6*repeatCount, 3*repeatCount);

  while(amount < repeatCount)
  {
    double number = distribution(generator);
    int num = std::round(number);
    it = mySet.find(num);
    if(it == mySet.end())
    {
        mySet.insert(num);
        table[i] = num;
        ++amount;
        ++i;
    }
  }
}

void hTest1(std::size_t repeatCount)
{
  hMap<int, std::string> myMap;
  auto start = std::chrono::system_clock::now();
  for(std::size_t i = 0; i < repeatCount; ++i)
  {
    myMap[i] = "test";
  }
  auto stop = std::chrono::system_clock::now();
  std::chrono::duration<double> diff = stop - start;
  std::cout << "Adding (HashMap): " << diff.count() << " sec\n";


  start = std::chrono::system_clock::now();
  for(std::size_t i = 0; i < repeatCount; ++i)
  {
    myMap.find(i);
  }
  stop = std::chrono::system_clock::now();
  diff = stop - start;
  std::cout << "Finding (HashMap): " << diff.count() << " sec\n";


  start = std::chrono::system_clock::now();
  for(std::size_t i = 0; i < repeatCount; ++i)
  {
    myMap.remove(repeatCount-i-1);
  }
  stop = std::chrono::system_clock::now();
  diff = stop - start;
  std::cout << "Remove (HashMap): " << diff.count() <<  " sec\n";
}

void tTest1(std::size_t repeatCount)
{
  int* table = (int*)malloc((repeatCount+1)*sizeof(int));
  chooseKey(table, repeatCount);
  tMap<int, std::string> myMap;
  auto start = std::chrono::system_clock::now();
  for(std::size_t i = 0; i < repeatCount; ++i)
  {
    std::size_t key = table[i];
    myMap[key] = "test";
  }
  auto stop = std::chrono::system_clock::now();
  std::chrono::duration<double> diff = stop - start;
  std::cout << "Adding (TreeMap): " << diff.count() << " sec\n";


  start = std::chrono::system_clock::now();
  for(std::size_t i = 0; i < repeatCount; ++i)
  {
    myMap.find(table[repeatCount-i-1]);
  }
  stop = std::chrono::system_clock::now();
  diff = stop - start;
  std::cout << "Finding (TreeMap): " << diff.count() << " sec\n";


  start = std::chrono::system_clock::now();
  for(std::size_t i = 0; i < repeatCount; ++i)
  {
    myMap.remove(table[repeatCount-i-1]);
  }
  stop = std::chrono::system_clock::now();
  diff = stop - start;
  std::cout << "Remove (TreeMap): " << diff.count() << " sec\n";

  free(table);
}

void hTest2(std::size_t repeatCount)
{
  hMap<int, std::string> myMap;
  for(std::size_t i = 0; i < repeatCount; ++i)
  {
    myMap[i] = "test";
  }
  auto start = std::chrono::system_clock::now();
  for(std::size_t i = 0; i < repeatCount; ++i)
  {
    myMap.find(i);
  }
  auto stop = std::chrono::system_clock::now();
  std::chrono::duration<double> diff = stop - start;
  std::cout << "Finding (HashMap): " << diff.count() << " sec\n";
}

void tTest2(std::size_t repeatCount)
{
  int* table = (int*)malloc((repeatCount+1)*sizeof(int));
  chooseKey(table, repeatCount);
  tMap<int, std::string> myMap;
  for(std::size_t i = 0; i < repeatCount; ++i)
  {
    std::size_t key = table[i];
    myMap[key] = "test";
  }
  auto start = std::chrono::system_clock::now();
  for(std::size_t i = 0; i < repeatCount; ++i)
  {
    myMap.find(table[repeatCount-i-1]);
  }
  auto stop = std::chrono::system_clock::now();
  std::chrono::duration<double> diff = stop - start;
  std::cout << "Finding (TreeMap): " << diff.count() << " sec\n";
  free(table);
}

void hTest3(std::size_t repeatCount)
{
  hMap<int, std::string> myMap;
  for(std::size_t i = 0; i < repeatCount; ++i)
  {
    myMap[i] = "test";
  }
  auto start = std::chrono::system_clock::now();
  for(std::size_t i = 0; i < repeatCount; ++i)
  {
    myMap.remove(repeatCount-i-1);
  }
  auto stop = std::chrono::system_clock::now();
  std::chrono::duration<double> diff = stop - start;
  std::cout << "Remove (HashMap): " << diff.count() <<  " sec\n";
}

void tTest3(std::size_t repeatCount)
{
  int* table = (int*)malloc((repeatCount+1)*sizeof(int));
  chooseKey(table, repeatCount);
  tMap<int, std::string> myMap;
  for(std::size_t i = 0; i < repeatCount; ++i)
  {
    std::size_t key = table[i];
    myMap[key] = "test";
  }
  auto start = std::chrono::system_clock::now();
  for(std::size_t i = 0; i < repeatCount; ++i)
  {
    myMap.remove(table[repeatCount-i-1]);
  }
  auto stop = std::chrono::system_clock::now();
  std::chrono::duration<double> diff = stop - start;
  std::cout << "Remove (TreeMap): " << diff.count() << " sec\n";
  free(table);
}

} // namespace

int main(int argc, char** argv)
{
  const std::size_t repeatCount = argc > 1 ? std::atoll(argv[1]) : 10000;

  hTest1(repeatCount);
  tTest1(repeatCount);
//  hTest2(repeatCount);
//  tTest2(repeatCount);
//  hTest3(repeatCount);
//  tTest3(repeatCount);
  return 0;
}
