#include "MainMenu.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    this->resize(900,600);
    this->setMaximumSize(900,600);
    this->setWindowIcon(QIcon(":/images/images/others/windowIcon.jpg"));
    this->setWindowTitle("甲午风云");
    QPalette backgroundIMG;
    backgroundIMG.setBrush(QPalette::Background,QBrush(QPixmap(":/images/images/others/mainMenuIMG.jpg")));
    this->setPalette(backgroundIMG);

    //设置标题
    QFont titleFont;
    titleFont.setFamily("Lisu");
    titleFont.setBold(true);
    titleFont.setPixelSize(100);
    gameTitle = new QLabel(this);
    gameTitle->setText("甲午风云");
    gameTitle->setFont(titleFont);
    gameTitle->setStyleSheet("color:Firebrick;background-color:Peru");
    gameTitle->setGeometry(QRect(245,0,410,100));

    //设置"开始游戏"按钮
    startButton = new QPushButton(this);
    startButton->setIcon(QIcon(":/images/images/buttons/startButton.png"));
    startButton->setIconSize(QSize(200,80));
    startButton->setGeometry(QRect(350,150,200,80));
    startButton->setFlat(true);

    //设置"甲午图鉴"按钮
    libraryButton = new QPushButton(this);
    libraryButton->setIcon(QIcon(":/images/images/buttons/libraryButton.png"));
    libraryButton->setIconSize(QSize(200,80));
    libraryButton->setGeometry(QRect(350,250,200,80));
    libraryButton->setFlat(true);

    //设置"游戏帮助"按钮
    helpButton = new QPushButton(this);
    helpButton->setIcon(QIcon(":/images/images/buttons/helpButton.png"));
    helpButton->setIconSize(QSize(200,80));
    helpButton->setGeometry(QRect(350,350,200,80));
    helpButton->setFlat(true);

    //设置"退出游戏"按钮
    exitButton = new QPushButton(this);
    exitButton->setIcon(QIcon(":/images/images/buttons/exitButton.png"));
    exitButton->setIconSize(QSize(200,80));
    exitButton->setGeometry(QRect(350,450,200,80));
    exitButton->setFlat(true);

    //设置每个按钮的信息和槽
    connect(startButton,SIGNAL(clicked()),this,SLOT(startSlot()));
    connect(libraryButton,SIGNAL(clicked()),this,SLOT(librarySlot()));
    connect(helpButton,SIGNAL(clicked()),this,SLOT(helpSlot()));
    connect(exitButton,SIGNAL(clicked()),this,SLOT(exitSlot()));
}

void MainMenu::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/images/images/others/mainMenuIMG.jpg"));
}

void MainMenu::startSlot()
{
    game = new selectCountryWidget(this);
    game->show();
}

void MainMenu::librarySlot()
{
    library = new libraryWidget(this);
    library->show();
}

void MainMenu::helpSlot()
{
    helper = new GameHelper(this);
    helper->show();
}

void MainMenu::exitSlot()
{
    if(QMessageBox::question(this,"退出游戏","是否退出当前游戏",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
        delete this;
        exit(0);
    }
}

