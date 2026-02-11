#ifndef _MENU_H
#define _MENU_H

#include <_button.h>
#include <vector>

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

    protected:

    private:
        std::vector<_button> buttons;
};

#endif // _MENU_H
