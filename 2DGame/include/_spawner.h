#ifndef _SPAWNER_H
#define _SPAWNER_H

#include <vector>
#include <_enemies.h>
#include <_boss.h>
#include <_phantom.h>
#include <_common.h>

class _spawner
{
    public:
        _spawner();
        _spawner(int count, float delay, float x, float y, bool boss, int level);
        virtual ~_spawner();

        void update(float dt, std::vector<_enemies*>& enemies, _collisionCheck* map);
        bool isFinished();

        int totalToSpawn;
        int spawned;
        int phantomSpawned = 0;
        int phantomCount = 0;

        int localLevelModifier;

        float spawnDelay;
        float timer;

        float spawnX;
        float spawnY;

        int count;
        float delay;
        float x;
        float y;

        bool spawnBoss;
        bool waveInitialized;


    protected:

    private:
};

#endif // _SPAWNER_H
