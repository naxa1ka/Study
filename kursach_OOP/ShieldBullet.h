
#include "Bullet.h"

class ShieldBullet : public Bullet { //пуля, способная пробивать несколько стенок
private:
    int counterCollision = 0; //счетчик столкновений
public:
    ShieldBullet(int InitX, int InitY, DIRECTION direction);

    ~ShieldBullet();

    HPEN SetColor() override;

    void virtual OnCollision(Entity* entity) override;
};

