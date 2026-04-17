#include "_shop.h"

_shop::_shop()
{
    //ctor
}

_shop::~_shop()
{
    //dtor
}

void _shop::initShop() {
    shopUI->loadTexture("images/shopUI.png");
    exitPrompt->loadTexture("images/exitPrompt.png");
}

void _shop::drawShopUI(float screenW, float screenH)
{
    glPushMatrix();

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);

    float width = 800.0f;
    float height = 250.0f;

    float halfW = width * 0.5f;
    float halfH = height * 0.5f;

    float x = screenW * 0.5f;
    float y = screenH * 0.8f;

    glColor4f(1, 1, 1, 1);
    shopUI->bindTexture();

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(x - halfW, y - halfH);
        glTexCoord2f(1, 0); glVertex2f(x + halfW, y - halfH);
        glTexCoord2f(1, 1); glVertex2f(x + halfW, y + halfH);
        glTexCoord2f(0, 1); glVertex2f(x - halfW, y + halfH);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void _shop::drawExitPrompt(float screenW, float screenH)
{
    glPushMatrix();

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);

    float width = 800.0f;
    float height = 250.0f;

    float halfW = width * 0.5f;
    float halfH = height * 0.5f;

    float x = screenW * 0.5f;
    float y = screenH * 0.8f;

    glColor4f(1, 1, 1, 1);
    exitPrompt->bindTexture();

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(x - halfW, y - halfH);
        glTexCoord2f(1, 0); glVertex2f(x + halfW, y - halfH);
        glTexCoord2f(1, 1); glVertex2f(x + halfW, y + halfH);
        glTexCoord2f(0, 1); glVertex2f(x - halfW, y + halfH);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
