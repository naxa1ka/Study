#include "SimpleBulletFactory.h"

void SimpleBulletFactory::CreateBullet(int InitX, int InitY, DIRECTION direction)
{
    new Bullet(InitX, InitY, direction);
}
