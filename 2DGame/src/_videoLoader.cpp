#include "_videoLoader.h"
#include <sstream>

_videoLoader::_videoLoader()
{
    currentFrame = 0;
    totalFrames = 0;
    timer = 0.0f;
    frameTime = 0.1f;
    loop = true;
    isPlaying = false;
}

_videoLoader::~_videoLoader()
{
    for (auto tex : frames)
        glDeleteTextures(1, &tex);
}

void _videoLoader::loadFrames(const std::string& folder, int frameCount, float fps)
{
    totalFrames = frameCount;
    frameTime = 1.0f / fps;

    frames.clear();

    // Extract base name from folder (e.g., "testVideo")
    std::string baseName = folder.substr(folder.find_last_of("/\\") + 1);

    for (int i = 1; i <= frameCount; i++)
    {
        std::stringstream ss;

        ss << folder << "/" << baseName;

        // zero-pad to 4 digits
        ss << std::setw(4) << std::setfill('0') << i;

        ss << ".tga";

        std::string path = ss.str();

        GLuint tex = SOIL_load_OGL_texture(
            path.c_str(),
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y
        );

        if (tex == 0)
        {
            printf("Failed to load: %s\n", path.c_str());
        }
        else
        {
            printf("Loaded: %s\n", path.c_str());
        }

        frames.push_back(tex);
    }
}

void _videoLoader::play(bool looped)
{
    loop = looped;
    isPlaying = true;
}

void _videoLoader::stop()
{
    isPlaying = false;
}

void _videoLoader::reset()
{
    currentFrame = 0;
    timer = 0.0f;
}

void _videoLoader::update(float deltaTime)
{
    if (!isPlaying || frames.empty()) return;

    timer += deltaTime;

    if (timer >= frameTime)
    {
        timer = 0.0f;
        currentFrame++;

        if (currentFrame >= totalFrames)
        {
            if (loop)
                currentFrame = 0;
            else
            {
                currentFrame = totalFrames - 1;
                isPlaying = false;
            }
        }
    }
}

void _videoLoader::draw(float x, float y, float w, float h)
{
    if (frames.empty()) return;

    float aspect = 9.0f / 16.0f;
    h = w * aspect;

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindTexture(GL_TEXTURE_2D, frames[currentFrame]);

    glBegin(GL_QUADS);
        glTexCoord2f(0,1); glVertex3f(x,     y,     0);
        glTexCoord2f(1,1); glVertex3f(x + w, y,     0);
        glTexCoord2f(1,0); glVertex3f(x + w, y + h, 0);
        glTexCoord2f(0,0); glVertex3f(x,     y + h, 0);
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}
