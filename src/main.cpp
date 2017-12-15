#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <string>

#include "Vector.h"
#include "LinkedList.h"

using namespace std;
using namespace aisdi;
using vector = aisdi::Vector<long long>;
using list = aisdi::LinkedList<long long>;

template <class Collection>
void testPrepend(long long n)
{
    Collection collection;

    for (long long i = 0; i < n; ++i)
        collection.prepend(i);
}

template <class Collection>
void testAppend(long long n)
{
    Collection collection;

    for (long long i = 0; i < n; ++i)
        collection.append(i);
}

void testCollectionsAppend(long long repeatCount)
{
    cout << "append:\n";
    clock_t time = clock();
    testAppend<vector>(repeatCount);
    time = clock() - time;
    cout << "vector: " << ((float)time)/CLOCKS_PER_SEC << endl;

    time = clock();
    testAppend<list>(repeatCount);
    time = clock() - time;
    cout << "list:   " << ((float)time)/CLOCKS_PER_SEC << endl;
}

void testCollectionsPrepend(long long repeatCount)
{
    cout << "\nprepend:\n";
    clock_t time = clock();
    testPrepend<vector>(repeatCount);
    time = clock() - time;
    cout << "vector: " << ((float)time)/CLOCKS_PER_SEC << endl;

    time = clock();
    testPrepend<list>(repeatCount);
    time = clock() - time;
    cout << "list:   " << ((float)time)/CLOCKS_PER_SEC;
}

int main(int argc, char** argv)
{
    long long repeatCount = argc > 1 ? std::atoll(argv[1]) : 10000;

    testCollectionsAppend(repeatCount);

    testCollectionsPrepend(repeatCount);

    return 0;
}