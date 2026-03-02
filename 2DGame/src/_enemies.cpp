#include "_enemies.h"
#include <glm/glm.hpp>

_enemies::_enemies()
{
    moveSpeed = 1.5f;
    radius = 0.2f;
    footOffset = 0.1f;
}

_enemies::~_enemies()
{
    //dtor
}

void _enemies::enemyMovement(vec3 playerPos, float deltaTime)
{
    vec3 direction;
    direction.x = playerPos.x - pos.x;
    direction.y = playerPos.y - pos.y;
    direction.z = 0.0f;

    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0.1f)
    {
        direction.x /= distance;
        direction.y /= distance;

        float newX = pos.x + direction.x * moveSpeed * deltaTime;
        float newY = pos.y + direction.y * moveSpeed * deltaTime;


        // --- Try X movement ---
        float leftX  = newX - radius;
        float rightX = newX + radius;
        float topY   = (pos.y + footOffset) + radius;
        float botY   = (pos.y + footOffset) - radius;

        // Convert to UV
        float uLeft  = (leftX + 8.0f) / 16.0f;
        float uRight = (rightX + 8.0f) / 16.0f;

        float vTop = 1.0f - ((topY + 3.2f) / 6.4f);
        float vBot = 1.0f - ((botY + 3.2f) / 6.4f);

        if (!collisionMap->isSolidUV(uLeft, vTop)  &&
            !collisionMap->isSolidUV(uLeft, vBot)  &&
            !collisionMap->isSolidUV(uRight, vTop) &&
            !collisionMap->isSolidUV(uRight, vBot))
        {
            pos.x = newX;
        }

        // --- Try Y movement ---
        leftX  = pos.x - radius;
        rightX = pos.x + radius;
        topY = (newY + footOffset) + radius;
        botY = (newY + footOffset) - radius;

        uLeft  = (leftX + 8.0f) / 16.0f;
        uRight = (rightX + 8.0f) / 16.0f;

        vTop = 1.0f - ((topY + 3.2f) / 6.4f);
        vBot = 1.0f - ((botY + 3.2f) / 6.4f);

        if (!collisionMap->isSolidUV(uLeft, vTop)  &&
            !collisionMap->isSolidUV(uLeft, vBot)  &&
            !collisionMap->isSolidUV(uRight, vTop) &&
            !collisionMap->isSolidUV(uRight, vBot))
        {
            pos.y = newY;
        }


        if (abs(direction.x) > abs(direction.y))
        {
            if (direction.x > 0)
                actionTrigger = IDLE_R;
            else
                actionTrigger = IDLE_L;
        }
        else
        {
            if (direction.y > 0)
                actionTrigger = IDLE_F;
            else
                actionTrigger = IDLE_B;
        }
    }
}

void _enemies::enemyHealth()
{


}


