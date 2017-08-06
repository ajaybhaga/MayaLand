#include "Enemy.h"

using namespace std;

Enemy::Enemy(World *W) : DynamicObject(W, 32.f, true)
{
    speed = 120.f;
    Object::setDynamicGenerate();

    setSize(32.f);
}

void Enemy::draw()
{    
    glColor4f(Object::getR(), Object::getG(), Object::getB(), 1.f);

    Object::draw();
}

int random(int min, int max) //range : [min, max)
{
   static bool first = true;
   if ( first )
   {
      srand(time(NULL)); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (max - min);
}

void Enemy::update(float time)
{
    static float pastTime = 0;

    if (pastTime > 4.0) {
        std::cout << "Generating colour time=" << time << " pastTime=" << pastTime << std::endl;
        generateColour();
        pastTime = 0.0;
    }

    if (!isCanMove() && (rand() % 50) == 0)
    {
        setPath
        (
            random(position.x - 600, position.x + 600),
            random(position.z - 600, position.z + 600)
        );
    }
    move(time);

    pastTime += time;
}
