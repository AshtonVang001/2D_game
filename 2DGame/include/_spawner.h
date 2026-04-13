#ifndef _SPAWNER_H
#define _SPAWNER_H

#include <vector>
#include <_enemies.h>

class _spawner
{
    public:
        _spawner();
        _spawner(int count, float delay, float x, float y);
        virtual ~_spawner();

        void update(float dt, std::vector<_enemies*>& enemies, _collisionCheck* map);
        bool isFinished();

        int totalToSpawn;
        int spawned;

        float spawnDelay;
        float timer;

        float spawnX;
        float spawnY;

        int count;
        float delay;
        float x;
        float y;


    protected:

    private:
};

#endif // _SPAWNER_H
