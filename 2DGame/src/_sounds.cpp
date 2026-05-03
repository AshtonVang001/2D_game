#include "_sounds.h"

_sounds::_sounds()
{
    //ctor
}

_sounds::~_sounds()
{
    //dtor
    eng->drop();
}

void _sounds::playMusic(char* filename)
{
    eng->setAllSoundsPaused(false);

    if (!eng->isCurrentlyPlaying(filename))
    {
        eng->play2D(filename, true, false);
    }
}

void _sounds::playSound(char* filename)
{
    eng->setAllSoundsPaused(false);
    if (!eng->isCurrentlyPlaying(filename)) {
        eng->play2D(filename, false, false);
    }
}

void _sounds::pauseSound(char* filename)
{
    eng->setAllSoundsPaused(true);
}

void _sounds::initSounds()
{
    if (!eng) {
        cout << "ERROR: The sound could not load" << endl;
    }
}
