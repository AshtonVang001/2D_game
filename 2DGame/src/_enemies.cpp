#include "_enemies.h"
#include <glm/glm.hpp>

_enemies::_enemies()
{
    moveSpeed = 1.5f;
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

        pos.x += direction.x * moveSpeed * deltaTime;
        pos.y += direction.y * moveSpeed * deltaTime;

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


