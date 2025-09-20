#include <iostream>
#include <cmath>
#include "vector.h"

Vector operator+(Vector a, Vector b)
{
    Vector res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;

    return res;
}

Vector operator-(Vector a, Vector b)
{
    Vector res;
    res.x = a.x - b.x;
    res.y = a.y - b.y;

    return res;
}

double norm2(Vector a)
{
    return std::sqrt(a.x*a.x + a.y*a.y);
}

Vector operator*(Vector a, double lambda)
{
    Vector res;
    res.x = a.x * lambda;
    res.y = a.y * lambda;

    return res;
}

Vector operator*(double lambda, Vector a)
{
    return a * lambda;
}


