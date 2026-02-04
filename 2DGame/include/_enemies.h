#ifndef _ENEMIES_H
#define _ENEMIES_H


class _enemies : public _sprite
{
    public:
        _enemies();
        virtual ~_enemies();

        void enemyMovement();
        void enemyHealth();


    protected:

    private:
};

#endif // _ENEMIES_H
