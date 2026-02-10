#pragma once
#include <vector>

class _collisionCheck {
public:
    _collisionCheck();
    ~_collisionCheck();

    bool loadFromTexture(
        const unsigned char* pixels,
        int width,
        int height,
        int channels
    );

    bool isSolidUV(float u, float v) const;
    bool isSolidPixel(int x, int y) const;

    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    int width = 0;
    int height = 0;
    std::vector<bool> solid;
};
