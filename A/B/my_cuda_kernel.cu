
#include "b.h"
#include "device_launch_parameters.h"
#include <iostream>

__global__ void my_kernel()
{
    printf(" i'm from kernel");
}

void B::greet_from_kernel()
{
    my_kernel<<<1,8>>>();
}
