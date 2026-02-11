#include "_button.h"

_button::_button()
{
    //ctor
    scale = 1.0f;
    targetScale = 1.0f;
    isHovered = false;
}

_button::~_button()
{
    //dtor
}
void _button::setButton(float x, float y, float w, float h, char* textureFile, ButtonAction action)
{
    this->x = x;
    this->y = y;
    this->width = w;
    this->height = h;
    this->action = action;

    texture.loadTexture(textureFile);
}

void _button::draw()
{
     glPushMatrix();

    glTranslatef(x + width / 2, y + height / 2, 0);
    glScalef(scale, scale, 1.0f);
    glTranslatef(-(x + width / 2), -(y + height / 2), 0);

    texture.bindTexture();

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(x, y);
        glTexCoord2f(1, 0); glVertex2f(x + width, y);
        glTexCoord2f(1, 1); glVertex2f(x + width, y + height);
        glTexCoord2f(0, 1); glVertex2f(x, y + height);
    glEnd();

    glPopMatrix();
}

void _button::update()
{
    scale += (targetScale - scale) * 0.1f;
}

void _button::checkHover(int mouseX, int mouseY)
{
    if (mouseX >= x && mouseX <= x + width &&
        mouseY >= y && mouseY <= y + height)
    {
        isHovered = true;
        targetScale = 1.1f;
    }
    else
    {
        isHovered = false;
        targetScale = 1.0f;
    }
}

bool _button::checkClick(int mouseX, int mouseY)
{
    return (mouseX >= x && mouseX <= x + width &&
            mouseY >= y && mouseY <= y + height);
}

ButtonAction _button::getAction()
{
    return action;
}
