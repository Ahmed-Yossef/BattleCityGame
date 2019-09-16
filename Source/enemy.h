#ifndef ENEMY_H
#define ENEMY_H
#include "basetank.h"
#include "bcglobal.h"
#include <QQuickView>
#include <QTimer>

class EnemyTank : public BaseTank
{
    Q_OBJECT
public:
    EnemyTank(QQuickView* parent, BCGlobal::MoveDirection Direction, int x, int y);
    ~EnemyTank();

    virtual int Speed() const { return 0; }
    virtual int Health() const { return 0;  }
    virtual void Stop();
    virtual void Continue();

    // BCItem interface
    BCGlobal::ItemTypes ItemType() { return BCGlobal::EnemyTank; }

public slots:
    void RandomMotion();
    void Fire();

protected:
    QTimer * _TankMotionTimer;
    QTimer * _BulletFireTimer;
};

class BasicEnemyTank : public EnemyTank
{
public:
    BasicEnemyTank(QQuickView* parent, BCGlobal::MoveDirection direction, int x, int y) :
        EnemyTank(parent, direction, x ,y) { }

    // MovableItem interface
    int Speed() const {return 4;}
};

class FastEnemyTank : public EnemyTank{

};

class ArmorEnemyTank : public EnemyTank{

};

class PowerEnemyTank : public EnemyTank{

};

#endif // ENEMY_H
