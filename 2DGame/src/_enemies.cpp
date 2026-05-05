#include "_enemies.h"
#include <glm/glm.hpp>

_enemies::_enemies()
{
    moveSpeed = 1.5f;
    radius = 0.2f;
    footOffset = 0.1f;
    health = 30 * pow(1.1f, levelModifier);
    damage = 1 * pow(1.1f, levelModifier);

    colliderX = imgRatioX * worldScale;
    colliderY = imgRatioY * worldScale;
}

_enemies::~_enemies()
{
    //dtor
}

void _enemies::enemyMovement(vec3 playerPos, float deltaTime)
{
    vec3 toPlayer;
    toPlayer.x = playerPos.x - pos.x;
    toPlayer.y = playerPos.y - pos.y;

    float dist = sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);

    if (dist < 0.1f) return;

    toPlayer.x /= dist;
    toPlayer.y /= dist;

    // Candidate directions
    glm::vec2 forward = glm::vec2(toPlayer.x, toPlayer.y);
    glm::vec2 left    = glm::vec2(-forward.y, forward.x);
    glm::vec2 right   = glm::vec2(forward.y, -forward.x);

    // Bias toward forward but allow sliding
    glm::vec2 directions[5] = {
        forward,
        (forward + left)  * 0.7f,
        (forward + right) * 0.7f,
        left,
        right
    };

    bool moved = false;

    for (int i = 0; i < 5; i++)
    {
        glm::vec2 dir = directions[i];

        float len = sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len > 0.0001f)
        {
            dir /= len;
        }

        float newX = pos.x + dir.x * moveSpeed * deltaTime;
        float newY = pos.y + dir.y * moveSpeed * deltaTime;

        // Player collision check
        float dx = newX - playerPos.x;
        float dy = newY - playerPos.y;

        float combinedRadius = radius + playerRadius;

        if ((dx * dx + dy * dy) < (combinedRadius * combinedRadius))
            continue;

        if (canMoveTo(newX, newY))
        {
            pos.x = newX;
            pos.y = newY;
            moved = true;

            // update facing
            if (abs(dir.x) > abs(dir.y))
                actionTrigger = (dir.x > 0) ? WALK_L : WALK_R;
            else
                actionTrigger = (dir.y > 0) ? WALK_B : WALK_F;

            break;
        }
        else{
            if (canMoveTo(newX, pos.y))
                pos.x = newX;

            if (canMoveTo(pos.x, newY))
                pos.y = newY;
            }
    }
}
bool _enemies::canMoveTo(float newX, float newY)
{
    float leftX  = newX - radius;
    float rightX = newX + radius;
    float topY   = (newY + footOffset) + radius;
    float botY   = (newY + footOffset) - radius;

    float uLeft  = (leftX + colliderX) / (colliderX * 2);
    float uRight = (rightX + colliderX) / (colliderX * 2);

    float vTop = 1.0f - ((topY + colliderY) / (colliderY * 2));
    float vBot = 1.0f - ((botY + colliderY) / (colliderY * 2));

    return !collisionMap->isSolidUV(uLeft, vTop)  &&
           !collisionMap->isSolidUV(uLeft, vBot)  &&
           !collisionMap->isSolidUV(uRight, vTop) &&
           !collisionMap->isSolidUV(uRight, vBot);
}

void _enemies::resolveCollision()
{
    const float pushStep = 0.02f;
    const int maxSteps = 10;

    for (int i = 0; i < maxSteps; i++)
    {
        if (canMoveTo(pos.x, pos.y))
            return;

        // try small pushes in 4 directions
        if (canMoveTo(pos.x + pushStep, pos.y))
            pos.x += pushStep;
        else if (canMoveTo(pos.x - pushStep, pos.y))
            pos.x -= pushStep;
        else if (canMoveTo(pos.x, pos.y + pushStep))
            pos.y += pushStep;
        else if (canMoveTo(pos.x, pos.y - pushStep))
            pos.y -= pushStep;
    }
}

void _enemies::enemyHealth()
{


}

void _enemies::takeDamage(int dmg)
{
    health -= dmg;

    damageValue = dmg;
    showDamage = true;
    damageTimer = 0.8f;     // how long text stays
    damageOffsetY = 0.0f;
}

void _enemies::updateDamage(float deltaTime)
{
    if (showDamage)
    {
        damageTimer -= deltaTime;
        damageOffsetY += deltaTime * 0.5f; // float upward

        if (damageTimer <= 0.0f)
        {
            showDamage = false;
        }
    }
}

void _enemies::drawDamageText()
{
    if (!showDamage) return;

    glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float alpha = damageTimer / 0.8f;
    glColor4f(1.0f, 0.2f, 0.2f, alpha);

    char dmgText[32];
    sprintf(dmgText, "-%d", damageValue);

    glPushMatrix();
        glTranslatef(pos.x, pos.y + 0.6f + damageOffsetY, 0.01f);
        glScalef(0.0025f, 0.0025f, 0.0025f);
        glLineWidth(4.0f);

        for (const char* c = dmgText; *c; ++c)
        {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
        }
    glPopMatrix();
    glPopAttrib();
}

void _enemies::setLevelModifier(int levelModifier)
{
    health = 30.0f * pow(1.1f, levelModifier);
}
