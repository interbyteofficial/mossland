#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED
#include <iostream>

int random(int n, int m){
    return rand() % (m - n + 1) + n;
}

float randomf(float l, float h)
{
    return l+static_cast<float>(rand())/(static_cast <float>(RAND_MAX/(h-l)));
}
#endif // RANDOM_H_INCLUDED
