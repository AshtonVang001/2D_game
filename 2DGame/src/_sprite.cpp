#include "_sprite.h"

_sprite::_sprite()
{
    //ctor

    xMin = yMin = 0.0;
    xMax = yMax = 1.0;

    rot.x = rot.y = rot.z = 0;
    pos.x = pos.y = pos.z = 0;

    vertX[0].x = -0.5; vertX[0].y = -0.5; vertX[0].z = 1;
    vertX[1].x =  0.5; vertX[1].y = -0.5; vertX[1].z = 1;
    vertX[2].x =  0.5; vertX[2].y =  0.5; vertX[2].z = 1;
    vertX[3].x = -0.5; vertX[3].y =  0.5; vertX[3].z = 1;

}

_sprite::~_sprite()
{
    //dtor
}

void _sprite::spriteInit(char* fileName, int xFrames, int yFrames)
{
    myTex->loadTexture(fileName);
    frames.x = xFrames;
    frames.y = yFrames;

    xMin = 0;
    yMin = 0;
    xMax = 1.0/xFrames;
    yMax = 1.0/yFrames;
}

void _sprite::drawSprite(float x, float y, float z)
{
    pos.x = x;
    pos.y = y;
    pos.z = z;

    glPushMatrix();
        glTranslatef(pos.x, pos.y, pos.z);
        myTex->bindTexture();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBegin(GL_QUADS);
            glTexCoord2f(xMin, yMax);
            glVertex2f(vertX[0].x, vertX[0].y);

            glTexCoord2f(xMax, yMax);
            glVertex2f(vertX[1].x, vertX[1].y);

            glTexCoord2f(xMax, yMin);
            glVertex2f(vertX[2].x, vertX[2].y);

            glTexCoord2f(xMin, yMin);
            glVertex2f(vertX[3].x, vertX[3].y);
        glEnd();

    glPopMatrix();
}

void _sprite::spriteActions()
{

    int row = 0;
    float frameW = 1.0f / frames.x;
    float frameH = 1.0f / frames.y;

    switch (actionTrigger)
    {
        case IDLE_F: row = 1; break;
        case IDLE_B: row = 3; break;
        case IDLE_L: row = 0; break;
        case IDLE_R: row = 2; break;
        default:     return;
    }

    // lock Y
    yMin = row * frameH;
    yMax = yMin + frameH;

    // advance X
    xMin += frameW;
    xMax = xMin + frameW;

    // wrap X
    if (xMin >= 1.0f) {
        xMin = 0.0f;
        xMax = frameW;
    }
}

