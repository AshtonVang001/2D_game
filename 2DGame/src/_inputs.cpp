#include "_inputs.h"

_inputs::_inputs()
{
    //ctor
    isRotationActive = false;
    isTranslationActive = false;
    //isScalingActive = false;
}

_inputs::~_inputs()
{
    //dtor
}


void _inputs::keyPressed(_sprite* mySprite, float deltaTime, _collisionCheck* myCollider)
{
    moveSpeed = 3.5f;
    dx = 0.0f;
    dy = 0.0f;

    // ---- Input ----
    if (keys['W']) { dy += 1; mySprite->actionTrigger = mySprite->IDLE_B; }
    if (keys['S']) { dy -= 1; mySprite->actionTrigger = mySprite->IDLE_F; }
    if (keys['A']) { dx -= 1; mySprite->actionTrigger = mySprite->IDLE_L; }
    if (keys['D']) { dx += 1; mySprite->actionTrigger = mySprite->IDLE_R; }

    // ---- Normalize ----
    float len = sqrtf(dx * dx + dy * dy);
    if (len > 0.0f) {
        dx /= len;
        dy /= len;
    }

    // ---- Sprint ----
    if (keys[16])
        moveSpeed *= 3.0f;

    float nextX = mySprite->pos.x + dx * moveSpeed * deltaTime;
    float nextY = mySprite->pos.y + dy * moveSpeed * deltaTime;

    // ---- player size ----
    float halfW = 0.25f;
    float halfH = 0.35f;

    // ---- Y Axis Collision ----
    if (dx != 0.0f)
    {
        float testX = nextX + (dx > 0 ? halfW : -halfW);

        float u = (testX + 8.0f) / 16.0f;
        float v = (mySprite->pos.y + 3.2f) / 6.4f;
        v = 1.0f - v;

        if (!myCollider->isSolidUV(u, v))
            mySprite->pos.x = nextX;
    }

    // ---- Y Axis Collision ----
    if (dy != 0.0f)
    {
        float testY = nextY + (dy > 0 ? halfH : -halfH);

        float u = (mySprite->pos.x + 8.0f) / 16.0f;
        float v = (testY + 3.2f) / 6.4f;
        v = 1.0f - v;

        if (!myCollider->isSolidUV(u, v))
            mySprite->pos.y = nextY;
    }

    playerPos.x = mySprite->pos.x;
    playerPos.y = mySprite->pos.y;
}

void _inputs::keyPressed(_camera* myCam, float deltaTime)
{
    followSpeed = 1.0;

    myCam->eye.y += (playerPos.y - myCam->eye.y) * followSpeed * (0.5 * moveSpeed) * deltaTime;
    myCam->des.y += (playerPos.y - myCam->des.y) * followSpeed * (0.5 * moveSpeed) * deltaTime;

    myCam->eye.x += (playerPos.x - myCam->eye.x) * followSpeed * (0.5 * moveSpeed) * deltaTime;
    myCam->des.x += (playerPos.x - myCam->des.x) * followSpeed * (0.5 * moveSpeed) * deltaTime;
}




void _inputs::keyUp()
{
    switch(wParam)
    {
        default: break;
    }
}

void _inputs::keyUp(_sprite* mySprite) {
        mySprite->actionTrigger = mySprite->IDLE_F;
}
