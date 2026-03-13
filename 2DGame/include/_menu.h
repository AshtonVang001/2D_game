#ifndef _MENU_H
#define _MENU_H

#include <_button.h>
#include <vector>
#include <_textureLoader.h>
#include <_timer.h>

class _menu
{
    public:
        _menu();
        virtual ~_menu();

        void init(int screenWidth, int screenHeight);
        void draw();
        void update(float);
        void mouseMove(int x, int y);
        ButtonAction mouseClick(int x, int y);

        _textureLoader *bg = new _textureLoader();
        int screenWidth;
        int screenHeight;

        float bgAlpha;
        //float buttonAlpha;
        float fadeSpeed;
        bool fadeDone;

        float buttonAlpha = 0.0f; // start fully transparent
        float buttonFadeSpeed = 0.9f; // tweak for speed

    protected:

    private:
        _button play;
        _button quit;
        _button help;
        _button settings;
        std::vector<_button*> buttons;
};

#endif // _MENU_H
