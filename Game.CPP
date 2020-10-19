
using namespace std;

#include <vector>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <cstdlib>
#include "bullet.h"


Player player;

int quantityEnemyX = 15;
int quantityEnemyY = 4;

int levelsComplete = 0;
Button levels[9] = {  Button(50,50,250,100,RGB(100,100,100),"1"),
                       Button(300,110,500,160,RGB(100,100,100),"2"),
                       Button(550,170,750,220,RGB(100,100,100),"3"),
                       Button(300,230,500,280,RGB(100,100,100),"4"),
                       Button(50,290,250,340,RGB(100,100,100),"5"),
                       Button(300,350,500,400,RGB(100,100,100),"6"),
                       Button(550,410,750,460,RGB(100,100,100),"7"),
                       Button(300,470,500,520,RGB(100,100,100),"8"),
                       Button(50,530,250,580,RGB(100,100,100),"9")
                    };
Enemy enemies[20][6];
vector<Bullet> bullets;
vector<Bullet> bulletsEnemys;
int quantityBullets = -1;
int quantityBulletsEnemys = -1;
int deltaTime = 50;
int deltaTimeEnemys = 50;
int timeShot = 0;
int timeShotEnemys = 0;
bool directionEnemy = RIGHT;
int coordinateEnemysX = 0;

int main()
{
    txDisableAutoPause();
    srand(time(NULL));
    long int time = 0;
    bool game = true;
    txCreateWindow (800, 800);
    Button start = Button(350,275,450,325,RGB(0,200,0),"Старт");
    Button exit = Button(350,350,450,400,RGB(200,0,0),"Выход");

    Difficulty difficulty;

    while(true)
    {
        while(true)
        {
            start.paint();
            exit.paint();
            if(start.check())
            {
                break;
            }

            if(exit.check())
            {
                return 0;
            }

            txSleep(20);
            txSetFillColour(RGB(0,0,0));
            txClear();
        }

        bool stop = false;
        while(true)
        {
            txSetFillColour(RGB(0,0,0));
            txClear();
            for (int i = 0; i < 9; i++)
            {
                levels[i].paint();
            }

            if(checkLevel(levels[0],10,1,10,3,15,&difficulty))
            {
                break;
            }
            if(checkLevel(levels[1],10,2,11,3,14,&difficulty))
            {
                break;
            }
            if(checkLevel(levels[2],10,2,12,3,13,&difficulty))
            {
                break;
            }
            if(checkLevel(levels[3],10,3,12,3,12,&difficulty))
            {
                break;
            }
            if(checkLevel(levels[4],11,3,13,4,11,&difficulty))
            {
                break;
            }
            if(checkLevel(levels[5],11,3,13,4,10,&difficulty))
            {
                break;
            }
            if(checkLevel(levels[6],11,4,14,4,8,&difficulty))
            {
                break;
            }
            if(checkLevel(levels[7],12,4,14,5,6,&difficulty))
            {
                break;
            }
            if(checkLevel(levels[8],12,5,15,5,4,&difficulty))
            {
                break;
            }

            txSleep(5);
        }

        while(true)
        {
            time++;
            for(int i = bullets.size() - 50; i < bullets.size(); i++)
            {
                for(int j = 0; j < difficulty.quantityEnemyX; j++)
                {
                    for(int h = 0; h < difficulty.quantityEnemyY; h++)
                    {
                        if(bullets[i].check(enemies[j][h].area) && !enemies[j][h].death)
                        {
                            bullets[i].hit = true;
                            enemies[j][h].death = true;
                        }
                    }
                }
            }
            int deathEnemy = 0;
            for(int i = 0; i < difficulty.quantityEnemyX; i++)
            {

                for(int j = 0; j <difficulty.quantityEnemyY; j++)
                {
                    if(enemies[i][j].death)
                    {
                        deathEnemy++;
                    }
                }
                if(deathEnemy == difficulty.quantityEnemyX*difficulty.quantityEnemyY)
                {
                    game = false;
                }
            }

            if(player.health <= 0 or !game)
            {
                Button menu = Button(350,200,450,250,RGB(0,200,0),"Меню");
                Button restart = Button(350,275,450,325,RGB(100,100,100),"Заново");
                if(!game)
                {
                    txSetFillColour(RGB(0,200,0));
                }
                else
                {
                    txSetFillColour(RGB(200,0,0));
                }

                txClear();
                txSleep(1000);
                bool stop = false;
                while(true)
                {
                    txSetFillColour(RGB(0,0,0));
                    txClear();
                    restart.paint();
                    menu.paint();
                    if(restart.check())
                    {
                        game = true;
                        player.health = 100;
                        player.coordinateX = 400;
                        for(int i = bulletsEnemys.size();i > (bulletsEnemys.size() - 15); i--)
                        {
                        bulletsEnemys[i].hit = true;
                        }
                        for(int i = bullets.size();i > (bullets.size() - 15); i--)
                        {
                        bullets[i].hit = true;
                        }
                        for(int i = 0; i < difficulty.quantityEnemyX; i++)
                        {
                            for(int j = 0; j < difficulty.quantityEnemyY; j++)
                            {
                                enemies[i][j].death = false;
                            }
                        }
                        break;
                    }

                    if(menu.check())
                    {
                        game = true;
                        player.health = 100;
                        player.coordinateX = 400;
                        for(int i = bulletsEnemys.size();i > (bulletsEnemys.size() - 15); i--)
                        {
                        bulletsEnemys[i].hit = true;
                        }
                        for(int i = bullets.size();i > (bullets.size() - 15); i--)
                        {
                        bullets[i].hit = true;
                        }
                        for(int i = 0; i < difficulty.quantityEnemyX; i++)
                        {
                            for(int j = 0; j < difficulty.quantityEnemyY; j++)
                            {
                                enemies[i][j].death = false;
                            }
                        }
                        stop = true;
                        break;
                    }
                    txSleep(5);
                }
                if(stop)
                {
                    break;
                }
            }

            txBegin();
            txSetFillColour(RGB(0,0,0));
            txClear();

            for(int i = 0; i<=quantityBullets; i++)
            {
                bullets[i].paint(time);
            }

            for(int i = 0; i<=quantityBulletsEnemys; i++)
            {
                bulletsEnemys[i].paint(time);
            }

            //PLAYER
            txSetFillColour(RGB(200,0,0));
            txRectangle(player.coordinateX - 20, 650, player.coordinateX + 20, 710);
            RECT areaPlayer = {player.coordinateX - 20, 650, player.coordinateX + 20, 710};


            //HEALTH
            txSetFillColour(RGB(100,100,100));
            txRectangle(0,750,800,800);
            txSetFillColour(RGB(50,50,50));
            txRectangle(10,760,790,790);
            txSetFillColour(RGB(200,0,0));
            txRectangle(10,760,10 + 7.8*player.health,790);


            if(directionEnemy == LEFT)
            {
                if(coordinateEnemysX > 170)
                {
                    directionEnemy = RIGHT;
                }
                coordinateEnemysX = coordinateEnemysX + difficulty.enemySpeed;
            }
            if(directionEnemy == RIGHT)
            {
                if(coordinateEnemysX < 1)
                {
                    directionEnemy = LEFT;
                }
                coordinateEnemysX = coordinateEnemysX - difficulty.enemySpeed;
            }

            for(int i = 0; i < difficulty.quantityEnemyX; i++)
            {
                for(int j = 0; j < difficulty.quantityEnemyY; j++)
                {
                    enemies[i][j].area = {20+40*i+coordinateEnemysX, 20+60*j, 45+40*i+coordinateEnemysX, 50+60*j};
                    if(!enemies[i][j].death)
                    {
                        txSetFillColour(RGB(0,0,200));
                        txRectangle(enemies[i][j].area.left,enemies[i][j].area.top,enemies[i][j].area.right,enemies[i][j].area.bottom) ;
                    }
                }
            }
            if((GetAsyncKeyState (VK_LEFT)) && player.coordinateX > 20)//LEFT
            {
                player.coordinateX = player.coordinateX - 16;
            }

            if((GetAsyncKeyState (VK_RIGHT)) && player.coordinateX <780)//RIGHT
            {
                player.coordinateX = player.coordinateX + 16;
            }

            deltaTime = time - timeShot;
            deltaTimeEnemys = time - timeShotEnemys;

            if((GetAsyncKeyState (VK_SPACE)) && deltaTime > 20)
            {
                timeShot = time;
                quantityBullets++;
                bullets.push_back(Bullet(player.coordinateX,650,time,UP,15));
                txSleep(50);
            }
            if(deltaTimeEnemys > difficulty.enemyBulletDeltaTime and game)
            {
                int rerun = 0;
                while(true)
                {
                    int EnemyX = rand() % difficulty.quantityEnemyX;
                    int EnemyY = rand() % difficulty.quantityEnemyY;

                    if(!enemies[EnemyX][EnemyY].death)
                    {
                        timeShotEnemys = time;
                        quantityBulletsEnemys++;
                        bulletsEnemys.push_back(Bullet(enemies[EnemyX][EnemyY].area.left+10,enemies[EnemyX][EnemyY].area.bottom,time,DOWN,difficulty.enemyBulletSpeed));
                        txSleep(50);
                        break;
                    }
                    if(rerun > 1000)
                    {
                        break;
                    }
                    else
                    {
                        rerun++;
                        continue;
                    }
                }
            }

            for(int i = 0; i < bulletsEnemys.size(); i++)
            {
                if(bulletsEnemys[i].check(areaPlayer))
                {
                    bulletsEnemys[i].hit = true;
                    player.health = player.health - 10;
                }
            }

            if((GetAsyncKeyState (VK_ESCAPE)))
            {
                txSleep(100);
                while(true)
                {
                    if((GetAsyncKeyState (VK_ESCAPE)))
                    {
                        txSleep(100);
                        break;
                    }
                }
            }
            txEnd();
            txSleep(4);
        }
    }
}
