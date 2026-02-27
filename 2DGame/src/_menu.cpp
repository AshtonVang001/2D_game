#include "_menu.h"

_menu::_menu()
{
    //ctor
}

_menu::~_menu()
{
    //dtor
}
void _menu::init(int screenWidth, int screenHeight)
{
    // Only set fade values the FIRST time
    if(!fadeDone)
    {
        bgAlpha = 1.0f;      // start fully black
        fadeSpeed = 0.4f;    // adjust speed if you want
    }

    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    float buttonWidth = 300;
    float buttonHeight = 80;

    //bg->loadTexture("images/prlx.jpg");
    bg->loadTexture("images/map Layer 1 ALT.png");

    float centerX = (screenWidth - buttonWidth) / 2;
    float centerY = screenHeight / 2;


    play.setButton(centerX - 480, centerY - 110, buttonWidth, buttonHeight,
                   "images/tex2.jpg", ACTION_PLAY);


    quit.setButton(centerX - 480, centerY + 110, buttonWidth, buttonHeight,
                   "images/tex2.jpg", ACTION_QUIT);


    help.setButton(centerX - 480, centerY , buttonWidth, buttonHeight,
                   "images/tex2.jpg", ACTION_HELP);


    settings.setButton(centerX + 700, centerY - 350, buttonWidth - 260, buttonHeight - 50,
                   "images/settings.png", ACTION_SETTINGS);

    buttons.clear();
    buttons.push_back(&play);
    buttons.push_back(&quit);
    buttons.push_back(&help);
    buttons.push_back(&settings);
}

void _menu::draw()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // ---- DRAW BACKGROUND ----

    /* OG
    bg->bindTexture();

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(0, 0);
        glTexCoord2f(1, 0); glVertex2f(screenWidth, 0);
        glTexCoord2f(1, 1); glVertex2f(screenWidth, screenHeight);
        glTexCoord2f(0, 1); glVertex2f(0, screenHeight);
    glEnd();
    */

    bg->bindTexture();

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glScalef(5, 5, 1);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(0, 0);
        glTexCoord2f(1, 0); glVertex2f(screenWidth, 0);
        glTexCoord2f(1, 1); glVertex2f(screenWidth, screenHeight);
        glTexCoord2f(0, 1); glVertex2f(0, screenHeight);
    glEnd();
    glPopMatrix();

    glColor4f(1.0f, 1.0f, 1.0f, buttonAlpha);
    for (auto& b : buttons)
        b->draw();
    if(!fadeDone)
    {
        glDisable(GL_TEXTURE_2D);

        glColor4f(0.0f, 0.0f, 0.0f, bgAlpha);

        glBegin(GL_QUADS);
            glVertex2f(0, 0);
            glVertex2f(screenWidth, 0);
            glVertex2f(screenWidth, screenHeight);
            glVertex2f(0, screenHeight);
        glEnd();

        glEnable(GL_TEXTURE_2D);
    }
    glDisable(GL_BLEND);
}

void _menu::update(float deltaTime)
{
    for (auto& b : buttons)
        b->update();

    // Run fade only if not done yet
    if(!fadeDone)
    {
        bgAlpha -= fadeSpeed * deltaTime;

        if(bgAlpha <= 0.0f)
        {
            bgAlpha = 0.0f;
            fadeDone = true; // never fade again
        }
    }
    else
    {
        // ---- Button fade ----
        if(buttonAlpha < 1.0f)
        {
            buttonAlpha += buttonFadeSpeed * deltaTime;
            if(buttonAlpha > 1.0f) buttonAlpha = 1.0f;
        }
    }
}

void _menu::mouseMove(int x, int y)
{
    for (auto& b : buttons)
        b->checkHover(x, y);
}

ButtonAction _menu::mouseClick(int x, int y)
{
    for (auto& b : buttons)
    {
        if (b->checkClick(x, y))
            return b->getAction();
    }
    return ACTION_NONE;
}
