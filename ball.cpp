
#include <Imagine/Graphics.h>
#include <cmath> // For sqrt
#include <iostream>
#include "tools.h"
#include "vector.h"
#include "ball.h"

using namespace Imagine;
using namespace std;

void shock(Ball& A, Ball& B)
{
    double vvx = (A.mass * A.speed.x + B.mass * B.speed.x)/(A.mass + B.mass);
    double vvy = (A.mass * A.speed.y + B.mass * B.speed.y)/(A.mass + B.mass);
    double deltax = B.pos.x - A.pos.x;
    double deltay = B.pos.y - A.pos.y;
    double norme = deltax * deltax + deltay * deltay;
    double scal = -2. * ((A.speed.x-vvx)*deltax + (A.speed.y-vvy)*deltay)/norme;
    A.speed.x += scal * deltax;
    A.speed.y += scal * deltay;
    scal = -2. * ((B.speed.x-vvx)*deltax + (B.speed.y-vvy)*deltay)/norme;
    B.speed.x += scal * deltax;
    B.speed.y += scal * deltay;
}

void shockSimple(Ball& A, Ball& B) {
    shock(A, B);
}

bool collision(Ball& A, Ball& B)
{
    double dx=A.pos.x-B.pos.x, dy=A.pos.y-B.pos.y, dvx=A.speed.x-B.speed.x, dvy=A.speed.y-B.speed.y, r=A.rad+B.rad;
    if(dvx*dvx + dvy*dvy != 0) {
        double t_min = -(dx*dvx + dy*dvy)/(dvx*dvx + dvy*dvy);
        double t_true;
        if (t_min < 0)
            t_true = 0;
        else if (t_min > dt)
            t_true = dt;
        else
            t_true = t_min;
        dx += dvx * t_true;
        dy += dvy * t_true;
    }
    return ((dx*dx + dy*dy) <= r*r);
}

void DisplayBall(Ball& ball)
{
    fillCircle(int(ball.pos.x),int(ball.pos.y),int(ball.rad), ball.color);
}

void EraseBall(Ball& ball)
{
    fillCircle(int(ball.pos.x),int(ball.pos.y),int(ball.rad), WHITE);
    fillCircle(int(ball.pos.x),int(ball.pos.y),int(ball.rad)/2, ball.color);
}

//void UpdatePos(double& x, double& y, double vx, double vy, double dt)
void UpdatePos(Ball& planet, double dt)
{
    planet.pos.x += planet.speed.x * dt;
    planet.pos.y += planet.speed.y * dt;
}

//void UpdateAcc(double& vx, double& vy, double ax, double ay, double dt)
void UpdateSpeed(Ball& planet, Vector accel, double dt)
{
    planet.speed.x += accel.x * dt;
    planet.speed.y += accel.y * dt;
}

void gravitation_move(Ball& P, Ball& S)
{
    //double dist = sqrt((S.pos.x-P.pos.x)*(S.pos.x-P.pos.x) + ((S.pos.y-P.pos.y)*(S.pos.y-P.pos.y)));
    double dist = norm2(P.pos-S.pos);

    //double cosTh, sinTh;
    //cosTh = (P.pos.x - S.pos.x) / dist;
    //sinTh = (P.pos.y - S.pos.y) / dist;

    if(dist >= P.rad + S.rad)
    {
        //double acc_x, acc_y;
        //accel.x = - S.mass * cosTh / (dist*dist) ;
        //accel.y = - S.mass * sinTh / (dist*dist) ;
        Vector accel = (P.pos - S.pos) * (1/dist);
        accel = accel*(-S.mass/(dist*dist));

        UpdateSpeed(P, accel, dt);
        UpdatePos(P, dt);
    }
}

Ball initBall (int width, int height)
{
    Ball ball;
    ball.pos.x = intRandom(0, width);
    ball.pos.y = intRandom(0, height);
    ball.speed.x = 0; ball.speed.y = 0;
    ball.rad = intRandom(5, 15);
    ball.mass = ball.rad * .05;

    return ball;
}
