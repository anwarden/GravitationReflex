// Imagine++ project
// Project:  Tp4_Initial
// Student(s): Anwar Kardid

#include <Imagine/Graphics.h>
using namespace Imagine;

#include <iostream>
#include <cmath> // For sqrt
using namespace std;

const int width = 512;
const int height = 512;

const double dt = 1;
const int freqDisplay = 100;

struct Ball{
    double x, y, vx, vy, rad;
    double mass;
    Color color;
};

void shock(double x,  double y,  double &vx,  double &vy,  double m,
          double x2, double y2, double &vx2, double &vy2, double m2) {
	double vvx = (m * vx + m2 * vx2)/(m + m2);
	double vvy = (m * vy + m2 * vy2)/(m + m2);
	double deltax = x2 - x;
	double deltay = y2 - y;
	double norme = deltax * deltax + deltay * deltay;
	double scal = -2. * ((vx-vvx)*deltax + (vy-vvy)*deltay)/norme;
	vx += scal * deltax;
	vy += scal * deltay;
	scal = -2. * ((vx2-vvx)*deltax + (vy2-vvy)*deltay)/norme;
	vx2 += scal * deltax;
	vy2 += scal * deltay;
}

void shock(Ball A, Ball B)
{
    double vvx = (A.mass * A.vx + B.mass * B.vx)/(A.mass + B.mass);
    double vvy = (A.mass * A.vy + B.mass * B.vy)/(A.mass + B.mass);
    double deltax = B.x - A.x;
    double deltay = B.y - A.y;
    double norme = deltax * deltax + deltay * deltay;
    double scal = -2. * ((A.vx-vvx)*deltax + (A.vy-vvy)*deltay)/norme;
    A.vx += scal * deltax;
    A.vy += scal * deltay;
    scal = -2. * ((B.vx-vvx)*deltax + (B.vy-vvy)*deltay)/norme;
    B.vx += scal * deltax;
    B.vy += scal * deltay;
}

void shockSimple(double x,  double y,  double &vx, double &vy, double m,
                double x2, double y2, double vx2, double vy2) {
    shock(x,y,vx,vy,m,x2,y2,vx2,vy2,1000*m);
}

void shockSimple(Ball A, Ball B) {
    shock(A.x,A.y,A.vx,A.vy,A.mass,B.x,B.y,B.vx,B.vy,1000*A.mass);
}

bool collision(double x1, double y1, double vx1, double vy1, double r1,
               double x2, double y2, double vx2, double vy2, double r2)
{
	double dx=x1-x2,dy=y1-y2,dvx=vx1-vx2,dvy=vy1-vy2,r=r1+r2;
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

bool collision(Ball A, Ball B)
{
    double dx=A.x-B.x,dy=A.y-B.y,dvx=A.vx-B.vx,dvy=A.vy-B.vy,r=A.rad+B.rad;
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

void DisplayBall(Ball ball)
{
    fillCircle(int(ball.x),int(ball.y),int(ball.rad),ball.color);

}

void EraseBall(Ball ball)
{
    fillCircle(int(ball.x),int(ball.y),int(ball.rad), BLACK);

}

void UpdatePos(double& x, double& y, double vx, double vy, double dt)
{
    x += vx * dt;
    y += vy * dt;
}

void UpdateAcc(double& vx, double& vy, double ax, double ay, double dt)
{
    vx += ax * dt;
    vy += ay * dt;
}

void gravitation_move(Ball& P, Ball& S)
{
    double acc_x, acc_y;

    double dist = sqrt((S.x-P.x)*(S.x-P.x) + ((S.y-P.y)*(S.y-P.y)));
    double cosTh, sinTh;
    cosTh = (P.x - S.x) / dist;
    sinTh = (P.y - S.y) / dist;

    if(dist >= P.rad + S.rad)
    {
        acc_x = - S.mass * cosTh / (dist*dist) ;
        acc_y = - S.mass * sinTh / (dist*dist) ;

        UpdateAcc(P.vx, P.vy, acc_x, acc_y, dt);
        UpdatePos(P.x, P.y , P.vx, P.vy, dt);
    }
}
/////////////////////////////////////////////
int main()
{
    openWindow(width, height);
    initRandom();

    //****************** INITIALISATION *******************#
    //Planet
    double x = width/3, y = height/3;
    double vx = 0.3, vy = 0;
    double r = 3;
    double mass = 1;
    int bounce_count = 0;
	Color col = RED;

    Ball planet;
    planet.x = x;
    planet.y = y;
    planet.vx = vx;
    planet.vy = vy;
    planet.mass = mass;
    planet.color = col;
    planet.rad = r;
    //******* Save position for display ********

    Ball sun;
    sun.color = YELLOW;
    sun.vx = 0; sun.vy = 0;
    sun.x = width/2;
    sun.y = height/2;
    sun.rad = 4;
    sun.mass = 10;

    DisplayBall(sun);

    //****** Main loop ******
    for(int timeStep=0; timeStep<10000*freqDisplay; timeStep++) {
        //******** Display ************
        if ((timeStep%freqDisplay)==0){
			noRefreshBegin();

            //Stopping conditions
            if(planet.x < 0 || planet.x >= width || planet.y < 0 || planet.y>=height || bounce_count >= 5)
                break;

            //fillCircle(int(ox),int(oy),int(r),WHITE);
            //planet.x = ox; planet.y = oy; planet.color = col; planet.rad = r;
            EraseBall(planet);

            //fillCircle(int(x),int(y),int(r),col);
            //planet.x = x; planet.y = y; planet.color = col; planet.rad = r;
            gravitation_move(planet, sun);

            if(collision(planet, sun))
            {
                planet.vx *= -1;
                planet.vy *= -1;
                bounce_count++;
            }

            DisplayBall(planet);

            //ox=x;oy=y;
			noRefreshEnd();
            milliSleep(50);
        }

        //x+=vx*dt;
        //y+=vy*dt;

        //UpdatePos(x, y, vx, vy, dt);
        //UpdateAcc(ball.vx, planet.vy, 0, 0.0005, dt);

    }

    cout << "Press the left mouse button  !!!!" << endl;

    int temp_x, temp_y;
    if(getMouse(temp_x, temp_y) == 1)
    {
        EraseBall(planet);

        //****************** INITIALISATION *******************#
        //Planet
        x = width/3, y = height/3;
        vx = 0.3, vy = 0;
        r = 3;
        mass = 1;
        col = RED;

        planet.x = x;
        planet.y = y;
        planet.vx = vx;
        planet.vy = vy;
        planet.mass = mass;
        planet.color = col;
        planet.rad = r;

        //****** Main loop ******
        for(int timeStep=0; timeStep<10000*freqDisplay; timeStep++) {


            //******** Display ************
            if ((timeStep%freqDisplay)==0){
                noRefreshBegin();

                EraseBall(planet);

                gravitation_move(planet, sun);

                if(collision(planet, sun))
                {
                    planet.vx *= -1;
                    planet.vy *= -1;
                }

                DisplayBall(planet);

                noRefreshEnd();
                milliSleep(50);

            }
        }
    }

    endGraphics();
	return 0;

}
