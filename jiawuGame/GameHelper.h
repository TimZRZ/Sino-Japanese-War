#ifndef GAMEHELPER_H
#define GAMEHELPER_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QLabel>

class GameHelper : public QWidget
{
    Q_OBJECT
public:
    explicit GameHelper(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    QPushButton *backToMenu;
    QPushButton *nextPage;
    QLabel *gameHelp;

signals:

public slots:
        void returnSlot();
};

#endif // GAMEHELPER_H
