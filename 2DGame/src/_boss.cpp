#include "_boss.h"

_boss::_boss()
{
    moveSpeed = 1.0f;     // slower, heavier
    radius = 0.5f;        // bigger hitbox
    health = 200 + (25 * levelModifier);         // tanky

    // different sprite
    spriteInit("images/CharacterRotate.png", 7, 4);
}

void _boss::update(float dt, vec3 playerPos)
{
    enemyMovement(playerPos, dt);   // reuse base movement
    bossBehavior(dt, playerPos);    // add special logic
}

void _boss::bossBehavior(float dt, vec3 playerPos)
{
    // Example: could shoot, dash, spawn minions, etc.
}
