#include "basetank.h"
#include "bullet.h"
#include "gameboard.h"
#include <QTimer>


BaseTank::~BaseTank()
{
    delete _Bullet;
}

void BaseTank::Fire()
{
    if (_Bullet == NULL)
    {
        GameBoard* parent = qobject_cast<GameBoard *>(this->Parent);

        // Create New Bullet
        _Bullet = new Bullet(Parent, Direction);
        connect(_Bullet, SIGNAL(Hit()), SLOT(BulletExplode()));
        parent->Items.append(_Bullet);

        switch(Direction)
        {
        case BCGlobal::Right: // Right
            _Bullet->SetPosition(XPos + Item->width() + 2, YPos + ((Item->height() / 2) - (_Bullet->Item->height() / 2)));
            _Bullet->Item->setProperty("state", "Right");
            break;
        case BCGlobal::Left: // Left
            _Bullet->SetPosition(XPos - (_Bullet->Item->height() / 2) - 2, YPos + ((Item->height() / 2) - (_Bullet->Item->height() / 2)));
            _Bullet->Item->setProperty("state", "Left");
            break;
        case BCGlobal::Forward: // Up
            _Bullet->SetPosition(XPos + ((Item->height() / 2) - (_Bullet->Item->height() / 2)), YPos - (_Bullet->Item->height() / 2) - 2);
            _Bullet->Item->setProperty("state", "Forward");
            break;
        case BCGlobal::Backward: // Down
            _Bullet->SetPosition(XPos + ((Item->height() / 2) - (_Bullet->Item->height() / 2)), YPos + Item->height() + 2);
            _Bullet->Item->setProperty("state", "Backword");
            break;
        default:
            break;
        }
    }
}

void BaseTank::ReSpawn()
{
    XPos = InitialX;
    YPos = InitialY;
    CheckIfStartPositionIsEmpty();
    Item->setX(XPos);
    Item->setY(YPos);
}

void BaseTank::CheckIfStartPositionIsEmpty()
{
    QList<BCItem*> obstacles;
    QRectF tankRect;
    bool reSpawnPosfound = false;
    int newX = InitialX;
    int newY = InitialY;

    while (!reSpawnPosfound) {
        tankRect.setRect(newX, newY, Item->width(), Item->height());
        obstacles = IsCollisionWithObject(tankRect);

        if(obstacles.count() != 0)
        {
            //qDebug() << "Can't Find A Free Spot to Respawn IN";
            reSpawnPosfound = false;
            newX += Item->width();
        }
        else
        {
            //qDebug() << "Found A Free Spot to Respawn IN";
            Item->setX(XPos);
            Item->setY(YPos);
            reSpawnPosfound = true;
            XPos = newX;
            YPos = newY;
        }
    }

    obstacles.clear();
}

void BaseTank::BulletExplode()
{
    delete _Bullet;
    _Bullet = NULL;
}

