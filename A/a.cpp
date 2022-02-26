
#include "a.h"
#include "B/b.h"
#include "C/c.h"
#include <iostream>

void A::greet()
{
    B b;
    b.greet();

    C c;
    c.greet();

    printf("i'm a\n");
}


