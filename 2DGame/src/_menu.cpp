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
    float buttonWidth = 300;
    float buttonHeight = 80;

    float centerX = (screenWidth - buttonWidth) / 2;
    float centerY = screenHeight / 2;

    _button play;
    play.setButton(centerX, centerY - 20, buttonWidth, buttonHeight,
                   "images/tex2.jpg", ACTION_PLAY);

    _button quit;
    quit.setButton(centerX, centerY + 100, buttonWidth, buttonHeight,
                   "images/tex2.jpg", ACTION_QUIT);

    buttons.push_back(play);
    buttons.push_back(quit);
}

void _menu::draw()
{
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
