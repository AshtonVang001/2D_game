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


void _inputs::keyPressed(_parallax* prlx) {
    switch(wParam) {
    case VK_LEFT:
        prlx->prlxScrollAuto("right", 0.005);
        break;
    case VK_RIGHT:
        prlx->prlxScrollAuto("left", 0.005);
        break;
    case VK_UP:
        //prlx->
        break;
    case VK_DOWN:
        //prlx->
        break;
    case VK_ADD:
        //prlx->
        break;
    case VK_SUBTRACT:
        //prlx->
        break;
    }
}

void _inputs::keyPressed(_skyBox* sky)
{
    switch(wParam) {
    case VK_LEFT:
        sky->rotation.y -= 1.0;
        break;
    case VK_RIGHT:
        sky->rotation.y += 1.0;
        break;
    case VK_UP:
        sky->rotation.x += 1.0;
        break;
    case VK_DOWN:
        sky->rotation.x -= 1.0;
        break;
    case VK_ADD:
        //prlx->
        break;
    case VK_SUBTRACT:
        //prlx->
        break;
    }
}

void _inputs::keyPressed(_sprite* mySprite, float deltaTime)
{
    float moveSpeed = 0.005f;// * deltaTime;
    float dx = 0.0f;
    float dy = 0.0f;

    // ---- Sprint ----
    if (keys[16])
        moveSpeed *= 1.2;

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

    mySprite->pos.x += dx * moveSpeed;
    mySprite->pos.y += dy * moveSpeed;
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


void _inputs::mouseEventUp()
{
    isRotationActive = false;                               //deactivate flags
    isTranslationActive = false;
}


void _inputs::mouseMove(_camera* myCamera, double x, double y)
{

    myCamera->rotAngle.y = (y / 10.0);
    myCamera->rotAngle.x = (x / 10.0);
    //myCamera->rotateXY();

}
