#include "_collisionCheck.h"

_collisionCheck::_collisionCheck() {}
_collisionCheck::~_collisionCheck() {}

bool _collisionCheck::loadFromTexture(
    const unsigned char* pixels,
    int w,
    int h,
    int channels
) {
    if (!pixels || channels < 4)
        return false;

    width = w;
    height = h;
    solid.resize(width * height);

    const unsigned char ALPHA_THRESHOLD = 128;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int idx = (y * width + x) * channels;
            unsigned char alpha = pixels[idx + 3];
            solid[y * width + x] = alpha > ALPHA_THRESHOLD;
        }
    }

    return true;
}

bool _collisionCheck::isSolidPixel(int x, int y) const {
    if (x < 0 || y < 0 || x >= width || y >= height)
        return false;
    return solid[y * width + x];
}

bool _collisionCheck::isSolidUV(float u, float v) const {
        if (u < 0.f || u > 1.f || v < 0.f || v > 1.f)
            return false;

        int x = int(u * width);
        int y = int(v * height);

        return isSolidPixel(x, y);
}
