#include <iostream>
#include "random.h"

int random(int n, int m){
    return rand() % (m - n + 1) + n;
}

float randomf(float l, float h)
{
    return l+static_cast<float>(rand())/(static_cast <float>(RAND_MAX/(h-l)));
}
