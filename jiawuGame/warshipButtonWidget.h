#ifndef WARSHIPBUTTONWIDGET_H
#define WARSHIPBUTTONWIDGET_H
#include <QFile> //Excel操作
#include <QObject>
#include <QString>
#include <QDir>
#include <QTextStream>
#include <QApplication>
#include <QHBoxLayout>
#include <QToolButton>
#include <QStringListModel>
#include <QListView>
#include <QGroupBox>
#include <QToolBox>
#include <QSize>
#include <iostream>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsView> //绘制游戏板块
#include <QGraphicsScene> //绘制游戏板块
#include <QWidget>
#include "warship.h"

class warshipButtonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit warshipButtonWidget(QWidget *parent = 0);
    QString setCSVPath(QString CSVName);
    QStringList setCSVList(QString CSVName);
    map<QString,warship> setWarshipMap(QStringList CSVList);
    map<QString,warship> outputWarshipMap();
    QToolButton* setWarshipButton(QString buttonText, QString buttonIcon,int buttonHeight,int buttonWidth,int iconHeight);
    map<QString,QToolButton*> setWarshipButtonMap(map<QString,warship> warshipMap,int buttonHeight,int buttonWidth,int iconHeight);
    QStringList warshipInfo;
    map<QString,warship> warshipMap;
    map<QString,QToolButton*> warshipButtonMap;
    QVBoxLayout* Qing;
    QVBoxLayout* Japan;

signals:

public slots:
};

#endif // WARSHIPBUTTONWIDGET_H
