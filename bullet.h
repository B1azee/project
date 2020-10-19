#include "TxLib.h"
#include "time.h"
#include "interface.h"

enum Direction {LEFT,RIGHT,UP,DOWN};


struct Enemy
{
    RECT area = {0,0,0,0};
    bool death = 0;
};

struct Player
{
    int coordinateX = 400;
    bool death = 0;
    int health = 100;
};

struct Difficulty
{
    int enemyBulletSpeed = 10;
    int enemySpeed = 5;
    int quantityEnemyX = 10;
    int quantityEnemyY = 3;
    int enemyBulletDeltaTime = 15;
};


bool checkLevel (Button level, int enemyBulletSpeed_, int enemySpeed_, int quantityEnemyX_, int quantityEnemyY_, int enemyBulletDeltaTime_,Difficulty* difficulty_)
{
    bool ret = 0;
                if(level.check())
            {
                difficulty_->enemyBulletSpeed = enemyBulletSpeed_;
                difficulty_->enemySpeed = enemySpeed_;
                difficulty_->quantityEnemyX = quantityEnemyX_;
                difficulty_->quantityEnemyY = quantityEnemyY_;
                difficulty_->enemyBulletDeltaTime = enemyBulletDeltaTime_;
                ret = 1;
            }
            return ret;
}



/**
 \brief Bullet
*/
struct Bullet
{
    int x;
    int y;
    long int t0;
    POINT left, right, top, down;
    bool hit = false;
    Direction direction;
    int speed;

    /**
     \param[in] x x coordinate
     \param[in] y y coordinate
     \param[in] t start time
     \param[in] direction direction of bullet
     \param[in] speed speed of a bullet

    */
    Bullet(int x_, int y_, long int t_, Direction direction_, int speed_)
    {
        x = x_;
        y = y_;
        t0 = t_;
        direction = direction_;
        speed = speed_;
    }
    /**
     \brief paint bullet
     \param[in] t drawing time
    */
    void paint(long int t_)
    {
        if(!hit)
        {
            if(direction == DOWN)
            {
                int tn = t_;
                int delta = (tn - t0) * speed;
                if(delta < 1000)
                {
                    txSetFillColor(RGB(0,0,0));
                    txRectangle(x - 3,y + delta,x + 3,y + 20 + delta);
                    left = {x - 3,y + delta};
                    right = {x + 3,y + delta};
                    top = {x - 3,y +  20 + delta};
                    down = {x + 3,y + 20 + delta};
                }
            }
            if(direction == UP)
            {
                int tn = t_;
                int delta = (tn - t0) * speed;
                if(delta < 1000)
                {
                    txSetFillColor(RGB(0,0,0));
                    txRectangle(x - 3,y - delta,x + 3,y + 20 - delta);
                    left = {x - 3,y - delta};
                    right = {x + 3,y - delta};
                    top = {x - 3,y +  20 - delta};
                    down = {x + 3,y + 20 - delta};
                }
            }
        }
    }
    /**
     \brief checks whether the bullet is located on the territory
     \param[in] area territory to check
     \return true if the bullet is located on the territory; false if not
    */
    bool check(RECT area)
    {
        if(!hit)
        {
            bool ret = false;
            if ((In(left,area)) or (In(right,area)) or (In(top,area)) or (In(down,area)))
            {
                ret = true;
            }
            return ret;
        }
    }
};

