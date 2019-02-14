#include "selectmodel.h"

selectModel::selectModel(QWidget *parent) : QWidget(parent)
{


    QDir dir;
    QString currentPath = dir.currentPath();
    QString path = currentPath.section('/',0,-2);
    QString fileName = path+"/jiawuGame/files/userselect1.txt";
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
         return;
    }
    QTextStream in(&file);
        //cout << "i=" << i <<endl;
        QString count1 = in.read(1);
        if (count1 == "0"){
            country = 0;
        }else{country = 1;}
        cout << country;
    file.close();



    if (country == 0){
    /* 设置界面 */
    this->resize(900,600);
    this->setMaximumSize(900,600);
    this->setWindowIcon(QIcon(":/images/images/others/windowIcon.jpg"));
    this->setWindowTitle("甲午风云:清");

    //设置标题
    QFont titleFont;
    titleFont.setFamily("PMingLiU");
    titleFont.setBold(true);
    titleFont.setPixelSize(50);
    selectModelTitle = new QLabel(this);
    selectModelTitle->setText("创建舰队");
    selectModelTitle->setFont(titleFont);
    selectModelTitle->setStyleSheet("color:white;background-color:black");
    selectModelTitle->setGeometry(QRect(347,20,206,100));

    /* 设置返回键 */
    backToMenu = new QPushButton(this);
    backToMenu->setText("重新选择势力和模式");
    backToMenu->setGeometry(QRect(700,500,200,50));
    connect(backToMenu,SIGNAL(clicked()),this,SLOT(returnSlot()));

    /* 设置船类按钮 */
    /* 木壳快船 */
    smship = new QPushButton(this);
    smship->setText("木壳快船(2容量)");
    smship->setGeometry(QRect(250,400,150,50));
    smmenu = new QMenu;
    smac1 = new QAction(smmenu);
    smac2 = new QAction(smmenu);
    smac3 = new QAction(smmenu);
    smmenu->addAction(smac1);
    smmenu->addAction(smac2);
    smmenu->addAction(smac3);
    smship->setMenu(smmenu);
    smac1->setText(tr("广甲1"));
    smac2->setText(tr("广甲2"));
    smac3->setText(tr("广甲3"));
    connect(smac1,SIGNAL(triggered(bool)),this,SLOT(addsm1shipSlot()));
    connect(smac2,SIGNAL(triggered(bool)),this,SLOT(addsm2shipSlot()));
    connect(smac3,SIGNAL(triggered(bool)),this,SLOT(addsm3shipSlot()));

     /* 钢壳快船 */
    sship = new QPushButton(this);
    sship->setText("钢壳快船(2容量)");
    sship->setGeometry(QRect(100,400,150,50));
    smenu = new QMenu;
    sac1 = new QAction(smenu);
    sac2 = new QAction(smenu);
    sac3 = new QAction(smenu);
    smenu->addAction(sac1);
    smenu->addAction(sac2);
    smenu->addAction(sac3);
    sship->setMenu(smenu);
    sac1->setText(tr("超勇"));
    sac2->setText(tr("扬威"));
    sac3->setText(tr("广丙"));
    connect(sac1,SIGNAL(triggered(bool)),this,SLOT(adds1shipSlot()));
    connect(sac2,SIGNAL(triggered(bool)),this,SLOT(adds2shipSlot()));
    connect(sac3,SIGNAL(triggered(bool)),this,SLOT(adds3shipSlot()));

     /* 穹甲巡洋舰 */
    mnship = new QPushButton(this);
    mnship->setText("穹甲巡洋舰(5容量)");
    mnship->setGeometry(QRect(550,400,150,50));
    mnmenu = new QMenu;
    mnac1 = new QAction(mnmenu);
    mnac2 = new QAction(mnmenu);
    mnac3 = new QAction(mnmenu);
    mnmenu->addAction(mnac1);
    mnmenu->addAction(mnac2);
    mnmenu->addAction(mnac3);
    mnship->setMenu(mnmenu);
    mnac1->setText(tr("致远"));
    mnac2->setText(tr("济远"));
    mnac3->setText(tr("靖远"));
    connect(mnac1,SIGNAL(triggered(bool)),this,SLOT(addmn1shipSlot()));
    connect(mnac2,SIGNAL(triggered(bool)),this,SLOT(addmn2shipSlot()));
    connect(mnac3,SIGNAL(triggered(bool)),this,SLOT(addmn3shipSlot()));

     /* 装甲巡洋舰 */
    mship = new QPushButton(this);
    mship->setText("装甲巡洋舰(5容量)");
    mship->setGeometry(QRect(400,400,150,50));
    mmenu = new QMenu;
    mac1 = new QAction(mmenu);
    mac2 = new QAction(mmenu);
    mac3 = new QAction(mmenu);
    mmenu->addAction(mac1);
    mmenu->addAction(mac2);
    mmenu->addAction(mac3);
    mship->setMenu(mmenu);
    mac1->setText(tr("经远"));
    mac2->setText(tr("来远"));
    mac3->setText(tr("威远"));
    connect(mac1,SIGNAL(triggered(bool)),this,SLOT(addm1shipSlot()));
    connect(mac2,SIGNAL(triggered(bool)),this,SLOT(addm2shipSlot()));
    connect(mac3,SIGNAL(triggered(bool)),this,SLOT(addm3shipSlot()));

     /* 铁甲舰 */
    lship = new QPushButton(this);
    lship->setText("铁甲舰(10容量)");
    lship->setGeometry(QRect(700,400,150,50));
    lmenu = new QMenu;
    lac1 = new QAction(lmenu);
    lac2 = new QAction(lmenu);
    lac3 = new QAction(lmenu);
    lmenu->addAction(lac1);
    lmenu->addAction(lac2);
    lmenu->addAction(lac3);
    lship->setMenu(lmenu);
    lac1->setText(tr("定远"));
    lac2->setText(tr("镇远"));
    lac3->setText(tr("平远"));
    connect(lac1,SIGNAL(triggered(bool)),this,SLOT(addl1shipSlot()));
    connect(lac2,SIGNAL(triggered(bool)),this,SLOT(addl2shipSlot()));
    connect(lac3,SIGNAL(triggered(bool)),this,SLOT(addl3shipSlot()));

    /* 设置输出按钮 */
    showCredit = new QToolButton(this);
    showCredit->setText("舰队容量：0/20");
    showCredit->setGeometry(QRect(350,350,200,50));

    /* 显示已选择的舰队 */
    showFleetTitle = new QToolButton(this);
    showFleetTitle->setText("我的舰队");
    showFleetTitle->setStyleSheet("color:white;background-color:black");
    showFleetTitle->setGeometry(QRect(400,150,100,50));

    arrowl = new QLabel(this);
    arrowl->setGeometry(QRect(350,150,50,50));
    arrow = new QPixmap;
    arrow->load(":/images/images/warshipsInGame/arrow.jpeg");
    arrowl->setPixmap(*arrow);
    arrowl->setScaledContents(true);

    showFleet = new QToolButton(this);
    showFleet->setText("铁甲舰：0艘； 穹甲巡洋舰：0艘； 装甲巡洋舰：0艘； 木壳快船：0艘； 钢壳快船： 0艘");
    showFleet->setGeometry(QRect(0,250,600,50));

    /* 显示已选择的舰队的图片 */
    fleetlable = new QLabel(this);
    fleetlable->setGeometry(QRect(0,0,300,250));
    fleetlable->setText("This is a lable");
    background = new QPixmap;
    background->load(":/images/images/warshipsInGame/timg-13.jpeg");
    fleetlable->setPixmap(*background);

    /* 设置清除键 */
    clearAll = new QToolButton(this);
    clearAll->setText("重新编排舰队");
    clearAll->setGeometry(QRect(550,500,100,50));
    connect(clearAll,SIGNAL(clicked()),this,SLOT(clearAllSlot()));

    /* 设置开始游戏键 */
    Start = new QToolButton(this);
    Start->setText("开始游戏");
    Start->setGeometry(QRect(400,500,100,50));
    connect(Start,SIGNAL(clicked()),this,SLOT(StartFleetGameSlot()));}

    /* 设置日本的选择舰队界面 */
    else{
        /* 设置界面 */
        this->resize(900,600);
        this->setMaximumSize(900,600);
        this->setWindowIcon(QIcon(":/images/images/others/windowIcon.jpg"));
        this->setWindowTitle("甲午风云:日本");

        strship = "铁甲舰：0艘； 防护巡洋舰：0艘； 装甲巡洋舰：0艘； 辅助巡洋舰：0艘； 炮舰： 0艘";

        //设置标题
        QFont titleFont;
        titleFont.setFamily("PMingLiU");
        titleFont.setBold(true);
        titleFont.setPixelSize(50);
        selectModelTitle = new QLabel(this);
        selectModelTitle->setText("创建舰队");
        selectModelTitle->setFont(titleFont);
        selectModelTitle->setStyleSheet("color:white;background-color:black");
        selectModelTitle->setGeometry(QRect(347,20,206,100));

        /* 设置返回键 */
        backToMenu = new QPushButton(this);
        backToMenu->setText("重新选择势力");
        backToMenu->setGeometry(QRect(700,500,200,50));
        connect(backToMenu,SIGNAL(clicked()),this,SLOT(returnSlot()));

        /* 设置船类按钮 */
        /* 辅助巡洋舰 */
        smship = new QPushButton(this);
        smship->setText("辅助巡洋舰(2容量)");
        smship->setGeometry(QRect(250,400,150,50));
        smmenu = new QMenu;
        smac1 = new QAction(smmenu);
        smac2 = new QAction(smmenu);
        smac3 = new QAction(smmenu);
        smmenu->addAction(smac1);
        smmenu->addAction(smac2);
        smmenu->addAction(smac3);
        smship->setMenu(smmenu);
        smac1->setText(tr("西京丸1"));
        smac2->setText(tr("西京丸2"));
        smac3->setText(tr("西京丸3"));
        connect(smac1,SIGNAL(triggered(bool)),this,SLOT(addsm1shipSlotr()));
        connect(smac2,SIGNAL(triggered(bool)),this,SLOT(addsm2shipSlotr()));
        connect(smac3,SIGNAL(triggered(bool)),this,SLOT(addsm3shipSlotr()));

         /* 炮舰 */
        sship = new QPushButton(this);
        sship->setText("炮舰(2容量)");
        sship->setGeometry(QRect(100,400,150,50));
        smenu = new QMenu;
        sac1 = new QAction(smenu);
        sac2 = new QAction(smenu);
        //sac3 = new QAction(smenu);
        smenu->addAction(sac1);
        smenu->addAction(sac2);
        //smenu->addAction(sac3);
        sship->setMenu(smenu);
        sac1->setText(tr("赤城"));
        sac2->setText(tr("秋津洲"));
        //sac3->setText(tr("广丙"));
        connect(sac1,SIGNAL(triggered(bool)),this,SLOT(adds1shipSlotr()));
        connect(sac2,SIGNAL(triggered(bool)),this,SLOT(adds2shipSlotr()));
        //connect(sac3,SIGNAL(triggered(bool)),this,SLOT(adds3shipSlotr()));

         /* 防护巡洋舰 */
        mnship = new QPushButton(this);
        mnship->setText("防护巡洋舰(5容量)");
        mnship->setGeometry(QRect(550,400,150,50));
        mnmenu = new QMenu;
        mnac1 = new QAction(mnmenu);
        mnac2 = new QAction(mnmenu);
        mnac3 = new QAction(mnmenu);
        mnmenu->addAction(mnac1);
        mnmenu->addAction(mnac2);
        mnmenu->addAction(mnac3);
        mnship->setMenu(mnmenu);
        mnac1->setText(tr("松岛"));
        mnac2->setText(tr("严岛"));
        mnac3->setText(tr("桥立"));
        connect(mnac1,SIGNAL(triggered(bool)),this,SLOT(addmn1shipSlotr()));
        connect(mnac2,SIGNAL(triggered(bool)),this,SLOT(addmn2shipSlotr()));
        connect(mnac3,SIGNAL(triggered(bool)),this,SLOT(addmn3shipSlotr()));

         /* 装甲巡洋舰 */
        mship = new QPushButton(this);
        mship->setText("装甲巡洋舰(5容量)");
        mship->setGeometry(QRect(400,400,150,50));
        mmenu = new QMenu;
        mac1 = new QAction(mmenu);
        mac2 = new QAction(mmenu);
        mac3 = new QAction(mmenu);
        mmenu->addAction(mac1);
        mmenu->addAction(mac2);
        mmenu->addAction(mac3);
        mship->setMenu(mmenu);
        mac1->setText(tr("千代田"));
        mac2->setText(tr("浪速"));
        mac3->setText(tr("高千穗"));
        connect(mac1,SIGNAL(triggered(bool)),this,SLOT(addm1shipSlotr()));
        connect(mac2,SIGNAL(triggered(bool)),this,SLOT(addm2shipSlotr()));
        connect(mac3,SIGNAL(triggered(bool)),this,SLOT(addm3shipSlotr()));

         /* 铁甲舰 */
        lship = new QPushButton(this);
        lship->setText("铁甲舰(10容量)");
        lship->setGeometry(QRect(700,400,150,50));
        lmenu = new QMenu;
        lac1 = new QAction(lmenu);
        lac2 = new QAction(lmenu);
        lac3 = new QAction(lmenu);
        lmenu->addAction(lac1);
        lmenu->addAction(lac2);
        lmenu->addAction(lac3);
        lship->setMenu(lmenu);
        lac1->setText(tr("比睿"));
        lac2->setText(tr("扶桑"));
        lac3->setText(tr("吉野"));
        connect(lac1,SIGNAL(triggered(bool)),this,SLOT(addl1shipSlotr()));
        connect(lac2,SIGNAL(triggered(bool)),this,SLOT(addl2shipSlotr()));
        connect(lac3,SIGNAL(triggered(bool)),this,SLOT(addl3shipSlotr()));

        /* 设置输出按钮 */
        showCredit = new QToolButton(this);
        showCredit->setText("舰队容量：0/20");
        showCredit->setGeometry(QRect(350,350,200,50));

        /* 显示已选择的舰队 */
        showFleetTitle = new QToolButton(this);
        showFleetTitle->setText("我的舰队");
        showFleetTitle->setStyleSheet("color:white;background-color:black");
        showFleetTitle->setGeometry(QRect(400,150,100,50));

        arrowl = new QLabel(this);
        arrowl->setGeometry(QRect(350,150,50,50));
        arrow = new QPixmap;
        arrow->load(":/images/images/warshipsInGame/arrow.jpeg");
        arrowl->setPixmap(*arrow);
        arrowl->setScaledContents(true);

        showFleet = new QToolButton(this);
        showFleet->setText("铁甲舰：0艘； 防护巡洋舰：0艘； 装甲巡洋舰：0艘； 辅助巡洋舰：0艘； 炮舰： 0艘");
        showFleet->setGeometry(QRect(0,250,600,50));

        /* 显示已选择的舰队的图片 */
        fleetlable = new QLabel(this);
        fleetlable->setGeometry(QRect(0,0,300,250));
        fleetlable->setText("This is a lable");
        background = new QPixmap;
        background->load(":/images/images/warshipsInGame/timg-13.jpeg");
        fleetlable->setPixmap(*background);

        /* 设置清除键 */
        clearAll = new QToolButton(this);
        clearAll->setText("重新编排舰队");
        clearAll->setGeometry(QRect(550,500,100,50));
        connect(clearAll,SIGNAL(clicked()),this,SLOT(clearAllSlotr()));

        /* 设置开始游戏键 */
        Start = new QToolButton(this);
        Start->setText("开始游戏");
        Start->setGeometry(QRect(400,500,100,50));
        connect(Start,SIGNAL(clicked()),this,SLOT(StartFleetGameSlot()));
    }

}

void selectModel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/images/images/others/selectCountryIMG.jpg"));
}

void selectModel::returnSlot() {
    delete this;
}

void selectModel::adds1shipSlot(){
    total = total + 2;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        csship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(43,1,QString::number(csship));
        showFleet->setText(strship);
        sac1->setText(tr("超勇(已选择)"));
    if (csship == 1){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,40));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/1690374707.jpg");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 2){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,80));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/2ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 3){
            gkkclabel = new QLabel(this);
            gkkclabel->setGeometry(QRect(250,25,25,120));
            gkkc = new QPixmap;
            gkkc->load(":/images/images/warshipsInGame/3ship.png");
            gkkclabel->setPixmap(*gkkc);
            gkkclabel->setScaledContents(true);
            gkkclabel->show();
    }else if (csship == 4){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,160));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/4ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 5){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/5ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 6){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/6ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 7){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/7ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 8){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/8ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 9){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/9ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 10){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/10ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }
    }else{total -= 2;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}

void selectModel::adds2shipSlot(){
    total = total + 2;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        csship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(43,1,QString::number(csship));
        showFleet->setText(strship);
        sac2->setText(tr("扬威(已选择)"));
    if (csship == 1){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,40));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/1690374707.jpg");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 2){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,80));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/2ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 3){
            gkkclabel = new QLabel(this);
            gkkclabel->setGeometry(QRect(250,25,25,120));
            gkkc = new QPixmap;
            gkkc->load(":/images/images/warshipsInGame/3ship.png");
            gkkclabel->setPixmap(*gkkc);
            gkkclabel->setScaledContents(true);
            gkkclabel->show();
    }else if (csship == 4){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,160));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/4ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 5){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/5ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 6){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/6ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 7){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/7ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 8){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/8ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 9){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/9ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 10){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/10ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }
    }else{total -= 2;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}

void selectModel::adds3shipSlot(){
    total = total + 2;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        csship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(43,1,QString::number(csship));
        showFleet->setText(strship);
        sac3->setText(tr("广丙(已选择)"));
    if (csship == 1){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,40));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/1690374707.jpg");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 2){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,80));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/2ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 3){
            gkkclabel = new QLabel(this);
            gkkclabel->setGeometry(QRect(250,25,25,120));
            gkkc = new QPixmap;
            gkkc->load(":/images/images/warshipsInGame/3ship.png");
            gkkclabel->setPixmap(*gkkc);
            gkkclabel->setScaledContents(true);
            gkkclabel->show();
    }else if (csship == 4){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,160));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/4ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 5){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/5ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 6){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/6ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 7){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/7ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 8){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/8ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 9){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/9ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 10){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/10ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }
    }else{total -= 2;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}

void selectModel::addsm1shipSlot(){
    total = total + 2;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        csmship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(33,1,QString::number(csmship));
        showFleet->setText(strship);
        smac1->setText(tr("广甲1(已选择)"));
    if (csmship == 1){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,40));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/1690374707.jpg");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 2){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,80));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/2ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 3){
            gkkclabel = new QLabel(this);
            gkkclabel->setGeometry(QRect(200,25,25,120));
            gkkc = new QPixmap;
            gkkc->load(":/images/images/warshipsInGame/3ship.png");
            gkkclabel->setPixmap(*gkkc);
            gkkclabel->setScaledContents(true);
            gkkclabel->show();
    }else if (csmship == 4){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,160));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/4ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 5){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/5ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 6){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/arshipsInGame/6ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 7){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/7ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 8){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/8ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 9){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/9ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 10){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/10ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }
    }else{total -= 2;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}


void selectModel::addsm2shipSlot(){
    total = total + 2;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        csmship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(33,1,QString::number(csmship));
        showFleet->setText(strship);
        smac2->setText(tr("广甲2(已选择)"));
    if (csmship == 1){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,40));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/1690374707.jpg");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 2){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,80));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/2ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 3){
            gkkclabel = new QLabel(this);
            gkkclabel->setGeometry(QRect(200,25,25,120));
            gkkc = new QPixmap;
            gkkc->load(":/images/images/warshipsInGame/3ship.png");
            gkkclabel->setPixmap(*gkkc);
            gkkclabel->setScaledContents(true);
            gkkclabel->show();
    }else if (csmship == 4){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,160));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/4ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 5){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/5ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 6){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/6ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 7){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/7ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 8){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/8ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 9){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/9ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 10){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/10ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }
    }else{total -= 2;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}


void selectModel::addsm3shipSlot(){
    total = total + 2;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        csmship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(33,1,QString::number(csmship));
        showFleet->setText(strship);
        smac3->setText(tr("广甲3(已选择)"));
    if (csmship == 1){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,40));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/1690374707.jpg");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 2){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,80));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/2ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 3){
            gkkclabel = new QLabel(this);
            gkkclabel->setGeometry(QRect(200,25,25,120));
            gkkc = new QPixmap;
            gkkc->load(":/images/images/warshipsInGame/3ship.png");
            gkkclabel->setPixmap(*gkkc);
            gkkclabel->setScaledContents(true);
            gkkclabel->show();
    }else if (csmship == 4){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,160));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/4ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 5){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/5ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 6){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/6ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 7){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/7ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 8){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/8ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 9){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/9ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 10){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/10ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }
    }else{total -= 2;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}


void selectModel::addm1shipSlot(){
    total = total + 5;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        cmship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(24,1,QString::number(cmship));
        showFleet->setText(strship);
        mac1->setText(tr("经远(已选择)"));

    if (cmship == 1){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);
        gjxyjlabel->show();
    }else if(cmship == 2){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);

        QLabel *gjxyjlabel2 = new QLabel(this);
        gjxyjlabel2->setGeometry(QRect(150,75,50,50));
        gjxyjlabel2->setPixmap(*gjxyj);
        gjxyjlabel2->setScaledContents(true);
        gjxyjlabel->show();
        gjxyjlabel2->show();
    }else if (cmship == 3){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);

        QLabel *gjxyjlabel2 = new QLabel(this);
        gjxyjlabel2->setGeometry(QRect(150,75,50,50));
        gjxyjlabel2->setPixmap(*gjxyj);
        gjxyjlabel2->setScaledContents(true);

        QLabel *gjxyjlabel3 = new QLabel(this);
        gjxyjlabel3->setGeometry(QRect(150,125,50,50));
        gjxyjlabel3->setPixmap(*gjxyj);
        gjxyjlabel3->setScaledContents(true);

        gjxyjlabel->show();
        gjxyjlabel2->show();
        gjxyjlabel3->show();
    }else if (cmship == 4){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);

        QLabel *gjxyjlabel2 = new QLabel(this);
        gjxyjlabel2->setGeometry(QRect(150,75,50,50));
        gjxyjlabel2->setPixmap(*gjxyj);
        gjxyjlabel2->setScaledContents(true);

        QLabel *gjxyjlabel3 = new QLabel(this);
        gjxyjlabel3->setGeometry(QRect(150,125,50,50));
        gjxyjlabel3->setPixmap(*gjxyj);
        gjxyjlabel3->setScaledContents(true);

        QLabel *gjxyjlabel4 = new QLabel(this);
        gjxyjlabel4->setGeometry(QRect(150,175,50,50));
        gjxyjlabel4->setPixmap(*gjxyj);
        gjxyjlabel4->setScaledContents(true);

        gjxyjlabel->show();
        gjxyjlabel2->show();
        gjxyjlabel3->show();
        gjxyjlabel4->show();
    }
    }else{total -= 5;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}

void selectModel::addm2shipSlot(){
    total = total + 5;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        cmship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(24,1,QString::number(cmship));
        showFleet->setText(strship);
        mac2->setText(tr("来远(已选择)"));

    if (cmship == 1){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);
        gjxyjlabel->show();

    }else if(cmship == 2){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);

        QLabel *gjxyjlabel2 = new QLabel(this);
        gjxyjlabel2->setGeometry(QRect(150,75,50,50));
        gjxyjlabel2->setPixmap(*gjxyj);
        gjxyjlabel2->setScaledContents(true);
        gjxyjlabel->show();
        gjxyjlabel2->show();
    }else if (cmship == 3){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);

        QLabel *gjxyjlabel2 = new QLabel(this);
        gjxyjlabel2->setGeometry(QRect(150,75,50,50));
        gjxyjlabel2->setPixmap(*gjxyj);
        gjxyjlabel2->setScaledContents(true);

        QLabel *gjxyjlabel3 = new QLabel(this);
        gjxyjlabel3->setGeometry(QRect(150,125,50,50));
        gjxyjlabel3->setPixmap(*gjxyj);
        gjxyjlabel3->setScaledContents(true);

        gjxyjlabel->show();
        gjxyjlabel2->show();
        gjxyjlabel3->show();
    }else if (cmship == 4){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);

        QLabel *gjxyjlabel2 = new QLabel(this);
        gjxyjlabel2->setGeometry(QRect(150,75,50,50));
        gjxyjlabel2->setPixmap(*gjxyj);
        gjxyjlabel2->setScaledContents(true);

        QLabel *gjxyjlabel3 = new QLabel(this);
        gjxyjlabel3->setGeometry(QRect(150,125,50,50));
        gjxyjlabel3->setPixmap(*gjxyj);
        gjxyjlabel3->setScaledContents(true);

        QLabel *gjxyjlabel4 = new QLabel(this);
        gjxyjlabel4->setGeometry(QRect(150,175,50,50));
        gjxyjlabel4->setPixmap(*gjxyj);
        gjxyjlabel4->setScaledContents(true);

        gjxyjlabel->show();
        gjxyjlabel2->show();
        gjxyjlabel3->show();
        gjxyjlabel4->show();
    }
    }else{total -= 5;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}

void selectModel::addm3shipSlot(){
    total = total + 5;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        cmship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(24,1,QString::number(cmship));
        showFleet->setText(strship);
        mac3->setText(tr("威远(已选择)"));

    if (cmship == 1){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);
        gjxyjlabel->show();
    }else if(cmship == 2){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);

        QLabel *gjxyjlabel2 = new QLabel(this);
        gjxyjlabel2->setGeometry(QRect(150,75,50,50));
        gjxyjlabel2->setPixmap(*gjxyj);
        gjxyjlabel2->setScaledContents(true);
        gjxyjlabel->show();
        gjxyjlabel2->show();
    }else if (cmship == 3){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);

        QLabel *gjxyjlabel2 = new QLabel(this);
        gjxyjlabel2->setGeometry(QRect(150,75,50,50));
        gjxyjlabel2->setPixmap(*gjxyj);
        gjxyjlabel2->setScaledContents(true);

        QLabel *gjxyjlabel3 = new QLabel(this);
        gjxyjlabel3->setGeometry(QRect(150,125,50,50));
        gjxyjlabel3->setPixmap(*gjxyj);
        gjxyjlabel3->setScaledContents(true);

        gjxyjlabel->show();
        gjxyjlabel2->show();
        gjxyjlabel3->show();
    }else if (cmship == 4){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);

        QLabel *gjxyjlabel2 = new QLabel(this);
        gjxyjlabel2->setGeometry(QRect(150,75,50,50));
        gjxyjlabel2->setPixmap(*gjxyj);
        gjxyjlabel2->setScaledContents(true);

        QLabel *gjxyjlabel3 = new QLabel(this);
        gjxyjlabel3->setGeometry(QRect(150,125,50,50));
        gjxyjlabel3->setPixmap(*gjxyj);
        gjxyjlabel3->setScaledContents(true);

        QLabel *gjxyjlabel4 = new QLabel(this);
        gjxyjlabel4->setGeometry(QRect(150,175,50,50));
        gjxyjlabel4->setPixmap(*gjxyj);
        gjxyjlabel4->setScaledContents(true);

        gjxyjlabel->show();
        gjxyjlabel2->show();
        gjxyjlabel3->show();
        gjxyjlabel4->show();
    }
    }else{total -= 5;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}


void selectModel::addmn1shipSlot(){
    total = total + 5;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        cmnship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(14,1,QString::number(cmnship));
        showFleet->setText(strship);
        mnac1->setText(tr("致远(已选择)"));

    if (cmnship == 1){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);
        zjxyjlabel->show();
    }else if(cmnship == 2){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);

        QLabel *zjxyjlabel2 = new QLabel(this);
        zjxyjlabel2->setGeometry(QRect(100,75,50,50));
        zjxyjlabel2->setPixmap(*zjxyj);
        zjxyjlabel2->setScaledContents(true);
        zjxyjlabel->show();
        zjxyjlabel2->show();
    }else if (cmnship == 3){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);

        QLabel *zjxyjlabel2 = new QLabel(this);
        zjxyjlabel2->setGeometry(QRect(100,75,50,50));
        zjxyjlabel2->setPixmap(*zjxyj);
        zjxyjlabel2->setScaledContents(true);

        QLabel *zjxyjlabel3 = new QLabel(this);
        zjxyjlabel3->setGeometry(QRect(100,125,50,50));
        zjxyjlabel3->setPixmap(*zjxyj);
        zjxyjlabel3->setScaledContents(true);

        zjxyjlabel->show();
        zjxyjlabel2->show();
        zjxyjlabel3->show();
    }else if (cmnship == 4){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);

        QLabel *zjxyjlabel2 = new QLabel(this);
        zjxyjlabel2->setGeometry(QRect(100,75,50,50));
        zjxyjlabel2->setPixmap(*zjxyj);
        zjxyjlabel2->setScaledContents(true);

        QLabel *zjxyjlabel3 = new QLabel(this);
        zjxyjlabel3->setGeometry(QRect(100,125,50,50));
        zjxyjlabel3->setPixmap(*zjxyj);
        zjxyjlabel3->setScaledContents(true);

        QLabel *zjxyjlabel4 = new QLabel(this);
        zjxyjlabel4->setGeometry(QRect(100,175,50,50));
        zjxyjlabel4->setPixmap(*zjxyj);
        zjxyjlabel4->setScaledContents(true);

        zjxyjlabel->show();
        zjxyjlabel2->show();
        zjxyjlabel3->show();
        zjxyjlabel4->show();
    }
    }else{total -= 5;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}

void selectModel::addmn2shipSlot(){
    total = total + 5;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        cmnship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(14,1,QString::number(cmnship));
        showFleet->setText(strship);
        mnac2->setText(tr("济远(已选择)"));

    if (cmnship == 1){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);
        zjxyjlabel->show();
    }else if(cmnship == 2){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);

        QLabel *zjxyjlabel2 = new QLabel(this);
        zjxyjlabel2->setGeometry(QRect(100,75,50,50));
        zjxyjlabel2->setPixmap(*zjxyj);
        zjxyjlabel2->setScaledContents(true);
        zjxyjlabel->show();
        zjxyjlabel2->show();
    }else if (cmnship == 3){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);

        QLabel *zjxyjlabel2 = new QLabel(this);
        zjxyjlabel2->setGeometry(QRect(100,75,50,50));
        zjxyjlabel2->setPixmap(*zjxyj);
        zjxyjlabel2->setScaledContents(true);

        QLabel *zjxyjlabel3 = new QLabel(this);
        zjxyjlabel3->setGeometry(QRect(100,125,50,50));
        zjxyjlabel3->setPixmap(*zjxyj);
        zjxyjlabel3->setScaledContents(true);

        zjxyjlabel->show();
        zjxyjlabel2->show();
        zjxyjlabel3->show();
    }else if (cmnship == 4){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);

        QLabel *zjxyjlabel2 = new QLabel(this);
        zjxyjlabel2->setGeometry(QRect(100,75,50,50));
        zjxyjlabel2->setPixmap(*zjxyj);
        zjxyjlabel2->setScaledContents(true);

        QLabel *zjxyjlabel3 = new QLabel(this);
        zjxyjlabel3->setGeometry(QRect(100,125,50,50));
        zjxyjlabel3->setPixmap(*zjxyj);
        zjxyjlabel3->setScaledContents(true);

        QLabel *zjxyjlabel4 = new QLabel(this);
        zjxyjlabel4->setGeometry(QRect(100,175,50,50));
        zjxyjlabel4->setPixmap(*zjxyj);
        zjxyjlabel4->setScaledContents(true);

        zjxyjlabel->show();
        zjxyjlabel2->show();
        zjxyjlabel3->show();
        zjxyjlabel4->show();
    }
    }else{total -= 5;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}

void selectModel::addmn3shipSlot(){
    total = total + 5;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        cmnship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(14,1,QString::number(cmnship));
        showFleet->setText(strship);
        mnac3->setText(tr("靖远(已选择)"));

    if (cmnship == 1){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);
        zjxyjlabel->show();
    }else if(cmnship == 2){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);

        QLabel *zjxyjlabel2 = new QLabel(this);
        zjxyjlabel2->setGeometry(QRect(100,75,50,50));
        zjxyjlabel2->setPixmap(*zjxyj);
        zjxyjlabel2->setScaledContents(true);
        zjxyjlabel->show();
        zjxyjlabel2->show();
    }else if (cmnship == 3){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);

        QLabel *zjxyjlabel2 = new QLabel(this);
        zjxyjlabel2->setGeometry(QRect(100,75,50,50));
        zjxyjlabel2->setPixmap(*zjxyj);
        zjxyjlabel2->setScaledContents(true);

        QLabel *zjxyjlabel3 = new QLabel(this);
        zjxyjlabel3->setGeometry(QRect(100,125,50,50));
        zjxyjlabel3->setPixmap(*zjxyj);
        zjxyjlabel3->setScaledContents(true);

        zjxyjlabel->show();
        zjxyjlabel2->show();
        zjxyjlabel3->show();
    }else if (cmnship == 4){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);

        QLabel *zjxyjlabel2 = new QLabel(this);
        zjxyjlabel2->setGeometry(QRect(100,75,50,50));
        zjxyjlabel2->setPixmap(*zjxyj);
        zjxyjlabel2->setScaledContents(true);

        QLabel *zjxyjlabel3 = new QLabel(this);
        zjxyjlabel3->setGeometry(QRect(100,125,50,50));
        zjxyjlabel3->setPixmap(*zjxyj);
        zjxyjlabel3->setScaledContents(true);

        QLabel *zjxyjlabel4 = new QLabel(this);
        zjxyjlabel4->setGeometry(QRect(100,175,50,50));
        zjxyjlabel4->setPixmap(*zjxyj);
        zjxyjlabel4->setScaledContents(true);

        zjxyjlabel->show();
        zjxyjlabel2->show();
        zjxyjlabel3->show();
        zjxyjlabel4->show();
    }
    }else{total -= 5;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}

void selectModel::addl1shipSlot(){
    total = total + 10;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
    clship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(4,1,QString::number(clship));
        showFleet->setText(strship);
    lac1->setText(tr("定远(已选择)"));
    if (clship == 1){
        tjjlable = new QLabel(this);
        tjjlable->setGeometry(QRect(0,25,100,100));
        tjj = new QPixmap;
        tjj->load(":/images/images/warshipsInGame/1690374707.jpg");
        tjjlable->setPixmap(*tjj);
        tjjlable->setScaledContents(true);
        tjjlable->show();
    }else if(clship == 2){
        tjjlable = new QLabel(this);
        tjjlable->setGeometry(QRect(0,25,100,100));
        tjj = new QPixmap;
        tjj->load(":/images/images/warshipsInGame/1690374707.jpg");
        tjjlable->setPixmap(*tjj);
        tjjlable->setScaledContents(true);

        QLabel *tjjlable2 = new QLabel(this);
        tjjlable2->setGeometry(QRect(0,125,100,100));
        tjjlable2->setPixmap(*tjj);
        tjjlable2->setScaledContents(true);
        tjjlable->show();
        tjjlable2->show();
    }
    }else{total -= 10;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}

void selectModel::addl2shipSlot(){
    total = total + 10;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
    clship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(4,1,QString::number(clship));
        showFleet->setText(strship);
    lac2->setText(tr("镇远(已选择)"));
    if (clship == 1){
        tjjlable = new QLabel(this);
        tjjlable->setGeometry(QRect(0,25,100,100));
        tjj = new QPixmap;
        tjj->load(":/images/images/warshipsInGame/1690374707.jpg");
        tjjlable->setPixmap(*tjj);
        tjjlable->setScaledContents(true);
        tjjlable->show();
    }else if(clship == 2){
        tjjlable = new QLabel(this);
        tjjlable->setGeometry(QRect(0,25,100,100));
        tjj = new QPixmap;
        tjj->load(":/images/images/warshipsInGame/1690374707.jpg");
        tjjlable->setPixmap(*tjj);
        tjjlable->setScaledContents(true);

        QLabel *tjjlable2 = new QLabel(this);
        tjjlable2->setGeometry(QRect(0,125,100,100));
        tjjlable2->setPixmap(*tjj);
        tjjlable2->setScaledContents(true);
        tjjlable->show();
        tjjlable2->show();
    }
    }else{total -= 10;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}

void selectModel::addl3shipSlot(){
    total = total + 10;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
    clship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(4,1,QString::number(clship));
        showFleet->setText(strship);
    lac3->setText(tr("平远(已选择)"));
    if (clship == 1){
        tjjlable = new QLabel(this);
        tjjlable->setGeometry(QRect(0,25,100,100));
        tjj = new QPixmap;
        tjj->load(":/images/images/warshipsInGame/1690374707.jpg");
        tjjlable->setPixmap(*tjj);
        tjjlable->setScaledContents(true);
        tjjlable->show();
    }else if(clship == 2){
        tjjlable = new QLabel(this);
        tjjlable->setGeometry(QRect(0,25,100,100));
        tjj = new QPixmap;
        tjj->load(":/images/images/warshipsInGame/1690374707.jpg");
        tjjlable->setPixmap(*tjj);
        tjjlable->setScaledContents(true);

        QLabel *tjjlable2 = new QLabel(this);
        tjjlable2->setGeometry(QRect(0,125,100,100));
        tjjlable2->setPixmap(*tjj);
        tjjlable2->setScaledContents(true);
        tjjlable->show();
        tjjlable2->show();
    }
    }else{total -= 10;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}



void selectModel::adds1shipSlotr(){
    total = total + 2;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        csship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(42,1,QString::number(csship));
        showFleet->setText(strship);
        sac1->setText(tr("赤城(已选择)"));
    if (csship == 1){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,40));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/1690374707.jpg");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 2){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,80));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/2ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 3){
            gkkclabel = new QLabel(this);
            gkkclabel->setGeometry(QRect(250,25,25,120));
            gkkc = new QPixmap;
            gkkc->load(":/images/images/warshipsInGame/3ship.png");
            gkkclabel->setPixmap(*gkkc);
            gkkclabel->setScaledContents(true);
            gkkclabel->show();
    }else if (csship == 4){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,160));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/4ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 5){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/5ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 6){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/6ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 7){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/7ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 8){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/8ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 9){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/9ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 10){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/10ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }
    }else{total -= 2;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}

void selectModel::adds2shipSlotr(){
    total = total + 2;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        csship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(42,1,QString::number(csship));
        showFleet->setText(strship);
        sac2->setText(tr("秋津洲(已选择)"));
    if (csship == 1){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,40));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/1690374707.jpg");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 2){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,80));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/2ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 3){
            gkkclabel = new QLabel(this);
            gkkclabel->setGeometry(QRect(250,25,25,120));
            gkkc = new QPixmap;
            gkkc->load(":/images/images/warshipsInGame/3ship.png");
            gkkclabel->setPixmap(*gkkc);
            gkkclabel->setScaledContents(true);
            gkkclabel->show();
    }else if (csship == 4){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,160));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/4ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 5){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/5ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 6){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/6ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 7){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/7ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 8){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/8ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 9){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/9ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 10){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/10ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }
    }else{total -= 2;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}

void selectModel::adds3shipSlotr(){
    total = total + 2;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        csship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(42,1,QString::number(csship));
        showFleet->setText(strship);
        sac3->setText(tr("广丙(已选择)"));
    if (csship == 1){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,40));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/1690374707.jpg");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 2){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,80));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/2ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 3){
            gkkclabel = new QLabel(this);
            gkkclabel->setGeometry(QRect(250,25,25,120));
            gkkc = new QPixmap;
            gkkc->load(":/images/images/warshipsInGame/3ship.png");
            gkkclabel->setPixmap(*gkkc);
            gkkclabel->setScaledContents(true);
            gkkclabel->show();
    }else if (csship == 4){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,160));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/4ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 5){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,25,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/5ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 6){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/6ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 7){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/7ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 8){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/8ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 9){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/9ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csship == 10){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(250,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/10ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }
    }else{total -= 2;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}

void selectModel::addsm1shipSlotr(){
    total = total + 2;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        csmship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(34,1,QString::number(csmship));
        showFleet->setText(strship);
        smac1->setText(tr("西京丸1(已选择)"));
    if (csmship == 1){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,40));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/1690374707.jpg");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 2){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,80));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/2ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 3){
            gkkclabel = new QLabel(this);
            gkkclabel->setGeometry(QRect(200,25,25,120));
            gkkc = new QPixmap;
            gkkc->load(":/images/images/warshipsInGame/3ship.png");
            gkkclabel->setPixmap(*gkkc);
            gkkclabel->setScaledContents(true);
            gkkclabel->show();
    }else if (csmship == 4){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,160));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/4ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 5){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/5ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 6){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/arshipsInGame/6ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 7){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/7ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 8){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/8ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 9){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/9ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 10){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/10ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }
    }else{total -= 2;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}


void selectModel::addsm2shipSlotr(){
    total = total + 2;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        csmship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(34,1,QString::number(csmship));
        showFleet->setText(strship);
        smac2->setText(tr("西京丸2(已选择)"));
    if (csmship == 1){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,40));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/1690374707.jpg");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 2){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,80));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/2ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 3){
            gkkclabel = new QLabel(this);
            gkkclabel->setGeometry(QRect(200,25,25,120));
            gkkc = new QPixmap;
            gkkc->load(":/images/images/warshipsInGame/3ship.png");
            gkkclabel->setPixmap(*gkkc);
            gkkclabel->setScaledContents(true);
            gkkclabel->show();
    }else if (csmship == 4){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,160));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/4ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 5){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/5ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 6){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/6ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 7){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/7ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 8){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/8ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 9){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/9ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 10){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/10ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }
    }else{total -= 2;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}


void selectModel::addsm3shipSlotr(){
    total = total + 2;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        csmship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(34,1,QString::number(csmship));
        showFleet->setText(strship);
        smac3->setText(tr("西京丸3(已选择)"));
    if (csmship == 1){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,40));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/1690374707.jpg");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 2){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,80));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/2ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 3){
            gkkclabel = new QLabel(this);
            gkkclabel->setGeometry(QRect(200,25,25,120));
            gkkc = new QPixmap;
            gkkc->load(":/images/images/warshipsInGame/3ship.png");
            gkkclabel->setPixmap(*gkkc);
            gkkclabel->setScaledContents(true);
            gkkclabel->show();
    }else if (csmship == 4){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,160));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/4ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 5){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,25,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/5ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 6){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/6ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 7){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/7ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 8){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/8ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 9){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/9ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }else if (csmship == 10){
        gkkclabel = new QLabel(this);
        gkkclabel->setGeometry(QRect(200,25,50,200));
        gkkc = new QPixmap;
        gkkc->load(":/images/images/warshipsInGame/10ship.png");
        gkkclabel->setPixmap(*gkkc);
        gkkclabel->setScaledContents(true);
        gkkclabel->show();
    }
    }else{total -= 2;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}


void selectModel::addm1shipSlotr(){
    total = total + 5;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        cmship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(24,1,QString::number(cmship));
        showFleet->setText(strship);
        mac1->setText(tr("千代田(已选择)"));

    if (cmship == 1){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);
        gjxyjlabel->show();
    }else if(cmship == 2){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);

        QLabel *gjxyjlabel2 = new QLabel(this);
        gjxyjlabel2->setGeometry(QRect(150,75,50,50));
        gjxyjlabel2->setPixmap(*gjxyj);
        gjxyjlabel2->setScaledContents(true);
        gjxyjlabel->show();
        gjxyjlabel2->show();
    }else if (cmship == 3){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);

        QLabel *gjxyjlabel2 = new QLabel(this);
        gjxyjlabel2->setGeometry(QRect(150,75,50,50));
        gjxyjlabel2->setPixmap(*gjxyj);
        gjxyjlabel2->setScaledContents(true);

        QLabel *gjxyjlabel3 = new QLabel(this);
        gjxyjlabel3->setGeometry(QRect(150,125,50,50));
        gjxyjlabel3->setPixmap(*gjxyj);
        gjxyjlabel3->setScaledContents(true);

        gjxyjlabel->show();
        gjxyjlabel2->show();
        gjxyjlabel3->show();
    }else if (cmship == 4){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);

        QLabel *gjxyjlabel2 = new QLabel(this);
        gjxyjlabel2->setGeometry(QRect(150,75,50,50));
        gjxyjlabel2->setPixmap(*gjxyj);
        gjxyjlabel2->setScaledContents(true);

        QLabel *gjxyjlabel3 = new QLabel(this);
        gjxyjlabel3->setGeometry(QRect(150,125,50,50));
        gjxyjlabel3->setPixmap(*gjxyj);
        gjxyjlabel3->setScaledContents(true);

        QLabel *gjxyjlabel4 = new QLabel(this);
        gjxyjlabel4->setGeometry(QRect(150,175,50,50));
        gjxyjlabel4->setPixmap(*gjxyj);
        gjxyjlabel4->setScaledContents(true);

        gjxyjlabel->show();
        gjxyjlabel2->show();
        gjxyjlabel3->show();
        gjxyjlabel4->show();
    }
    }else{total -= 5;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}

void selectModel::addm2shipSlotr(){
    total = total + 5;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        cmship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(24,1,QString::number(cmship));
        showFleet->setText(strship);
        mac2->setText(tr("浪速(已选择)"));

    if (cmship == 1){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);
        gjxyjlabel->show();
    }else if(cmship == 2){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);

        QLabel *gjxyjlabel2 = new QLabel(this);
        gjxyjlabel2->setGeometry(QRect(150,75,50,50));
        gjxyjlabel2->setPixmap(*gjxyj);
        gjxyjlabel2->setScaledContents(true);
        gjxyjlabel->show();
        gjxyjlabel2->show();
    }else if (cmship == 3){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);

        QLabel *gjxyjlabel2 = new QLabel(this);
        gjxyjlabel2->setGeometry(QRect(150,75,50,50));
        gjxyjlabel2->setPixmap(*gjxyj);
        gjxyjlabel2->setScaledContents(true);

        QLabel *gjxyjlabel3 = new QLabel(this);
        gjxyjlabel3->setGeometry(QRect(150,125,50,50));
        gjxyjlabel3->setPixmap(*gjxyj);
        gjxyjlabel3->setScaledContents(true);

        gjxyjlabel->show();
        gjxyjlabel2->show();
        gjxyjlabel3->show();
    }else if (cmship == 4){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);

        QLabel *gjxyjlabel2 = new QLabel(this);
        gjxyjlabel2->setGeometry(QRect(150,75,50,50));
        gjxyjlabel2->setPixmap(*gjxyj);
        gjxyjlabel2->setScaledContents(true);

        QLabel *gjxyjlabel3 = new QLabel(this);
        gjxyjlabel3->setGeometry(QRect(150,125,50,50));
        gjxyjlabel3->setPixmap(*gjxyj);
        gjxyjlabel3->setScaledContents(true);

        QLabel *gjxyjlabel4 = new QLabel(this);
        gjxyjlabel4->setGeometry(QRect(150,175,50,50));
        gjxyjlabel4->setPixmap(*gjxyj);
        gjxyjlabel4->setScaledContents(true);

        gjxyjlabel->show();
        gjxyjlabel2->show();
        gjxyjlabel3->show();
        gjxyjlabel4->show();
    }
    }else{total -= 5;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}

void selectModel::addm3shipSlotr(){
    total = total + 5;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        cmship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(24,1,QString::number(cmship));
        showFleet->setText(strship);
        mac3->setText(tr("高千穗(已选择)"));

    if (cmship == 1){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);
        gjxyjlabel->show();
    }else if(cmship == 2){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);

        QLabel *gjxyjlabel2 = new QLabel(this);
        gjxyjlabel2->setGeometry(QRect(150,75,50,50));
        gjxyjlabel2->setPixmap(*gjxyj);
        gjxyjlabel2->setScaledContents(true);
        gjxyjlabel->show();
        gjxyjlabel2->show();
    }else if (cmship == 3){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);

        QLabel *gjxyjlabel2 = new QLabel(this);
        gjxyjlabel2->setGeometry(QRect(150,75,50,50));
        gjxyjlabel2->setPixmap(*gjxyj);
        gjxyjlabel2->setScaledContents(true);

        QLabel *gjxyjlabel3 = new QLabel(this);
        gjxyjlabel3->setGeometry(QRect(150,125,50,50));
        gjxyjlabel3->setPixmap(*gjxyj);
        gjxyjlabel3->setScaledContents(true);

        gjxyjlabel->show();
        gjxyjlabel2->show();
        gjxyjlabel3->show();
    }else if (cmship == 4){
        gjxyjlabel = new QLabel(this);
        gjxyjlabel->setGeometry(QRect(150,25,50,50));
        gjxyj = new QPixmap;
        gjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        gjxyjlabel->setPixmap(*gjxyj);
        gjxyjlabel->setScaledContents(true);

        QLabel *gjxyjlabel2 = new QLabel(this);
        gjxyjlabel2->setGeometry(QRect(150,75,50,50));
        gjxyjlabel2->setPixmap(*gjxyj);
        gjxyjlabel2->setScaledContents(true);

        QLabel *gjxyjlabel3 = new QLabel(this);
        gjxyjlabel3->setGeometry(QRect(150,125,50,50));
        gjxyjlabel3->setPixmap(*gjxyj);
        gjxyjlabel3->setScaledContents(true);

        QLabel *gjxyjlabel4 = new QLabel(this);
        gjxyjlabel4->setGeometry(QRect(150,175,50,50));
        gjxyjlabel4->setPixmap(*gjxyj);
        gjxyjlabel4->setScaledContents(true);

        gjxyjlabel->show();
        gjxyjlabel2->show();
        gjxyjlabel3->show();
        gjxyjlabel4->show();
    }
    }else{total -= 5;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}


void selectModel::addmn1shipSlotr(){
    total = total + 5;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        cmnship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(14,1,QString::number(cmnship));
        showFleet->setText(strship);
        mnac1->setText(tr("松岛(已选择)"));

    if (cmnship == 1){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);
        zjxyjlabel->show();
    }else if(cmnship == 2){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);

        QLabel *zjxyjlabel2 = new QLabel(this);
        zjxyjlabel2->setGeometry(QRect(100,75,50,50));
        zjxyjlabel2->setPixmap(*zjxyj);
        zjxyjlabel2->setScaledContents(true);
        zjxyjlabel->show();
        zjxyjlabel2->show();
    }else if (cmnship == 3){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);

        QLabel *zjxyjlabel2 = new QLabel(this);
        zjxyjlabel2->setGeometry(QRect(100,75,50,50));
        zjxyjlabel2->setPixmap(*zjxyj);
        zjxyjlabel2->setScaledContents(true);

        QLabel *zjxyjlabel3 = new QLabel(this);
        zjxyjlabel3->setGeometry(QRect(100,125,50,50));
        zjxyjlabel3->setPixmap(*zjxyj);
        zjxyjlabel3->setScaledContents(true);

        zjxyjlabel->show();
        zjxyjlabel2->show();
        zjxyjlabel3->show();
    }else if (cmnship == 4){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);

        QLabel *zjxyjlabel2 = new QLabel(this);
        zjxyjlabel2->setGeometry(QRect(100,75,50,50));
        zjxyjlabel2->setPixmap(*zjxyj);
        zjxyjlabel2->setScaledContents(true);

        QLabel *zjxyjlabel3 = new QLabel(this);
        zjxyjlabel3->setGeometry(QRect(100,125,50,50));
        zjxyjlabel3->setPixmap(*zjxyj);
        zjxyjlabel3->setScaledContents(true);

        QLabel *zjxyjlabel4 = new QLabel(this);
        zjxyjlabel4->setGeometry(QRect(100,175,50,50));
        zjxyjlabel4->setPixmap(*zjxyj);
        zjxyjlabel4->setScaledContents(true);

        zjxyjlabel->show();
        zjxyjlabel2->show();
        zjxyjlabel3->show();
        zjxyjlabel4->show();
    }
    }else{total -= 5;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}

void selectModel::addmn2shipSlotr(){
    total = total + 5;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        cmnship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(14,1,QString::number(cmnship));
        showFleet->setText(strship);
        mnac2->setText(tr("严岛(已选择)"));

    if (cmnship == 1){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);
        zjxyjlabel->show();
    }else if(cmnship == 2){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);

        QLabel *zjxyjlabel2 = new QLabel(this);
        zjxyjlabel2->setGeometry(QRect(100,75,50,50));
        zjxyjlabel2->setPixmap(*zjxyj);
        zjxyjlabel2->setScaledContents(true);
        zjxyjlabel->show();
        zjxyjlabel2->show();
    }else if (cmnship == 3){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);

        QLabel *zjxyjlabel2 = new QLabel(this);
        zjxyjlabel2->setGeometry(QRect(100,75,50,50));
        zjxyjlabel2->setPixmap(*zjxyj);
        zjxyjlabel2->setScaledContents(true);

        QLabel *zjxyjlabel3 = new QLabel(this);
        zjxyjlabel3->setGeometry(QRect(100,125,50,50));
        zjxyjlabel3->setPixmap(*zjxyj);
        zjxyjlabel3->setScaledContents(true);

        zjxyjlabel->show();
        zjxyjlabel2->show();
        zjxyjlabel3->show();
    }else if (cmnship == 4){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);

        QLabel *zjxyjlabel2 = new QLabel(this);
        zjxyjlabel2->setGeometry(QRect(100,75,50,50));
        zjxyjlabel2->setPixmap(*zjxyj);
        zjxyjlabel2->setScaledContents(true);

        QLabel *zjxyjlabel3 = new QLabel(this);
        zjxyjlabel3->setGeometry(QRect(100,125,50,50));
        zjxyjlabel3->setPixmap(*zjxyj);
        zjxyjlabel3->setScaledContents(true);

        QLabel *zjxyjlabel4 = new QLabel(this);
        zjxyjlabel4->setGeometry(QRect(100,175,50,50));
        zjxyjlabel4->setPixmap(*zjxyj);
        zjxyjlabel4->setScaledContents(true);

        zjxyjlabel->show();
        zjxyjlabel2->show();
        zjxyjlabel3->show();
        zjxyjlabel4->show();
    }
    }else{total -= 5;
        QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}

void selectModel::addmn3shipSlotr(){
    total = total + 5;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
        cmnship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(14,1,QString::number(cmnship));
        showFleet->setText(strship);
        mnac3->setText(tr("桥立(已选择)"));

    if (cmnship == 1){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);
        zjxyjlabel->show();
    }else if(cmnship == 2){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);

        QLabel *zjxyjlabel2 = new QLabel(this);
        zjxyjlabel2->setGeometry(QRect(100,75,50,50));
        zjxyjlabel2->setPixmap(*zjxyj);
        zjxyjlabel2->setScaledContents(true);
        zjxyjlabel->show();
        zjxyjlabel2->show();
    }else if (cmnship == 3){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);

        QLabel *zjxyjlabel2 = new QLabel(this);
        zjxyjlabel2->setGeometry(QRect(100,75,50,50));
        zjxyjlabel2->setPixmap(*zjxyj);
        zjxyjlabel2->setScaledContents(true);

        QLabel *zjxyjlabel3 = new QLabel(this);
        zjxyjlabel3->setGeometry(QRect(100,125,50,50));
        zjxyjlabel3->setPixmap(*zjxyj);
        zjxyjlabel3->setScaledContents(true);

        zjxyjlabel->show();
        zjxyjlabel2->show();
        zjxyjlabel3->show();
    }else if (cmnship == 4){
        zjxyjlabel = new QLabel(this);
        zjxyjlabel->setGeometry(QRect(100,25,50,50));
        zjxyj = new QPixmap;
        zjxyj->load(":/images/images/warshipsInGame/1690374707.jpg");
        zjxyjlabel->setPixmap(*zjxyj);
        zjxyjlabel->setScaledContents(true);

        QLabel *zjxyjlabel2 = new QLabel(this);
        zjxyjlabel2->setGeometry(QRect(100,75,50,50));
        zjxyjlabel2->setPixmap(*zjxyj);
        zjxyjlabel2->setScaledContents(true);

        QLabel *zjxyjlabel3 = new QLabel(this);
        zjxyjlabel3->setGeometry(QRect(100,125,50,50));
        zjxyjlabel3->setPixmap(*zjxyj);
        zjxyjlabel3->setScaledContents(true);

        QLabel *zjxyjlabel4 = new QLabel(this);
        zjxyjlabel4->setGeometry(QRect(100,175,50,50));
        zjxyjlabel4->setPixmap(*zjxyj);
        zjxyjlabel4->setScaledContents(true);

        zjxyjlabel->show();
        zjxyjlabel2->show();
        zjxyjlabel3->show();
        zjxyjlabel4->show();
    }
    }else{total -= 5;
    QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}

void selectModel::addl1shipSlotr(){
    total = total + 10;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
    clship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(4,1,QString::number(clship));
        showFleet->setText(strship);
    lac1->setText(tr("比睿(已选择)"));
    if (clship == 1){
        tjjlable = new QLabel(this);
        tjjlable->setGeometry(QRect(0,25,100,100));
        tjj = new QPixmap;
        tjj->load(":/images/images/warshipsInGame/1690374707.jpg");
        tjjlable->setPixmap(*tjj);
        tjjlable->setScaledContents(true);
        tjjlable->show();
    }else if(clship == 2){
        tjjlable = new QLabel(this);
        tjjlable->setGeometry(QRect(0,25,100,100));
        tjj = new QPixmap;
        tjj->load(":/images/images/warshipsInGame/1690374707.jpg");
        tjjlable->setPixmap(*tjj);
        tjjlable->setScaledContents(true);

        QLabel *tjjlable2 = new QLabel(this);
        tjjlable2->setGeometry(QRect(0,125,100,100));
        tjjlable2->setPixmap(*tjj);
        tjjlable2->setScaledContents(true);
        tjjlable->show();
        tjjlable2->show();
    }
    }else{total -= 10;
    QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}

void selectModel::addl2shipSlotr(){
    total = total + 10;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
    clship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(4,1,QString::number(clship));
        showFleet->setText(strship);
    lac2->setText(tr("扶桑(已选择)"));
    if (clship == 1){
        tjjlable = new QLabel(this);
        tjjlable->setGeometry(QRect(0,25,100,100));
        tjj = new QPixmap;
        tjj->load(":/images/images/warshipsInGame/1690374707.jpg");
        tjjlable->setPixmap(*tjj);
        tjjlable->setScaledContents(true);
        tjjlable->show();
    }else if(clship == 2){
        tjjlable = new QLabel(this);
        tjjlable->setGeometry(QRect(0,25,100,100));
        tjj = new QPixmap;
        tjj->load(":/images/images/warshipsInGame/1690374707.jpg");
        tjjlable->setPixmap(*tjj);
        tjjlable->setScaledContents(true);

        QLabel *tjjlable2 = new QLabel(this);
        tjjlable2->setGeometry(QRect(0,125,100,100));
        tjjlable2->setPixmap(*tjj);
        tjjlable2->setScaledContents(true);
        tjjlable->show();
        tjjlable2->show();
    }
    }else{total -= 10;
    QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}

void selectModel::addl3shipSlotr(){
    total = total + 10;
    QString strtotal = "";
    QString s = QString::number(total);
    if (total<= 20){
    clship += 1;
        strtotal = strtotal.append("舰队容量：");
        strtotal = strtotal.append(s);
        strtotal = strtotal.append("/20");
        showCredit->setText(strtotal);
        strship = strship.replace(4,1,QString::number(clship));
        showFleet->setText(strship);
    lac3->setText(tr("吉野(已选择)"));
    if (clship == 1){
        tjjlable = new QLabel(this);
        tjjlable->setGeometry(QRect(0,25,100,100));
        tjj = new QPixmap;
        tjj->load(":/images/images/warshipsInGame/1690374707.jpg");
        tjjlable->setPixmap(*tjj);
        tjjlable->setScaledContents(true);
        tjjlable->show();
    }else if(clship == 2){
        tjjlable = new QLabel(this);
        tjjlable->setGeometry(QRect(0,25,100,100));
        tjj = new QPixmap;
        tjj->load(":/images/images/warshipsInGame/1690374707.jpg");
        tjjlable->setPixmap(*tjj);
        tjjlable->setScaledContents(true);

        QLabel *tjjlable2 = new QLabel(this);
        tjjlable2->setGeometry(QRect(0,125,100,100));
        tjjlable2->setPixmap(*tjj);
        tjjlable2->setScaledContents(true);
        tjjlable->show();
        tjjlable2->show();
    }
    }else{total -= 10;
    QMessageBox::information(this, "警告","您所选择的舰船超出容量");}
}



void selectModel::clearAllSlot(){
    total = 0;
    csship = 0;
    csmship = 0;
    cmship = 0;
    cmnship = 0;
    clship = 0;
    showCredit->setText("舰队容量：0/20");
    strship = "铁甲舰：0艘； 穹甲巡洋舰：0艘； 装甲巡洋舰：0艘； 木壳快船：0艘； 钢壳快船： 0艘";
    showFleet->setText("铁甲舰：0艘； 穹甲巡洋舰：0艘； 装甲巡洋舰：0艘； 木壳快船：0艘； 钢壳快船： 0艘");
    fleetlable = new QLabel(this);
    fleetlable->setGeometry(QRect(0,0,300,250));
    background = new QPixmap;
    background->load(":/images/images/warshipsInGame/timg-13.jpeg");
    fleetlable->setPixmap(*background);
    fleetlable->show();
    smac1->setText(tr("广甲1"));
    smac2->setText(tr("广甲2"));
    smac3->setText(tr("广甲3"));
    sac1->setText(tr("超勇"));
    sac2->setText(tr("扬威"));
    sac3->setText(tr("广丙"));
    mnac1->setText(tr("致远"));
    mnac2->setText(tr("济远"));
    mnac3->setText(tr("靖远"));
    mac1->setText(tr("经远"));
    mac2->setText(tr("来远"));
    mac3->setText(tr("威远"));
    lac1->setText(tr("定远"));
    lac2->setText(tr("镇远"));
    lac3->setText(tr("平远"));
}


void selectModel::clearAllSlotr(){
    total = 0;
    csship = 0;
    csmship = 0;
    cmship = 0;
    cmnship = 0;
    clship = 0;
    showCredit->setText("舰队容量：0/20");
    strship = "铁甲舰：0艘； 防护巡洋舰：0艘； 装甲巡洋舰：0艘； 辅助巡洋舰：0艘； 炮舰： 0艘";
    showFleet->setText("铁甲舰：0艘； 防护巡洋舰：0艘； 装甲巡洋舰：0艘； 辅助巡洋舰：0艘； 炮舰： 0艘");
    fleetlable = new QLabel(this);
    fleetlable->setGeometry(QRect(0,0,300,250));
    background = new QPixmap;
    background->load(":/images/images/warshipsInGame/timg-13.jpeg");
    fleetlable->setPixmap(*background);
    fleetlable->show();
    smac1->setText(tr("西京丸1"));
    smac2->setText(tr("西京丸2"));
    smac3->setText(tr("西京丸3"));
    sac1->setText(tr("赤城"));
    sac2->setText(tr("秋津洲"));
    mnac1->setText(tr("松岛"));
    mnac2->setText(tr("严岛"));
    mnac3->setText(tr("桥立"));
    mac1->setText(tr("千代田"));
    mac2->setText(tr("浪速"));
    mac3->setText(tr("高千穗"));
    lac1->setText(tr("比睿"));
    lac2->setText(tr("扶桑"));
    lac3->setText(tr("吉野"));

}




void selectModel::StartFleetGameSlot(){
    if(total == 0) {
        QMessageBox::information(this, "警告","您未选择任何舰船");
    } else{
        QDir dir;
        QString currentPath = dir.currentPath();
        QString path = currentPath.section('/',0,-2);
        QString fileName = path+"/jiawuGame/files/userselect.txt";
        QFile file(fileName);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream out(&file);

        out << clship  << endl;
        out << cmnship << endl;
        out << cmship << endl;
        out << csmship << endl;
        out << csship << endl;
        out << country << endl;
        out.flush();
        file.close();

        GameWidget *enterGame = new GameWidget();
        enterGame->show();
    }
}
