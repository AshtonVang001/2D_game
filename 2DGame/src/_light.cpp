#include "_light.h"

_light::_light()
{
    //ctor
}

_light::~_light()
{
    //dtor
}

void _light::drawLight(float cx, float cy)
{
    flickerTimer += myTime->deltaTime * 5.5f;   // speed of flicker

    if (flickerTimer >= 1.0f)
    {
        flickerTimer = 0.0f;
        currentColor = nextColor;
        nextColor = rand() % 2;
    }




    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);


    float r = torchColors[currentColor][0] * (1.0f - flickerTimer) + torchColors[nextColor][0] * flickerTimer;
    float g = torchColors[currentColor][1] * (1.0f - flickerTimer) + torchColors[nextColor][1] * flickerTimer;
    float b = torchColors[currentColor][2] * (1.0f - flickerTimer) + torchColors[nextColor][2] * flickerTimer;

    float flickerSpeed = 5.0f;

    static float flickerTime = 0.0f;
    flickerTime += myTime->deltaTime * flickerSpeed;

    float flicker =
        sin(flickerTime * 2.0f) * 0.10f +
        sin(flickerTime * 5.0f) * 0.05f;

    float radiusFlicker = 1.3f + flicker;
    float alphaFlicker  = 0.5f + flicker * 0.4f;




    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    float radius = 2.0f;

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(r, g, b, alphaFlicker);
    glVertex3f(cx, cy, 0);

    for(int i = 0; i <= 360; i++)
    {
        float angle = i * 3.14159f / 180.0f;
        float x = cx + cos(angle) * radiusFlicker;
        float y = cy + sin(angle) * radiusFlicker;

        glColor4f(r, g * 0.5f, b * 0.3f, 0.0f);
        glVertex3f(x, y, 0);
    }

    glEnd();
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

}
