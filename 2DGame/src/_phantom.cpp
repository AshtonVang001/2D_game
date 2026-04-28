#include "_phantom.h"

_phantom::_phantom()
{
    moveSpeed = 2.5f;
    health    = 20 * pow(1.1f, levelModifier);
    radius = 0.18f;
    damage = 0.5f;
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
