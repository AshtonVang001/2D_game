#ifndef _PAGE_H
#define _PAGE_H

#include <_textureLoader.h>

class _page
{
    public:
        _page();
        virtual ~_page();

        void init(int screenWidth, int screenHeight, char* backgroundFile);
    void draw();

    protected:

    private:
        _textureLoader *bg = new _textureLoader();

        int screenWidth;
        int screenHeight;
};

#endif // _PAGE_H
