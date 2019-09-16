#include "movableitem.h"
#include "basetank.h"
#include "bullet.h"
#include "gameboard.h"


bool MovableItem::Move(BCGlobal::MoveDirection direction)
{
    QList<BCItem *> obstacle = IsCollision(direction);

    if(!IsIntersectWithBoardBounds(XPos, YPos, direction) &&  obstacle.count() == 0)
    {
        switch(direction)
        {
        case BCGlobal::Right: //Right
            XPos += Speed();
            break;

        case BCGlobal::Left: // Left
            XPos -= Speed();
            break;

        case BCGlobal::Forward: // Up
            YPos -= Speed();
            break;

        case BCGlobal::Backward: // Down
            YPos += Speed();
            break;

        default:
            break;
        }

        Item->setX(XPos);
        Item->setY(YPos);

        this->Direction = direction;

        return true;
    }

    return false;
}

void MovableItem::SetPosition(int x, int y)
{
    XPos = x;
    YPos = y;

    Item->setX(XPos);
    Item->setY(YPos);
}

bool MovableItem::IsIntersectWithBoardBounds(int x, int y, BCGlobal::MoveDirection direction)
{
    bool isCollision = false;

    switch(direction) {
    case BCGlobal::Right: //Right
        isCollision =  !(x + Item->width() < 416 );
        break;

    case BCGlobal::Left: // Left
        isCollision =  !(x >= Speed());
        break;

    case BCGlobal::Forward: // Up
        isCollision = !(y >= Speed());
        break;

    case BCGlobal::Backward: // Down
        isCollision = !(y + Item->height() < Parent->height());
        break;

    default:
        break;
    }

    return isCollision;
}

QList<BCItem *> MovableItem::IsCollisionWithObject(QRectF &viewRect)
{
    GameBoard* parent = qobject_cast<GameBoard *>(this->Parent);
    QList<BCItem *> collidedItemsList;

    foreach(BCItem* obstacle, parent->Items)
    {
        if (obstacle != this && obstacle != NULL)
        {
            const QRectF obstacleRect(obstacle->Item->x(), obstacle->Item->y(), obstacle->Item->width(), obstacle->Item->height());

            if(viewRect.intersects(obstacleRect))
            {
                if (obstacle->ItemType() != BCGlobal::TraversableObstacle)
                    collidedItemsList.append(obstacle);
            }
        }
    }

    return collidedItemsList;
}

QList<BCItem*> MovableItem::IsCollision(BCGlobal::MoveDirection direction)
{
    QList<BCItem*> obstacle;
    QRectF viewRect;

    switch(direction)
    {
    case BCGlobal::Right:
        viewRect.setRect(Item->x() + 4, Item->y(), Item->width(), Item->height());
        obstacle = IsCollisionWithObject(viewRect);
        break;

    case BCGlobal::Left:
        viewRect.setRect(Item->x() - 4, Item->y(), Item->width(), Item->height());
        obstacle = IsCollisionWithObject(viewRect);
        break;

    case BCGlobal::Forward:
        viewRect.setRect(Item->x(), Item->y() - 4, Item->width(), Item->height());
        obstacle = IsCollisionWithObject(viewRect);
        break;

    case BCGlobal::Backward:
        viewRect.setRect(Item->x(), Item->y() + 4, Item->width(), Item->height());
        obstacle = IsCollisionWithObject(viewRect);
        break;

    default:
        break;
    }

    return obstacle;
}
