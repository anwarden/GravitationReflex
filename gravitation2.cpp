// Imagine++ project
// Project:  Tp4_Initial
// Student(s): Anwar Kardid

#include <Imagine/Graphics.h>
#include <cmath> // For sqrt
#include <iostream>
//#include "tools.h"
#include "vector.h"
#include "ball.h"

using namespace Imagine;
using namespace std;

const int width = 512;
const int height = 512;
const int freqDisplay = 1000;

/////////////////////////////////////////////
int main()
{
    openWindow(width, height);
    initRandom();

    //****************** INITIALISATION *******************#
    //Planet
    Vector pos;
    pos.x = width/2;
    pos.y = height/2;

    Vector speed;
    speed.x = 0.3;
    speed.y = 0;

    double r = 3;
    double mass = 1;
    int bounce_count = 0;
    Color col = RED;

    Ball planet;
    planet.pos = pos;
    planet.speed = speed;
    planet.mass = mass;
    planet.color = col;
    planet.rad = r;

    //Sun
    const int suns_number = 10;
    Ball suns[suns_number];
    for(int i = 0; i < suns_number; i++)
    {
        Ball sun_temp = initBall(width, height);
        suns[i] = sun_temp;
        suns[i].color = YELLOW;
        DisplayBall(suns[i]);
        suns[i].mass *= 20;
    }

    //******* Save position for display ********

    //****** Main loop ******
    for(int timeStep=0; timeStep<10000*freqDisplay; timeStep++) {
        //******** Display ************
        if ((timeStep%freqDisplay)==0){
            noRefreshBegin();

            //Stopping conditions
            if(planet.pos.x < 0 || planet.pos.x >= width || planet.pos.y < 0 || planet.pos.y>=height || bounce_count >= 5)
                break;

            for(int i = 0; i < suns_number; i++)
                EraseBall(suns[i]);
            EraseBall(planet);

            for(int i = 0; i < suns_number; i++)
                gravitation_move(planet, suns[i]);

            for(int i = 0; i < suns_number; i++)
            {
                for(int j = 0; j < suns_number; j++)
                {
                    if(i==j) continue;
                    gravitation_move(suns[j], suns[i]);
                    if(collision(suns[j], suns[i]))
                    {
                        shock(suns[i], suns[j]);
                    }
                }
            }

            for(int i = 0; i < suns_number; i++)
            {
                if(collision(planet, suns[i]))
                {
                    shock(suns[i], planet);
                    bounce_count++;
                }
            }

            for(int i = 0; i < suns_number; i++)
                DisplayBall(suns[i]);
            DisplayBall(planet);

            noRefreshEnd();
            milliSleep(50);
        }
    }

    cout << "Press the left mouse button  !!!!" << endl;

    int temp_x, temp_y;
    if(getMouse(temp_x, temp_y) == 1)
    {
        EraseBall(planet);

        //****************** INITIALISATION *******************#
        //Planet
        speed.x = 0.1;
        speed.y = 0;

        planet.pos = pos;
        planet.speed = speed;
        planet.mass = mass;

        bounce_count = 0;
        //****** Main loop ******
        for(int timeStep=0; timeStep<10000*freqDisplay; timeStep++) {
            //******** Display ************
            if ((timeStep%freqDisplay)==0){
                noRefreshBegin();

                //Stopping conditions
                if(planet.pos.x < 0 || planet.pos.x >= width || planet.pos.y < 0 || planet.pos.y >= height || bounce_count >= 5)
                    break;

                for(int i = 0; i < suns_number; i++)
                    EraseBall(suns[i]);
                EraseBall(planet);

                for(int i = 0; i < suns_number; i++)
                    gravitation_move(planet, suns[i]);

                for(int i = 0; i < suns_number; i++)
                {
                    for(int j = 0; j < suns_number; j++)
                    {
                        if(i==j) continue;
                        gravitation_move(suns[j], suns[i]);
                        if(collision(suns[j], suns[i]))
                        {
                            shock(suns[i], suns[j]);
                        }
                    }
                }

                for(int i = 0; i < suns_number; i++)
                {
                    if(collision(planet, suns[i]))
                    {
                        shock(suns[i], planet);
                        bounce_count++;
                    }
                }

                for(int i = 0; i < suns_number; i++)
                    DisplayBall(suns[i]);
                DisplayBall(planet);

                noRefreshEnd();
                milliSleep(50);
            }
        }

    }

    endGraphics();
    return 0;

}
