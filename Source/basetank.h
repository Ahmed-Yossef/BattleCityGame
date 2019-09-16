#ifndef BASETANK_H
#define BASETANK_H
#include <QQuickItem>
#include <QPointer>
#include "bcglobal.h"
#include "bullet.h"
#include "movableitem.h"

class BaseTank : public MovableItem
{
    Q_OBJECT

public:
    BaseTank(BCGlobal::MoveDirection direction, QQuickView* parent) :
        MovableItem(direction, parent), _Bullet(NULL) {}
    ~BaseTank();

    virtual void Fire();
    virtual void ReSpawn();
    virtual int Speed() const { return 8; }
    virtual int Health() const { return 1; }

private:
    QPointer<Bullet> _Bullet;

protected:
    int InitialX;
    int InitialY;

signals:
    void Hit();
    void IAmDestroyed();

private slots:
    void BulletExplode();
    void CheckIfStartPositionIsEmpty();
};

#endif // BASETANK_H
