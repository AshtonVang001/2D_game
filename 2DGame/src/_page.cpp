#include "_page.h"

_page::_page() {}
_page::~_page() {}

void _page::init(int screenWidth, int screenHeight, char* backgroundFile)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    bg->loadTexture(backgroundFile);
}

void _page::draw()
{
    bg->bindTexture();

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(0, 0);
        glTexCoord2f(1, 0); glVertex2f(screenWidth, 0);
        glTexCoord2f(1, 1); glVertex2f(screenWidth, screenHeight);
        glTexCoord2f(0, 1); glVertex2f(0, screenHeight);
    glEnd();
}
