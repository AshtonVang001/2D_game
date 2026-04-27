#include "_phantom.h"

_phantom::_phantom()
{
    // Override base stats
    moveSpeed = 2.5f;   // faster than normal enemy
    health    = 60;     // weaker

    radius = 0.18f;     // slightly smaller hitbox if you want

    // sprite setup (you can also do this in spawner if you prefer)
    spriteInit("images/phantoms.png", 6, 8);
}

_phantom::~_phantom()
{
}

void _phantom::update(float dt, vec3 playerPos)
{
    // reuse base movement
    enemyMovement(playerPos, dt);

    // handle damage text animation
    updateDamage(dt);

    // OPTIONAL: phantom-specific behavior later
    // (phase through walls, teleport, etc.)
}
