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


void _inputs::keyPressed(_sprite* mySprite, float deltaTime)
{
    moveSpeed = 3.5f;
    dx = 0.0f;
    dy = 0.0f;

    // ---- Sprint ----
    if (keys[16])
        moveSpeed *= 3;

    // ---- Forward / Back ----
    if (keys['W']) {
        dy += 1;
        mySprite->actionTrigger = mySprite->IDLE_B;
    }
    if (keys['S']) {
        dy -= 1;
        mySprite->actionTrigger = mySprite->IDLE_F;
    }

    // ---- Left / Right ----
    if (keys['A']) {
        dx -= 1;
        mySprite->actionTrigger = mySprite->IDLE_L;
    }
    if (keys['D']) {
        dx += 1;
        mySprite->actionTrigger = mySprite->IDLE_R;
    }

    // ---- Normalize ----
    float length = sqrtf(dx * dx + dy * dy);
    if (length > 0.0f) {
        dx /= length;
        dy /= length;
    }

    playerPos.x = mySprite->pos.x += dx * moveSpeed * deltaTime;
    playerPos.y = mySprite->pos.y += dy * moveSpeed * deltaTime;
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
