#ifndef PLAYER_H
#define PLAYER_H
#include "basetank.h"
#include <QQuickItem>
#include <QQuickView>


class PlayerTank : public BaseTank
{
    Q_OBJECT

public:
    PlayerTank(QQuickView* parent, BCGlobal::MoveDirection Direction, int x, int y);

    // BCItem interface
    BCGlobal::ItemTypes ItemType() { return BCGlobal::PlayerTank; }

public:
    bool IsAlive;
};

#endif // PLAYER_H
