#pragma once

struct Vector
{
    double x;
    double y;
};

Vector operator+(Vector a, Vector b);
Vector operator-(Vector a, Vector b);

double norm2(Vector a);

Vector operator*(Vector a, double lambda);
Vector operator*(double lambda, Vector a);
