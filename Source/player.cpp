#include "player.h"
#include <QQuickItem>
#include <QQuickView>
#include <QSGSimpleRectNode>


PlayerTank::PlayerTank(QQuickView* parent, BCGlobal::MoveDirection direction, int x, int y) :
    BaseTank(direction, parent)
{
    QQmlComponent component(parent->engine(), QUrl(QStringLiteral("qrc:/QML/PlayerTank.qml")));
    Item = qobject_cast<QQuickItem*>(component.create());
    Item->setParentItem(parent->rootObject());

    XPos = x;
    YPos = y;
    InitialX = x;
    InitialY = y;
    Item->setX(x);
    Item->setY(y);
}
