#include "bcitem.h"

Brick::Brick(QQuickView *parent) : DestroybaleObstacle(parent)
{
    QQmlComponent component(parent->engine(), QUrl(QStringLiteral("qrc:/QML/Brick.qml")));
    Item = qobject_cast<QQuickItem*>(component.create());
    Item->setParentItem(parent->rootObject());
}

void Brick::Destroy()
{
    delete Item;
}

BCItem::~BCItem()
{
    delete Item;
}

void BCItem::SetPosition(int row, int column)
{
    Item->setX(row);
    Item->setY(column);
}

Concrete::Concrete(QQuickView *parent) : NonTraversableObstacle(parent)
{
    QQmlComponent component(parent->engine(), QUrl(QStringLiteral("qrc:/QML/Concrete.qml")));
    Item = qobject_cast<QQuickItem*>(component.create());
    Item->setParentItem(parent->rootObject());
}

Falcon::Falcon(QQuickView *parent) : DestroybaleObstacle(parent)
{
    QQmlComponent component(parent->engine(), QUrl(QStringLiteral("qrc:/QML/Falcon.qml")));
    Item = qobject_cast<QQuickItem*>(component.create());
    Item->setParentItem(parent->rootObject());
}

void Falcon::Destroy()
{
    Item->setParent(NULL);
}
