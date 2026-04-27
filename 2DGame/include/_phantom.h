#pragma once
#include "_enemies.h"
#include <_common.h>

class _phantom : public _enemies
{
public:
    _phantom();
    virtual ~_phantom();

    void update(float dt, vec3 playerPos); // optional override
};
