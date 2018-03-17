#include <cstddef>
#include <cstdlib>
#include <string>
#include <iostream>
#include <ctime>
#include <iomanip>


#include "Vector.h"
#include "LinkedList.h"

namespace
{

template <typename T>
using LinearCollection = aisdi::LinkedList<T>;

template <typename T>
using VectorCollection = aisdi::Vector<T>;

void Test1_LL(std::size_t repeatCount)
{
  LinearCollection<int> col1;
  for (std::size_t i = 0; i < repeatCount; ++i)
    col1.append(12345);
}

void Test1_V(std::size_t repeatCount)
{
  VectorCollection<int> col2;
  for (std::size_t i = 0; i < repeatCount; ++i)
    col2.append(12345);
}

void Test2_LL(std::size_t repeatCount)
{
  LinearCollection<int> col1;
  for (std::size_t i = 0; i < repeatCount; ++i)
    col1.prepend(12345);
}

void Test2_V(std::size_t repeatCount)
{
  VectorCollection<int> col2;
  for (std::size_t i = 0; i < repeatCount; ++i)
    col2.prepend(12345);
}

void Test3_LL(std::size_t repeatCount)
{
  LinearCollection<int> col1;
  for (std::size_t i = 0; i < repeatCount; ++i)
    col1.append(12345);
  auto time1 = clock();
  for (std::size_t i = 0; i < repeatCount; ++i)
    col1.popFirst();
  time1 = clock() - time1;
  double t1 = 1.0*time1/CLOCKS_PER_SEC;
  std::cout << std::fixed << std::setprecision(2) << "PopFirst (LL / V): " << t1 << " / ";
}

void Test3_V(std::size_t repeatCount)
{
  VectorCollection<int> col2;
  for (std::size_t i = 0; i < repeatCount; ++i)
    col2.append(12345);
  auto time1 = clock();
  for (std::size_t i = 0; i < repeatCount; ++i)
    col2.popFirst();
  time1 = clock() - time1;
  double t1 = 1.0*time1/CLOCKS_PER_SEC;
  std::cout << std::fixed << std::setprecision(2) << t1 << std::endl;
}

} // namespace

int main(int argc, char* argv[])
{
  const std::size_t repeatCount = argc > 1 ? std::atoi(argv[1]) : 10000;
  auto time1 = clock();
    Test1_LL(repeatCount);
  time1 = clock() - time1;

  auto time2 = clock();
    Test1_V(repeatCount);
  time2 = clock() - time2;
  double t1 = 1.0*time1/CLOCKS_PER_SEC;
  double t2 = 1.0*time2/CLOCKS_PER_SEC;
  std::cout << std::fixed << std::setprecision(2) << "Append (LL / V): " << t1 << " / " << t2 << std::endl;

  double time3 = clock();
    Test2_LL(repeatCount);
  time3 = clock() - time3;


  auto time4 = clock();
    Test2_V(repeatCount);
  time4 = clock() - time4;
  double t3 = 1.0*time3/CLOCKS_PER_SEC;
  double t4 = 1.0*time4/CLOCKS_PER_SEC;
  std::cout << std::fixed << std::setprecision(2) << "Prepend (LL / V): " << t3 << " / " << t4 << std::endl;

  Test3_LL(repeatCount);
  Test3_V(repeatCount);
  return 0;
}
