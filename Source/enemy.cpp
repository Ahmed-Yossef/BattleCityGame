#include "enemy.h"
#include <QTimer>

EnemyTank::EnemyTank(QQuickView* parent, BCGlobal::MoveDirection direction, int x, int y) :
    BaseTank(direction, parent) {
    QQmlComponent component(parent->engine(), QUrl(QStringLiteral("qrc:/QML/NormalTank.qml")));
    Item = qobject_cast<QQuickItem*>(component.create());
    Item->setParentItem(parent->rootObject());

    XPos = x;
    YPos = y;
    InitialX = x;
    InitialY = y;
    Item->setX(x);
    Item->setY(y);

    _TankMotionTimer = new QTimer(this);
    connect(_TankMotionTimer, SIGNAL(timeout()), this, SLOT(RandomMotion()));
    _TankMotionTimer->start(100);

    _BulletFireTimer = new QTimer(this);
    connect(_BulletFireTimer, SIGNAL(timeout()), this, SLOT(Fire()));
    _BulletFireTimer->start(500);
}

EnemyTank::~EnemyTank()
{
    _TankMotionTimer->stop();
    delete _TankMotionTimer;
    _BulletFireTimer->stop();
    delete _BulletFireTimer;
}

void EnemyTank::Stop()
{
    _TankMotionTimer->stop();
    _BulletFireTimer->stop();
}

void EnemyTank::Continue()
{
    _TankMotionTimer->start(100);
    _BulletFireTimer->start(500);
}

void EnemyTank::RandomMotion()
{
    QList<BCItem *> obstacles = IsCollision(Direction);

    if(obstacles.count() != 0)
    {
        foreach(BCItem* obstacle, obstacles)
        {
            if(obstacle->ItemType() == BCGlobal::Bullet)
            {
                //qDebug("Enemy Tank: I Hit a bullet");
                return;
            }
            else if(obstacle->ItemType() == BCGlobal::Obstacle)
            {
                //qDebug("Enemy Tank: I Hit an Obstacle");
            }
            else if(obstacle->ItemType() == BCGlobal::PlayerTank)
            {
                //qDebug("Enemy Tank: I Hit the player");
            }
            else if(obstacle->ItemType() == BCGlobal::EnemyTank)
            {
                //qDebug("Enemy Tank: I Hit another enemy tank");
            }
        }
    }

    if(obstacles.count() != 0 || IsIntersectWithBoardBounds(XPos, YPos, Direction))
    {
        Direction = static_cast<BCGlobal::MoveDirection>(qrand() % 4);
        switch (Direction) {
        case BCGlobal::Forward:
            Item->setProperty("state", "Forward");
            break;
        case BCGlobal::Backward:
            Item->setProperty("state", "Backward");
            break;
        case BCGlobal::Right:
            Item->setProperty("state", "Right");
            break;
        case BCGlobal::Left:
            Item->setProperty("state", "Left");
            break;
        default:
            break;
        }
    }

    Move(Direction);
}

void EnemyTank::Fire()
{
    BaseTank::Fire();
}

