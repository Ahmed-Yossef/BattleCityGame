#ifndef BULLET_H
#define BULLET_H
#include <QQuickItem>
#include <QQuickView>
#include "bcglobal.h"
#include "movableitem.h"


class Bullet : public MovableItem
{
    Q_OBJECT
public:
    Bullet(QQuickView* parent, BCGlobal::MoveDirection Direction);
    ~Bullet();

    void Destroy();
    void SetPosition(int x, int y);
    int Speed() const { return 8; }

    // BCItem interface
    BCGlobal::ItemTypes ItemType() { return BCGlobal::Bullet; }

private:
    QTimer * _BulletMotionTimer;

signals:
    void Hit();

public slots:
    void RandomMotion();
};

#endif // BULLET_H
