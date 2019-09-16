#include <QQuickView>
#include <QQuickItem>
#include <QQmlProperty>
#include <QQmlEngine>
#include <QList>
#include "enemy.h"
#include "gameboard.h"
#include "player.h"

GameBoard::GameBoard(QString levelMAPPath) :
    QQuickView(QUrl(QStringLiteral("qrc:/QML/BattleCityBoard.qml")))
{
    for (int i = 0; i < 3; i++)
        _enemyTanks[i] = nullptr;

    _playerTank = nullptr;
    _falcon = nullptr;

    CellSize = 32;
    BoardSize = 13;
    NumberOfEnemyTanks = 20;
    RemainingLives = 4;

    Initialize(levelMAPPath);

    rootObject()->setProperty("enemiesLeft", QVariant("Enemies Left: " + QString::number(NumberOfEnemyTanks)));
    rootObject()->setProperty("livesLeft", QVariant("Lives Left: " + QString::number(RemainingLives)));

    show();
}

GameBoard::~GameBoard()
{
    // All Items
    foreach (BCItem* item, Items)
        if (item != nullptr) delete item;

    // Enemy Tanks
    for (int i = 0; i < 3; i++)
    {
        if (_enemyTanks[i] != nullptr)
            delete _enemyTanks[i];
    }
//    delete[] _enemyTanks;

    // Player
    if (_playerTank != nullptr)
        delete _playerTank;

    // Falcon
    if (_falcon != nullptr)
        delete _falcon;
}


void GameBoard::Initialize(QString levelMAPPath)
{
    rootObject()->setProperty("winLose", QVariant("Playing"));

    foreach (BCItem* item, Items)
        Items.removeOne(item);

    for (int i = 0; i < 3; i++)
    {
        if (_enemyTanks[i] != nullptr)
            delete _enemyTanks[i];
    }

    if (_playerTank != nullptr)
        delete _playerTank;

    if (_falcon != nullptr)
        delete _falcon;

    NumberOfEnemyTanks = 20;
    RemainingLives = 4;

    // Create Player
    _playerTank = new PlayerTank(this, BCGlobal::Forward, 128 ,392);
    connect(_playerTank, SIGNAL(IAmDestroyed()), SLOT(PlayerDestroyed()));
    Items.append(_playerTank);
    _playerTank->IsAlive = true;

    // Creat Falcon
    _falcon = new Falcon(this);
    _falcon->SetPosition(192, 392);
    connect(_falcon, SIGNAL(IAmDestroyed()), SLOT(FalconDestroyed()));
    Items.append(_falcon);
    _falcon->Item->setProperty("state", "Alive");

    // Create Enemies
    _enemyTanks[0] = new BasicEnemyTank(this, BCGlobal::Backward, 128, 0);
    connect(_enemyTanks[0], SIGNAL(IAmDestroyed()), SLOT(EnemyDestroyed()));
    _enemyTanks[1] = new BasicEnemyTank(this, BCGlobal::Backward, 416 - 32, 0);
    connect(_enemyTanks[1], SIGNAL(IAmDestroyed()), SLOT(EnemyDestroyed()));
    _enemyTanks[2] = new BasicEnemyTank(this, BCGlobal::Backward, 0, 0);
    connect(_enemyTanks[2], SIGNAL(IAmDestroyed()), SLOT(EnemyDestroyed()));

    Items.append(_enemyTanks[0]);
    Items.append(_enemyTanks[1]);
    Items.append(_enemyTanks[2]);

    LoadLevel(levelMAPPath);
}


void GameBoard::LoadLevel(QString levelMAPPath)
{
    QFile inputFile(levelMAPPath);

    if(inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        int lineCount = 0;

        while(!in.atEnd())
        {
            QString line = in.readLine();
            QStringList lineSplitted = line.split(' ');
            BCItem* obstacle;

            for(int i = 0; i < lineSplitted.length(); i++)
            {
                obstacle = nullptr;

                if(lineSplitted[i] == "1")
                { // Brick
                    obstacle = new Brick(this);
                    obstacle->SetPosition(i * 8, lineCount * 8);
                }
                else if (lineSplitted[i] == "2")
                { // Concrete
                    obstacle = new Concrete(this);
                    obstacle->SetPosition(i * 8, lineCount * 8);
                }
                else
                {

                }

                if (obstacle != nullptr)
                    Items.append(obstacle);
            }

            lineCount++;
        }

        inputFile.close();
    }
}

void GameBoard::StopGame()
{
    for (int i = 0; i < 3; i++)
        _enemyTanks[i]->Stop();

    _playerTank->IsAlive = false;
}

void GameBoard::keyPressEvent(QKeyEvent *event)
{
    BCGlobal::MoveDirection direction = _playerTank->Direction;

    if(_playerTank->IsAlive)
    {
        if (event->key() == Qt::Key_Left)
        {
            direction = BCGlobal::Left;
            _playerTank->Direction = direction;
            _playerTank->Move(direction);
            _playerTank->Item->setProperty("state", "Left");
        }
        else if (event->key() == Qt::Key_Right)
        {
            direction = BCGlobal::Right;
            _playerTank->Direction = direction;
            _playerTank->Move(direction);
            _playerTank->Item->setProperty("state", "Right");
        }
        else if (event->key() == Qt::Key_Up)
        {
            direction = BCGlobal::Forward;
            _playerTank->Direction = direction;
            _playerTank->Move(direction);
            _playerTank->Item->setProperty("state", "Forward");
        }
        else if (event->key() == Qt::Key_Down) {
            direction = BCGlobal::Backward;
            _playerTank->Direction = direction;
            _playerTank->Move(direction);
            _playerTank->Item->setProperty("state", "Backward");
        }
        else if (event->key() == Qt::Key_Space)
        {
            _playerTank->Fire();
        }
    }
    update();
}

void GameBoard::Explode()
{
    //qDebug("Enemy Says: Oh I am DEAD");
    if (NumberOfEnemyTanks > 0)
    {
        _enemyTanks[0]->ReSpawn();
        NumberOfEnemyTanks--;
    }
}


void GameBoard::EnemyDestroyed()
{
    NumberOfEnemyTanks--;
    rootObject()->setProperty("enemiesLeft", QVariant("Enemies Left: " + QString::number(NumberOfEnemyTanks)));

    if(NumberOfEnemyTanks == 0)
    { // Win
        //qDebug() << "YEAAAAH I WIN";
        rootObject()->setProperty("winLose", QVariant("You WIN"));
        StopGame();
    }
    else
    {
        BaseTank* tank = qobject_cast<EnemyTank *>(QObject::sender());
        tank->ReSpawn();
        //qDebug() << "An Enemy is Killed: Remaining Tanks = " << NumberOfEnemyTanks;
    }
}


void GameBoard::PlayerDestroyed()
{
    RemainingLives--;
    rootObject()->setProperty("livesLeft", QVariant("Lives Left: " + QString::number(RemainingLives)));

    if (RemainingLives == 0)
    { // Lose
        rootObject()->setProperty("winLose", QVariant("You Lose"));
        StopGame();
        //qDebug() << "You Lose.. You died 4 times";
    }
    else
    {
        BaseTank* tank = qobject_cast<PlayerTank *>(QObject::sender());
        tank->ReSpawn();
        //qDebug() << "You have been hit: Remaining Lifes = " << RemainingLives;
    }
}


void GameBoard::FalconDestroyed()
{
    rootObject()->setProperty("winLose", QVariant("You Lose"));
    _falcon->Item->setProperty("state", "Dead");
    StopGame();
    //qDebug() << "You Lose.. Falcon is DEAD";
}
