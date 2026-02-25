#ifndef _ENEMIES_H
#define _ENEMIES_H

#include<_sprite.h>


class _enemies : public _sprite
{
    public:
        _enemies();
        virtual ~_enemies();

        void enemyMovement(vec3 playerPos, float deltaTime);
        void enemyHealth();

        float moveSpeed;

    protected:

    private:
};

#endif // _ENEMIES_H
