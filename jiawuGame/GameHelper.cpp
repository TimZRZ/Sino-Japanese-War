#include "GameHelper.h"

GameHelper::GameHelper(QWidget *parent) : QWidget(parent)
{
    this->resize(900,600);
    this->setMaximumSize(900,600);
    this->setWindowIcon(QIcon(":/images/images/others/windowIcon.jpg"));
    this->setWindowTitle("甲午风云");

    backToMenu = new QPushButton(this);
    backToMenu->setText("返回主菜单");
    backToMenu->setGeometry(QRect(770,500,100,50));
    connect(backToMenu,SIGNAL(clicked()),this,SLOT(returnSlot()));

    QFont helpFont;
    helpFont.setFamily("Kaisu");
    helpFont.setBold(true);
    helpFont.setPixelSize(16);
    gameHelp = new QLabel(this);
    gameHelp->setText("游戏背景：\n1894年，中日甲午海战爆发，清政府的北洋水师与日本联合舰队在黄海海域进行了激烈交\n"
                      "战。\n\n模式选择：\n玩家可选择【日本舰队】或【清朝舰队】参与战争。\n两支舰队各有5种属性不同的舰船。\n"
                      "每支舰队总人口值为20，玩家可自行安排每种舰船的上阵数量。\n\n游戏玩法：\n"
                      "初始状态，玩家与敌方所选战舰一字排开，玩家可跟据每艘战舰的可移动距离（蓝色）依次\n"
                      "移动舰船，每移动一次舰船，该舰船可粉色区域所示的攻击范围内进行一次攻击。攻击一次\n"
                      "后可移动下一艘战舰。每艘舰船的移动和攻击均可使用右键跳过。当玩家部署完成所有舰船\n"
                      "的移动和攻击后，敌方(计算机)进行舰船移动和攻击，交互进行游戏。界面右侧将实时显示\n"
                      "玩家与敌方每艘战舰生命值，当生命值降为零时，战舰沉没。当一方所有战舰沉没，该方失\n败，战争结束。\n");
    gameHelp->setFont(helpFont);
    gameHelp->setStyleSheet("color:Black");
    gameHelp->setGeometry(QRect(70,9,720,550));

}

void GameHelper::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/images/images/others/helper.jpg"));
}

void GameHelper::returnSlot() {
    delete this;
}


