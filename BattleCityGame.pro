TEMPLATE = app

QT += qml quick

SOURCES += \
    Source/basetank.cpp \
    Source/bcglobal.cpp \
    Source/bcitem.cpp \
    Source/bullet.cpp \
    Source/enemy.cpp \
    Source/game.cpp \
    Source/gameboard.cpp \
    Source/main.cpp \
    Source/movableitem.cpp \
    Source/player.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    Source/basetank.h \
    Source/bcglobal.h \
    Source/bcitem.h \
    Source/bullet.h \
    Source/enemy.h \
    Source/game.h \
    Source/gameboard.h \
    Source/movableitem.h \
    Source/player.h
