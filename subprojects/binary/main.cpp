#include "sublib2/sublib2.h"
#include "sublib1/hello.h"

int main()
{
    sublib1 lib1;
    lib1.print();
    sublib2 lib2;
    lib2.print();
    return 0;
}