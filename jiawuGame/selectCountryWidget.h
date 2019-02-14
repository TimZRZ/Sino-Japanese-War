#ifndef SELECTCOUNTRYWIDGET_H
#define SELECTCOUNTRYWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QPainter>
#include "GameWidget.h"
#include "selectmodel.h"

class selectCountryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit selectCountryWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    GameWidget *enterGame;
    selectModel *enterselect;

private:
    QLabel *selectCountryTitle;
    QPushButton *backToMenu;
    QToolButton *Selectgamemodel1;
    QToolButton *Selectgamemodel2;
    QToolButton *Qing;
    QToolButton *Japan;
    QToolButton *Start;
    QToolButton *info;
    //int model = 0;
    int Country = 0;

signals:

public slots:
    void returnSlot();
    void gameStartSlot();
//    void selectModel1Slot();
//    void selectModel2Slot();
    void selectCountry1Slot();
    void selectCountry2Slot();

};

#endif // SELECTCOUNTRYWIDGET_H

