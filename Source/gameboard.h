#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include "gameboard.h"
#include <QKeyEvent>
#include <QQuickView>
#include <QQuickItem>
#include "player.h"
#include "enemy.h"

class GameBoard : public QQuickView
{
    Q_OBJECT

public:
    GameBoard(QString levelMAPPath);
    ~GameBoard();

    void Initialize(QString levelMAPPath);

public:
    int BoardSize;
    int CellSize;
    QList<BCItem *> Items;

private:
    EnemyTank* _enemyTanks[3];
    PlayerTank* _playerTank;
    Falcon* _falcon;

    int NumberOfEnemyTanks;
    int RemainingLives;

private:
    void LoadLevel(QString levelMAPPath);
    void StopGame();

    // QWindow interface
protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void Explode();
    void EnemyDestroyed();
    void PlayerDestroyed();
    void FalconDestroyed();
};

#endif // GAMEBOARD_H
