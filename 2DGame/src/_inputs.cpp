#include "_inputs.h"

_inputs::_inputs()
{
    //ctor
    isRotationActive = false;
    isTranslationActive = false;
    //isScalingActive = false;
    lastDirection = _sprite::IDLE_F;

    colliderX = imgRatioX * worldScale;
    colliderY = imgRatioY * worldScale;

}

_inputs::~_inputs()
{
    //dtor
}


void _inputs::keyPressed(_sprite* mySprite, float deltaTime, _collisionCheck* myCollider)
{
    moveSpeed = 2.5f;
    dx = 0.0f;
    dy = 0.0f;
    isMoving = false;

    // ---- Input (Disabled While Dashing) ----
    if (!isDashing)
    {
        if (keys['W'] && canMove) {
            dy += 1;
            mySprite->actionTrigger = mySprite->WALK_B;
            lastDirection = mySprite->IDLE_B;
            isMoving = true;
        }
        if (keys['S'] && canMove) {
            dy -= 1;
            mySprite->actionTrigger = mySprite->WALK_F;
            lastDirection = mySprite->IDLE_F;
            isMoving = true;
        }
        if (keys['A'] && canMove) {
            dx -= 1;
            mySprite->actionTrigger = mySprite->WALK_L;
            lastDirection = mySprite->IDLE_L;
            isMoving = true;
        }
        if (keys['D'] && canMove) {
            dx += 1;
            mySprite->actionTrigger = mySprite->WALK_R;
            lastDirection = mySprite->IDLE_R;
            isMoving = true;
        }

        bool attackDown = keys['F'];
        if (attackDown && !attackWasDown) {
            attackPressed = true;
        }
        else {
            attackPressed = false;
        }
        attackWasDown = attackDown;

        bool bDown = keys['B'];
        if (bDown && !bWasDown) {
            showHitboxes = !showHitboxes;
        }
        bWasDown = bDown;
    }

    if (!isMoving && !isDashing)
        mySprite->actionTrigger = lastDirection;

    // ---- Normalize ----
    float len = sqrtf(dx * dx + dy * dy);
    if (len > 0.0f) {
        dx /= len;
        dy /= len;
    }

    // ---- Dash Trigger ----
    bool shiftDown = keys[16];
    if (shiftDown && !shiftWasDown && !isDashing)
    {
        isDashing = true;
        dashAttack = true;
        dashTraveled = 0.0f;
        dashDir = {0.0f, 0.0f};

        mySprite->setLoop(false);

        if (lastDirection == mySprite->IDLE_B) {
            dashDir.y = 1;
            mySprite->actionTrigger = mySprite->DASH_B;
        }
        else if (lastDirection == mySprite->IDLE_F) {
            dashDir.y = -1;
            mySprite->actionTrigger = mySprite->DASH_F;
        }
        else if (lastDirection == mySprite->IDLE_L) {
            dashDir.x = -1;
            mySprite->actionTrigger = mySprite->DASH_L;
        }
        else if (lastDirection == mySprite->IDLE_R) {
            dashDir.x = 1;
            mySprite->actionTrigger = mySprite->DASH_R;
        }

        mySprite->resetAnimation();
    }


    // ---- Dashing ----

    shiftWasDown = shiftDown;

    if (isDashing)
    {
        dx = dashDir.x;
        dy = dashDir.y;

        float dashStep = dashSpeed * deltaTime;

        float remaining = dashDistance - dashTraveled;
        if (dashStep > remaining)
            dashStep = remaining;

        dashTraveled += dashStep;

        float nextX = mySprite->pos.x + dx * dashStep;
        float nextY = mySprite->pos.y + dy * dashStep;

        //Player Height
        float halfW = 0.20f;
        float halfH = 0.30f;

        // ---- X Collision ----
        if (dx != 0.0f)
        {
            float testX = nextX + (dx > 0 ? halfW : -halfW);
            float u = (testX + colliderX) / (colliderX*2);                        //float u = (testX + 8.0f) / 16.0f;
            float v = (mySprite->pos.y + colliderY) / (colliderY*2);              //float v = (mySprite->pos.y + 3.2f) / 6.4f;
            v = 1.0f - v;

            if (!myCollider->isSolidUV(u, v))
                mySprite->pos.x = nextX;
        }

        // ---- Y Collision ----
        if (dy != 0.0f)
        {
            float testY = nextY + (dy > 0 ? halfH : -halfH);
            float u = (mySprite->pos.x + colliderX) / (colliderX*2);              //float u = (mySprite->pos.x + 8.0f) / 16.0f;
            float v = (testY + colliderY) / (colliderY*2);                        //float v = (testY + 3.2f) / 6.4f;
            v = 1.0f - v;

            if (!myCollider->isSolidUV(u, v))
                mySprite->pos.y = nextY;
        }

        if (dashTraveled >= dashDistance && mySprite->animationFinished)
        {
            isDashing = false;
            dashAttack = false;
            mySprite->setLoop(true);
            mySprite->actionTrigger = lastDirection;
            mySprite->resetAnimation();
        }

        playerPos.x = mySprite->pos.x;
        playerPos.y = mySprite->pos.y;

        return;
    }

    // ---- Normal Collision ----

    float speed = moveSpeed;

    float nextX = mySprite->pos.x + dx * speed * deltaTime;
    float nextY = mySprite->pos.y + dy * speed * deltaTime;

    float halfW = 0.20f;
    float halfH = 0.30f;

    // ---- X Collision ----
    if (dx != 0.0f)
    {
        float testX = nextX + (dx > 0 ? halfW : -halfW);
        float u = (testX + colliderX) / (colliderX*2);                    //float u = (testX + 8.0f) / 16.0f;
        float v = (mySprite->pos.y + colliderY) / (colliderY*2);          //float v = (mySprite->pos.y + 3.2f) / 6.4f;
        v = 1.0f - v;

        if (!myCollider->isSolidUV(u, v))
            mySprite->pos.x = nextX;
    }

    // ---- Y Collision ----
    if (dy != 0.0f)
    {
        float testY = nextY + (dy > 0 ? halfH : -halfH);
        float u = (mySprite->pos.x + colliderX) / (colliderX*2);          //float u = (mySprite->pos.x + 8.0f) / 16.0f;
        float v = (testY + colliderY) / (colliderY*2);                    //float v = (testY + 3.2f) / 6.4f;
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
