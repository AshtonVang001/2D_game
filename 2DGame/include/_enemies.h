#ifndef _ENEMIES_H
#define _ENEMIES_H

#include<_sprite.h>
#include<_collisionCheck.h>
#include<_common.h>


class _enemies : public _sprite
{
    public:
        _enemies();
        virtual ~_enemies();

        _collisionCheck* collisionMap;

        void enemyMovement(vec3 playerPos, float deltaTime);
        void enemyHealth();
        void takeDamage(int dmg);
        void updateDamage(float deltaTime);
        void drawDamageText();

        float health = 30;
        float moveSpeed;
        float radius;
        float footOffset;
        float playerRadius = 0.25f;

        bool showDamage = false;
        int damageValue = 0;
        float damageTimer = 0.0f;
        float damageOffsetY = 0.0f;

        float colliderX;
        float colliderY;

    protected:

    private:
};

#endif // _ENEMIES_H
