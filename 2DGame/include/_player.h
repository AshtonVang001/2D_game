#ifndef _PLAYER_H
#define _PLAYER_H

#include <_sprite.h>
#include <_collisionCheck.h>

class _player : public _sprite
{
    public:
        _player();
        virtual ~_player();

        _collisionCheck* collisionMap;

        float health = 100.0f;
        float damageCoolDown = 0.0f;
        float damageCoolDownDuration = 0.8f;
        float radius = 0.3f;

        int getTickLimit(bool isDashing, bool isMoving);
        void takeDamage(int dmg, float deltaTime);
        void updateCoolDown(float deltaTime);
        void drawHealthBar(float currentHealth, float maxHealth, float x, float y, float width, float height);


    protected:

    private:
};

#endif // _PLAYER_H
