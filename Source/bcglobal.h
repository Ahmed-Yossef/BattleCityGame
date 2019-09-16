#ifndef BCGLOBAL_H
#define BCGLOBAL_H
#include <QObject>


class BCGlobal : public QObject
{
    Q_OBJECT

public:
    enum ObstacleType { Ground, Brick, Water, Concrete };
    enum MoveDirection { Forward, Backward, Left, Right };
    enum TankType { Basic, Fast, Power, Armor };
    enum ItemTypes { PlayerTank, EnemyTank, Bullet,
                     DestroyableObstacle, TraversableObstacle, NonTraversableObstacle, Obstacle,
                     Falcon };

    BCGlobal();
};

#endif // BCGLOBAL_H
