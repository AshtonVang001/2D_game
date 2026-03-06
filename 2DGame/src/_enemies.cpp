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

        // ---- Player Collision ----
        float dx = newX - playerPos.x;
        float dy = newY - playerPos.y;

        float combinedRadius = radius + playerRadius;

        if ((dx * dx + dy * dy) < (combinedRadius * combinedRadius))
        {
            return;  // too close — cancel movement entirely
        }
        //--------


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

