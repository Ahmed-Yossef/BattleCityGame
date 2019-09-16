#include "bullet.h"
#include <QTimer>
#include "enemy.h"
#include "player.h"
#include "gameboard.h"

Bullet::Bullet(QQuickView *parent, BCGlobal::MoveDirection direction) :
    MovableItem(direction, parent)
{
    QQmlComponent component(parent->engine(), QUrl(QStringLiteral("qrc:/QML/Bullet.qml")));
    Item = qobject_cast<QQuickItem*>(component.create());
    Item->setParentItem(parent->rootObject());

    _BulletMotionTimer = new QTimer(this);
    connect(_BulletMotionTimer, SIGNAL(timeout()), this, SLOT(RandomMotion()));
    _BulletMotionTimer->start(20);
}

Bullet::~Bullet()
{
    _BulletMotionTimer->stop();
    _BulletMotionTimer = NULL;
    Item->setParent(NULL);
}

void Bullet::SetPosition(int x, int y)
{
    XPos = x;
    YPos = y;
    Item->setX(XPos);
    Item->setY(YPos);
}

void Bullet::Destroy()
{
    Item->setParent(NULL);
    _BulletMotionTimer->stop();
}

void Bullet::RandomMotion()
{
    GameBoard* parent = qobject_cast<GameBoard *>(this->Parent);

    if(!Move(Direction))
    {
        QList<BCItem*> obstacles = IsCollision(Direction);

        if(obstacles.count() != 0)
        {
            foreach(BCItem* obstacle, obstacles)
            {
                if (obstacle->ItemType() == BCGlobal::PlayerTank)
                {
                    //qDebug("Bullet Says: I Hit APlayer Tank");
                    BaseTank* tank = qobject_cast<PlayerTank *>(obstacle);
                    parent->Items.removeOne(this); // Remove Bullet from the List of Item
                    emit tank->IAmDestroyed();
                }
                else if (obstacle->ItemType() == BCGlobal::EnemyTank)
                {
                    //qDebug("Bullet Says: I Hit An Enemy Tank");
                    BaseTank* tank = qobject_cast<EnemyTank *>(obstacle);
                    parent->Items.removeOne(this); // Remove Bullet from the List of Item
                    emit tank->IAmDestroyed();
                }
                else if (obstacle->ItemType() == BCGlobal::Bullet)
                {
                    //qDebug() << "Bullet Says: I Hit Another Bullet";
                    Bullet* bullet = qobject_cast<Bullet *>(obstacle);
                    parent->Items.removeOne(bullet);
                    emit bullet->Hit();
                }
                else if (obstacle->ItemType() == BCGlobal::DestroyableObstacle)
                {
                    //qDebug("Bullet Says: I Hit A Destroyable Obstacle");
                    Brick* brick = qobject_cast<Brick *>(obstacle);

                    if(parent->Items.removeOne(brick)) ;
                        //qDebug("Bullet Says: Obstacle Destroyed");
                    brick->Destroy();
                }
                else if (obstacle->ItemType() == BCGlobal::NonTraversableObstacle)
                {
                   // qDebug("Bullet Says: I Hit An Obstacle");
                }
                else if (obstacle->ItemType() == BCGlobal::Falcon)
                {
                    //qDebug("Bullet Says: I Hit THE FALCON");
                    Falcon* falcon = qobject_cast<Falcon *>(obstacle);
                    emit falcon->IAmDestroyed();
                }
                else
                {
                }
            }
        }
        else {
            //qDebug("Bullet Says: I Hit The Boarders");
        }

        parent->Items.removeOne(this); // Remove Bullet from the List of Item
        emit Hit();
    }
}
