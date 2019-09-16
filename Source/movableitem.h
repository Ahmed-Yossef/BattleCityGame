#ifndef MOVABLEITEM_H
#define MOVABLEITEM_H
#include "bcitem.h"
#include "bcglobal.h"

class MovableItem : public BCItem
{
    Q_OBJECT

public:
    MovableItem(BCGlobal::MoveDirection direction, QQuickView* parent) : BCItem(parent), Direction(direction){}

    virtual bool Move(BCGlobal::MoveDirection Direction);
    virtual int Speed() const = 0;
    void SetPosition(int x, int y);

protected:
    BCGlobal::MoveDirection GetDirection() const { return Direction; }
    virtual bool IsIntersectWithBoardBounds(int x, int y, BCGlobal::MoveDirection Direction);
    virtual QList<BCItem *> IsCollision(BCGlobal::MoveDirection Direction);
    virtual QList<BCItem *> IsCollisionWithObject(QRectF &viewRect);

public:
    int XPos;
    int YPos;
    BCGlobal::MoveDirection Direction;
};

#endif // MOVABLEITEM_H
