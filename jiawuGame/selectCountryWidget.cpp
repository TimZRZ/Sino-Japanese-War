#include "selectCountryWidget.h"


selectCountryWidget::selectCountryWidget(QWidget *parent) : QWidget(parent)
{
    this->resize(900,600);
    this->setMaximumSize(900,600);
    this->setWindowIcon(QIcon(":/images/images/others/windowIcon.jpg"));
    this->setWindowTitle("甲午风云");

    //设置标题
    QFont titleFont;
    titleFont.setFamily("PMingLiU");
    titleFont.setBold(true);
    titleFont.setPixelSize(50);
    selectCountryTitle = new QLabel(this);
    selectCountryTitle->setText("选择势力");
    selectCountryTitle->setFont(titleFont);
    selectCountryTitle->setStyleSheet("color:white;background-color:black");
    selectCountryTitle->setGeometry(QRect(350,20,200,100));

    backToMenu = new QPushButton(this);
    backToMenu->setText("返回主菜单");
    backToMenu->setGeometry(QRect(750,500,100,50));
    connect(backToMenu,SIGNAL(clicked()),this,SLOT(returnSlot()));

    //设置选择大清北洋水师的按钮
    Qing = new QToolButton(this);
    Qing->setStyleSheet("QToolButton{border-image: url(:/images/images/others/QingFlag.jpg);}"
                        "QToolButton:hover{border-image: url(:/images/images/others/QingFlag.jpg);}");
    Qing->setGeometry(QRect(100,200,300,210));
    Qing->setAutoRaise(false);
    connect(Qing,SIGNAL(clicked()),this,SLOT(selectCountry1Slot()));

    //设置选择日本联合舰队的按钮
    Japan = new QToolButton(this);
    //Qing->setIcon(QPixmap(":/images/images/buttons/startButton.png"));
    //Qing->setIconSize(QSize(250,250));
    Japan->setStyleSheet("QToolButton{border-image: url(:/images/images/others/JapanFlag.jpg);}"
                        "QToolButton:hover{border-image: url(:/images/images/others/JapanFlag.jpg);}");
    Japan->setGeometry(QRect(500,200,300,210));
    connect(Japan,SIGNAL(clicked()),this,SLOT(selectCountry2Slot()));


    /* 显示选择国家的信息 */
    info = new QToolButton(this);
    info->setText("当前选择国家：清");
    info->setGeometry(QRect(400,130,150,50));

    /* 设置开始游戏的按钮 */
    Start = new QToolButton(this);
    Start->setText("确定");
    Start->setGeometry(QRect(400,500,100,50));
    connect(Start,SIGNAL(clicked()),this,SLOT(gameStartSlot()));
}

void selectCountryWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/images/images/others/selectCountryIMG.jpg"));
}

void selectCountryWidget::returnSlot()
{
    delete this;
}

void selectCountryWidget::gameStartSlot()
{
    if (Country ==0){

        QDir dir;
        QString currentPath = dir.currentPath();
        QString path = currentPath.section('/',0,-2);
        QString fileName = path+"/jiawuGame/files/userselect1.txt";
        QFile file(fileName);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream out(&file);

        out << 0;
        out.flush();
        file.close();

        enterselect = new selectModel();
        enterselect->show();

    }else {

        QDir dir;
        QString currentPath = dir.currentPath();
        QString path = currentPath.section('/',0,-2);
        QString fileName = path+"/jiawuGame/files/userselect1.txt";
        QFile file(fileName);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream out(&file);

        out << 1;
        out.flush();
        file.close();

        enterselect = new selectModel();
        enterselect->show();
    }
}


void selectCountryWidget::selectCountry1Slot()
{
    Country = 0;
    info->setText("当前选择国家：清");

}

void selectCountryWidget::selectCountry2Slot()
{
    Country = 1;
    info->setText("当前选择国家：日本");

}
