#pragma once
#include <vector>
#include <string>
#include <_common.h>
#include <SOIL2.h>
#include <iomanip>

class _videoLoader {
public:
    _videoLoader();
    ~_videoLoader();

    void loadFrames(const std::string& folder, int frameCount, float fps);
    void update(float deltaTime);
    void draw(float x, float y, float w, float h);

    void play(bool loop = true);
    void stop();
    void reset();

    bool isPlaying;

private:
    std::vector<GLuint> frames;

    int currentFrame;
    int totalFrames;

    float frameTime;     // time per frame (1/fps)
    float timer;

    bool loop;
};
