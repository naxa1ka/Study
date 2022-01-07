#include "MagicBulletFactory.h"
#include "MagicBullet.h"

void MagicBulletFactory::CreateBullet(int InitX, int InitY, DIRECTION direction)
{
    new MagicBullet(InitX, InitY, direction);
}