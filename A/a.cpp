
#include "a.h"
#include "b.h"
#include "c.h"
#include <iostream>

void A::greet()
{
    B b;
    b.greet();

    C c;
    c.greet();

    printf("i'm a\n");
}


