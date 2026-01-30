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
    float moveSpeed = 25.0f * deltaTime;

    // ---- Sprint ----
    if (keys[16])
        moveSpeed *= 1.5;

    // ---- Forward / Back ----
    if (keys['W'])
        //mySprite->pos.y += 1;
        cout << "W Pressed\n";
    if (keys['S'])
        mySprite->pos.y -= 1;

    // ---- Left / Right ----
    if (keys['A'])
        mySprite->pos.x -= 1;
    if (keys['D'])
        mySprite->pos.x += 1;
}




void _inputs::keyUp()
{
    switch(wParam)
    {
        default: break;
    }
}

void _inputs::keyUp(_sprite* mySprite) {
        mySprite->actionTrigger = mySprite->IDLE;
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
