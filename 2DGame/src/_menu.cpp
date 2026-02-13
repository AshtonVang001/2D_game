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
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    float buttonWidth = 300;
    float buttonHeight = 80;

    bg->loadTexture("images/prlx.jpg");

    float centerX = (screenWidth - buttonWidth) / 2;
    float centerY = screenHeight / 2;

    _button play;
    play.setButton(centerX - 480, centerY - 110, buttonWidth, buttonHeight,
                   "images/tex2.jpg", ACTION_PLAY);

    _button quit;
    quit.setButton(centerX - 480, centerY + 110, buttonWidth, buttonHeight,
                   "images/tex2.jpg", ACTION_QUIT);

    _button help;
    help.setButton(centerX - 480, centerY , buttonWidth, buttonHeight,
                   "images/tex2.jpg", ACTION_HELP);

    _button settings;
    settings.setButton(centerX + 700, centerY - 350, buttonWidth - 260, buttonHeight - 50,
                   "images/settings.png", ACTION_SETTINGS);

    buttons.push_back(play);
    buttons.push_back(quit);
    buttons.push_back(help);
    buttons.push_back(settings);
}

void _menu::draw()
{
    // ---- DRAW BACKGROUND ----
    bg->bindTexture();

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(0, 0);
        glTexCoord2f(1, 0); glVertex2f(screenWidth, 0);
        glTexCoord2f(1, 1); glVertex2f(screenWidth, screenHeight);
        glTexCoord2f(0, 1); glVertex2f(0, screenHeight);
    glEnd();

    for (auto& b : buttons)
        b.draw();
}

void _menu::update()
{
    for (auto& b : buttons)
        b.update();
}

void _menu::mouseMove(int x, int y)
{
    for (auto& b : buttons)
        b.checkHover(x, y);
}

ButtonAction _menu::mouseClick(int x, int y)
{
    for (auto& b : buttons)
    {
        if (b.checkClick(x, y))
            return b.getAction();
    }
    return ACTION_NONE;
}
