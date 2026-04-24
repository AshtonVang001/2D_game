#include "_coin.h"
#include <windows.h>
#include <math.h>
#include <stdlib.h>

_textureLoader* _coin::sharedTex = nullptr;
_sprite* _coin::sharedSprite = nullptr;

_coin::_coin()
{
    pos = {0,0,0};
    vel = {0,0,0};

    size = 0.3f;

    lifeTime = 0.0f;
    maxLife = 10.0f;

    value = 1;
    destroy = false;

    animTimer = 0.0f;
    animSpeed = 1000.0f;
}

_coin::~_coin()
{
}

void _coin::init()
{
    if (!sharedTex)
    {
        sharedTex = new _textureLoader();

        GLuint id = sharedTex->loadTexture("images/coin.png");

        if (id == 0)
            printf("COIN TEXTURE FAILED TO LOAD\n");
    }

    if (!sharedSprite)
    {
        sharedSprite = new _sprite();
        sharedSprite->spriteInit("images/coin.png", 8, 1);
    }

    vel.x = ((rand() % 100) / 100.0f - 0.5f) * 2.0f;
    vel.y = ((rand() % 100) / 100.0f - 0.5f) * 2.0f;
}

void _coin::update(float dt, float playerX, float playerY)
{
    // ---- Movement (existing) ----
    pos.x += vel.x * dt;
    pos.y += vel.y * dt;

    vel.x *= 0.90f;
    vel.y *= 0.90f;

    // ---- Magnet logic ----
    float dx = playerX - pos.x;
    float dy = playerY - pos.y;

    float distSq = dx*dx + dy*dy;
    float dist = sqrt(distSq);

    float magnetRadius = 2.5f;
    float baseForce = 8.0f;   // base pull
    float expStrength = 3.0f; // how aggressive the exponential is

    if (dist < magnetRadius && dist > 0.001f)
    {
        // normalize
        dx /= dist;
        dy /= dist;

        // ---- exponential strength ----
        float t = 1.0f - (dist / magnetRadius);  // 0 (far)  1 (close)

        float strength = baseForce * exp(t * expStrength);
        //  THIS is the key line

        vel.x += dx * strength * dt;
        vel.y += dy * strength * dt;

        // optional: reduce damping so it feels snappier
        vel.x *= 0.98f;
        vel.y *= 0.98f;
    }

    // ---- Lifetime ----
    lifeTime += dt;
    if (lifeTime >= maxLife)
        destroy = true;

    // ---- Animation ----
    animTimer += dt * animSpeed;

    if (animTimer > 150) {
        sharedSprite->spriteActions();
        animTimer = 0;
    }
}



void _coin::draw()
{
    if (!sharedSprite)
        return;

    glPushMatrix();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    // ---- position ----
    glTranslatef(pos.x, pos.y, pos.z);

    // ---- SCALE HERE ----
    glScalef(0.2f, 0.2f, 1.0f);

    // draw at origin
    sharedSprite->drawSprite(0, 0, 0);

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    glPopMatrix();
}

/*
void _coin::draw()
{
    if (!sharedTex)
        return;

    glPushMatrix();

    // ---- WORLD POSITION ----
    glTranslatef(pos.x, pos.y, pos.z);

    // ---- spin / animation ----
    float squash = fabs(sin(animTimer));

    glScalef(size * squash, size, size);

    // ---- IMPORTANT WORLD STATE ----
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // ---- bind texture safely ----
    if (sharedTex->textID != 0)
    {
        sharedTex->bindTexture();
        glColor4f(1, 1, 1, 1);
    }
    else
    {
        // debug fallback
        glDisable(GL_TEXTURE_2D);
        glColor3f(1, 0, 1);
    }

    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f(-1, -1, 0);
        glTexCoord2f(1, 1); glVertex3f( 1, -1, 0);
        glTexCoord2f(1, 0); glVertex3f( 1,  1, 0);
        glTexCoord2f(0, 0); glVertex3f(-1,  1, 0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    glPopMatrix();
}
*/
