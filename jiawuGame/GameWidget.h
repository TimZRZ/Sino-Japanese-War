#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
#include <QLabel>
#include <warship.h>
#include <random>
#include <QThread>
#include <QMessageBox>
#include "vector"
#include "QString"
#include "fstream"
#include "QtGui"
#include <qfile.h>
#include <qtextstream.h>
#include <qtextcodec.h>
#include <tuple>
#include <QMatrix>

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    warship testship;
    warship testship2;
    int clickPosRow, clickPosCol; //鼠标位置
    int firePosRow, firePosCol; //开火位置
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent();
    void setWarshipList(vector<int> userSelect);
    void setInitialPosition();
    vector<int> setEnemyCombination();
    void setEnemyWarshipList(vector<int> Parameters);
    void setEnemyInitialPosition();
    bool judgeCover(int x, int y);
    vector<tuple<int,int,int> > GenerateOpponentInfo(vector<warship> warshipList);
    vector<vector<int> > GenerateSingleInfluenceMap(warship TargetWarship);
    vector<vector<int> > GenerateOverallInfluenceMap(vector<warship> targetWarshipList);
    bool inAttackRange(warship attacker,warship receiver);
    bool inDirectAttackRange(int x,int y,warship attacker,warship receiver);
    bool inReachRange(int x, int y, warship myship);
    bool JudgeCollision(int x,int y,warship myship);
    bool testWin(vector<warship> shipList);
    void SetComputerStage();
    void ConcentrateMode();
    void RandomMode();
    void ComputerMove();
    int judgeSameShip(warship ship, vector<warship> shipList);
    void setSightRange();

    int gameRole = 0;

    QLabel *gameInfo;

    QLabel *myName;
    QLabel *power1;
    QLabel *power2;
    vector<int> userSelect;
    vector<warship> warshipList;
    vector<warship> EnemyWarshipList;
    vector<QLabel *> warshipBlood;
    vector<QLabel *> enemyWarshipBlood;
    QString countryID;
    QString enemyID;
    int concentrateControl = 0;
    int shipNumber;
    int winOrNot = 0;
    friend class selectModel;


private:
    vector<vector<int>> sightRange;
    int country = 0;
signals:

public slots:

};

#endif // GAMEWIDGET_H
