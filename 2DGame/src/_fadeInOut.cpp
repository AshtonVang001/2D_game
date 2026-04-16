#include "_fadeInOut.h"

_fadeInOut::_fadeInOut()
{
    //ctor
}

_fadeInOut::~_fadeInOut()
{
    //dtor
}

void _fadeInOut::fadeIn(float dt)
{
    fadeTimer -= dt;

    if (fadeTimer <= 0.0f)
    {
        fadeTimer = 0.0f;
        fadeComplete = true;
    }
}

void _fadeInOut::fadeOut(float dt)
{
    fadeTimer += dt;

    if (fadeTimer >= 1.0)
    {
        fadeTimer = fadeDuration;
        fadeComplete = true;
    }
}

void _fadeInOut::draw(int width, int height)
{
    float t = fadeTimer / fadeDuration;
    t = glm::clamp(t, 0.0f, 1.0f);

    if (t <= 0.0f) return;

    glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_TRANSFORM_BIT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(0, 0, 0, t);

    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(width, 0);
        glVertex2f(width, height);
        glVertex2f(0, height);
    glEnd();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glPopAttrib();
}
