#ifndef _SHOP_H
#define _SHOP_H

#include <_common.h>
#include <_textureLoader.h>

class _shop
{
    public:
        _shop();
        virtual ~_shop();

        _textureLoader* shopUI = new _textureLoader();
        _textureLoader* shopUI2 = new _textureLoader();
        _textureLoader* exitPrompt = new _textureLoader();

        void initShop();
        void drawShopUI(float camX, float camY);
        void drawShopUI2(float camX, float camY);
        void drawExitPrompt(float camX, float camY);

    protected:

    private:
};

#endif // _SHOP_H
