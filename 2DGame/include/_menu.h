#ifndef _MENU_H
#define _MENU_H

#include <_button.h>
#include <vector>
#include <_textureLoader.h>

class _menu
{
    public:
        _menu();
        virtual ~_menu();

        void init(int screenWidth, int screenHeight);
        void draw();
        void update();
        void mouseMove(int x, int y);
        ButtonAction mouseClick(int x, int y);

        _textureLoader *bg = new _textureLoader();
        int screenWidth;
        int screenHeight;

    protected:

    private:
        std::vector<_button> buttons;
};

#endif // _MENU_H
