#include "libraryWidget.h"

libraryWidget::libraryWidget(QWidget *parent) : QWidget(parent)
{
    this->resize(900,600);
    this->setMaximumSize(900,600);
    this->setWindowIcon(QIcon(":/images/images/others/windowIcon.jpg"));
    this->setWindowTitle("甲午风云");

    info = new QLabel(this);
    info->setText("");
    info->setGeometry(QRect(750,50,100,50));

    warshipButtons = new warshipButtonWidget(this);
    QGridLayout* Layout = new QGridLayout;


    backToMenu = new QPushButton(this);
    backToMenu->setText("返回主菜单");
    backToMenu->setGeometry(QRect(750,500,100,50));

    //设置按钮链接
    connect(backToMenu,SIGNAL(clicked()),this,SLOT(returnSlot()));
    signalMapper = new QSignalMapper(this);
    for (map<QString,QToolButton*>::iterator i = (warshipButtons->warshipButtonMap).begin();i != (warshipButtons->warshipButtonMap).end();i++) {
        connect(i->second,SIGNAL(clicked()),signalMapper,SLOT(map()));
        signalMapper->setMapping(i->second,i->first);
        connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(setInfoBoard(QString)));
    }

    //设置Layout
    Layout->addLayout(warshipButtons->Qing,0,0);
    Layout->addLayout(warshipButtons->Japan,1,0);
    this->setLayout(Layout);
}

void libraryWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/images/images/others/library.jpg"));
}

void libraryWidget::returnSlot() {
    delete this;
}

void libraryWidget::setInfoBoard(QString warshipName)
{
    warship warshipOBJ = warshipButtons->warshipMap[warshipName];
    info->setText(warshipOBJ.shipName);
}
