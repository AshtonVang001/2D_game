#pragma once
#include "_common.h" // assuming you use this for pos
#include "_textureLoader.h" // or whatever your texture class is
#include <_sprite.h>
#include <_common.h>

class _coin
{
public:
    _coin();
    ~_coin();

    // ---- Core ----
    void init();
    void update(float dt, float playerX, float playerY);
    void draw();

    static _textureLoader* sharedTex;
    static _sprite* sharedSprite;
    //_sprite sprite;

    // ---- Data ----
    vec3 pos;
    vec3 vel;

    float size;
    float lifeTime;
    float maxLife;

    int value;

    bool destroy;

private:

    float animTimer;
    float animSpeed;
};
