#ifndef TESTS_H
#define TESTS_H
#include <assert.h>

class Tests
{
    void test1();
    void test2();
    friend class Menu;
public:
    Tests();
};

#endif // TESTS_H
