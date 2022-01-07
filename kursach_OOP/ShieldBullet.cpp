#include "ShieldBullet.h"
#include <regex>

ShieldBullet::ShieldBullet(int InitX, int InitY, DIRECTION direction) : Bullet(InitX, InitY, direction)
{
}

ShieldBullet::~ShieldBullet()
{
}

HPEN ShieldBullet::SetColor()
{
	return CreatePen(PS_SOLID, 2, RGB(128, 256, 128));
}

void ShieldBullet::OnCollision(Entity* entity)
{
	const std::regex reg("class .*Bonus");
	if (!(std::regex_match(typeid(*entity).name(), reg))) {
		if (counterCollision >= 1) {
			Destroy();
		}
		counterCollision++;
	}	
}
