#ifndef _BUTTON_H
#define _BUTTON_H

#include <_textureLoader.h>
#include <_common.h>

enum ButtonAction
{
    ACTION_NONE,
    ACTION_PLAY,
    ACTION_QUIT,
    ACTION_HELP,
    ACTION_SETTINGS,
    ACTION_PAUSE,
    ACTION_RESUME,

    ACTION_HEALTHBOOST,
    ACTION_GOLDENHEART,
    ACTION_COINBOOST,
    ACTION_VAMPIRE,
    ACTION_ATTACKBOOST,
    ACTION_ARMORBOOST,
    ACTION_SPEEDBOOST,
    ACTION_DASHBOOST,
    ACTION_EXIT,

    ACTION_YES,
    ACTION_NO,
    ACTION_WIN,

    ACTION_RETURN
};

class _button
{
    public:
        _button();
        virtual ~_button();

        void setButton(float x, float y, float w, float h, char* textureFile, ButtonAction action);
        void draw();
        void update();                         // handles hover scaling
        void checkHover(int mouseX, int mouseY);
        bool checkClick(int mouseX, int mouseY);

        ButtonAction getAction();

    protected:

    private:
        float x, y;
        float width, height;

        float scale;
        float targetScale;

        bool isHovered;

        ButtonAction action;

        _textureLoader texture;

};

#endif // _BUTTON_H
