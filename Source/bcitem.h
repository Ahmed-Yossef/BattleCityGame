#ifndef BCITEM_H
#define BCITEM_H
#include <QQuickItem>
#include <QQuickView>
#include "bcglobal.h"
#include <QObject>

class BCItem : public QObject
{
    Q_OBJECT

public:
    BCItem(QQuickView* parent) : Parent(parent) { }
    ~BCItem();

    void SetPosition(int row, int column);
    virtual BCGlobal::ItemTypes ItemType() { return BCGlobal::Obstacle; }

public:
    QQuickItem* Item;
    QQuickView* Parent;
};

class TravelsableObstacle : public BCItem
{

};

class NonTraversableObstacle : public BCItem
{
public:
    NonTraversableObstacle(QQuickView* parent) : BCItem(parent) {}
};

class DestroybaleObstacle : public NonTraversableObstacle
{
    Q_OBJECT
public:
    DestroybaleObstacle(QQuickView* parent) : NonTraversableObstacle(parent) {}
    virtual void Destroy() { }

    // BCItem interface
    BCGlobal::ItemTypes ItemType() { return BCGlobal::DestroyableObstacle; }
};

class Grass : public TravelsableObstacle
{
    // BCItem interface
public:
    BCGlobal::ItemTypes ItemType() { return BCGlobal::TraversableObstacle; }
};

class Brick : public DestroybaleObstacle
{
    Q_OBJECT
public:
    Brick(QQuickView* parent);

    // DestroybaleObstacle interface
    void Destroy();
    BCGlobal::ItemTypes ItemType() { return BCGlobal::DestroyableObstacle; }
};

class Falcon : public DestroybaleObstacle
{
    Q_OBJECT
public:
    Falcon(QQuickView* parent);

    // BCItem interface
    BCGlobal::ItemTypes ItemType() {return BCGlobal::Falcon; }

    // DestroybaleObstacle interface
    void Destroy();

signals:
    void IAmDestroyed();

};

class Water : NonTraversableObstacle
{
    Q_OBJECT
};

class Concrete : public NonTraversableObstacle
{
    Q_OBJECT
public:
    Concrete(QQuickView* parent);

    // BCItem interface
    BCGlobal::ItemTypes ItemType() { return BCGlobal::NonTraversableObstacle; }
};

#endif // BCITEM_H
