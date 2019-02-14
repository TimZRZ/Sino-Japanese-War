#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QLabel>
#include <QSignalMapper>
#include "warshipButtonWidget.h"

class libraryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit libraryWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    warshipButtonWidget *warshipButtons;
    QPushButton *backToMenu;
    QLabel *info;

private:
    QSignalMapper *signalMapper;

signals:

private slots:

public slots:
    void setInfoBoard(QString warshipName);
    void returnSlot();
};

#endif // LIBRARYWIDGET_H
