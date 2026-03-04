#ifndef _ENEMIES_H
#define _ENEMIES_H

#include<_sprite.h>
#include<_collisionCheck.h>


class _enemies : public _sprite
{
    public:
        _enemies();
        virtual ~_enemies();

        _collisionCheck* collisionMap;

        void enemyMovement(vec3 playerPos, float deltaTime);
        void enemyHealth();

        float health = 30;
        float moveSpeed;
        float radius;
        float footOffset;
        float playerRadius = 0.25f;

    protected:

    private:
};

#endif // _ENEMIES_H
