#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <GameWidget.h>
#include <QMessageBox>
#include "selectCountryWidget.h"
#include "libraryWidget.h"
#include "GameHelper.h"

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
private:
    QPushButton *startButton;
    QPushButton *libraryButton;
    QPushButton *helpButton;
    QPushButton *exitButton;
    selectCountryWidget *game;
    libraryWidget *library;
    GameHelper *helper;
    QLabel *gameTitle;
signals:

public slots:
    void startSlot();
    void librarySlot();
    void helpSlot();
    void exitSlot();
};

#endif // MAINMENU_H
