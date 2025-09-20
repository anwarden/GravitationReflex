#pragma once
#include "vector.h"
#include <Imagine/Graphics.h>

using namespace Imagine;

struct Ball{
    //double x, y, vx, vy, rad;
    Vector pos;
    Vector speed;
    double mass;
    double rad;
    Color color;
};

void shock(Ball& A, Ball& B);

void shockSimple(Ball& A, Ball& B);

bool collision(Ball& A, Ball& B);

void DisplayBall(Ball& ball);

void EraseBall(Ball& ball);

void UpdatePos(Ball& planet, double dt);

void UpdateSpeed(Ball& planet, Vector accel, double dt);

void gravitation_move(Ball& P, Ball& S);

Ball initBall (int width, int height);
