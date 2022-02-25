
#include "c.h"
#include "d.h"

#include <iostream>

void C::greet()
{
    D d;
    d.greet();
    printf("i'm c\n");
}


