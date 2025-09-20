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

const int suns_number = 5;

int aim_finish_x, aim_finish_y;

bool getPlayerInput(Ball& planet) {
    if(getMouse(aim_finish_x, aim_finish_y) == 1)
    {
        double norm = 1000;
        planet.speed.x = (aim_finish_x - planet.pos.x) / norm;
        planet.speed.y = (aim_finish_y - planet.pos.y) / norm;
        drawLine(aim_finish_x, aim_finish_y, planet.pos.x, planet.pos.y, BLACK);

        return true;
    }
    return false;
}

Ball createBall(int x, int y, int vx, int vy, int mass, double radius, Color color) {
    Ball b;
    b.pos.x = x;
    b.pos.y = y;
    b.speed.x = vx;
    b.speed.y = vy;
    b.mass = mass;
    b.rad = radius;
    b.color = color;
    return b;
}

bool handle_turn(Ball player, Ball oponent,  Ball& planet, Ball suns[])
{
    planet.pos = player.pos;

    while(!getPlayerInput(planet))
    {
        milliSleep(20);
        getMouse(aim_finish_x, aim_finish_y);
    }

    //250 display
    int projectile_life = 250;
    for(int timeStep=0; timeStep<10000*freqDisplay && projectile_life > 0; timeStep++)
    {
        if ((timeStep%freqDisplay)==0){
            noRefreshBegin();

            EraseBall(planet);

            for(int i = 0; i < suns_number; i++)
            {
                EraseBall(suns[i]);
                gravitation_move(planet, suns[i]);
            }

            for(int i = 0; i < suns_number; i++)
            {
                for(int j = 0; j < suns_number; j++)
                {
                    if(i==j) continue;
                    gravitation_move(suns[i], suns[j]);
                    if(collision(suns[i], suns[j]))
                        shock(suns[i], suns[j]);
                }
            }

            for(int i = 0; i < suns_number; i++)
            {
                if(collision(planet, suns[i]))
                {
                    shock(suns[i], planet);
                }
            }

            if(collision(planet, oponent))
                return true;

            for(int i = 0; i < suns_number; i++)
                DisplayBall(suns[i]);

            DisplayBall(planet);
            DisplayBall(player);
            DisplayBall(oponent);
            noRefreshEnd();
            milliSleep(50);

            projectile_life--;
        }
    }

    EraseBall(planet);
    drawLine(player.pos.x, player.pos.y, aim_finish_x, aim_finish_y, WHITE);


    return false;
}

/////////////////////////////////////////////
int main()
{
    openWindow(width, height);
    initRandom();

    //****************** INITIALISATION *******************#
    //Planet
    Ball P1 = createBall(width/8, height/2, 0, 0, 1, 10, GREEN);
    DisplayBall(P1);

    Ball P2 = createBall(7*width/8, height/2, 0, 0, 1, 10, BLUE);
    DisplayBall(P2);

    Ball planet = createBall(0, 0, 0, 0, 1, 3, RED);

    //Suns
    Ball suns[suns_number];
    for(int i = 0; i < suns_number; i++)
    {
        Ball sun_temp;
        bool well_placed;
        while(true)
        {
            sun_temp = initBall(width, height);
            well_placed = true;

            for(int j = 0; j<i; j++)
            {
                if(norm2(sun_temp.pos - suns[j].pos) < suns[j].rad + sun_temp.rad)
                {
                    well_placed = false;
                    break;
                }
            }
            if(well_placed)
                break;
        }
        suns[i] = sun_temp;
        suns[i].color = YELLOW;
        suns[i].mass *= 20;
        DisplayBall(suns[i]);
    }


    //****** Main loop *****
    bool game_end = false;
    int turn = -1;

    while(true)
    {
        if(turn<0) //Player 1 turn
        {
            cout << "Player 1 press the left mouse button to choose direction and speed " << endl;
            game_end = handle_turn(P1, P2, planet, suns);
            if(game_end)
            {
                cout << "Player 1 wins" << endl;
                fillRect(width/2-100, height/2-100, 200, 200, GREEN);
                break;
            }
        }
        else
        {
            cout << "Player 2 press the left mouse button to choose direction and speed " << endl;
            game_end = handle_turn(P2, P1, planet, suns);
            if(game_end)
            {
                cout << "Player 2 wins" << endl;
                fillRect(width/2-100, height/2-100, 200, 200, BLUE);
                break;
            }
        }
        turn *= -1;
    }
    endGraphics();
    return 0;

}
