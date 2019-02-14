#include "GameWidget.h"
#define ROW 90
#define COL 120
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

GameWidget::GameWidget(QWidget *parent) : QWidget(parent)
{
    QDir dir;
    QString currentPath = dir.currentPath();
    QString path = currentPath.section('/',0,-2);
    QString fileName = path+"/jiawuGame/files/userselect.txt";
    userSelect.clear();
    bool ok;
    int i = 1;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
         return;
    }
    QTextStream in(&file);
    while(!in.atEnd()){
        QString count= in.read(1);
        if((i%3) == 1){
            userSelect.push_back(count.toInt(&ok, 10));
            if (i == 16){
                if (count.toInt(&ok, 10) == 1)country = 1;
            }}
        i += 1;
    }
    file.close();
    if (country == 0) {
        setWarshipList(userSelect);
        setEnemyWarshipList(setEnemyCombination());
        setInitialPosition();
        setEnemyInitialPosition();
        countryID = "Q";
        enemyID = "J";
    } else if (country == 1) {
        setWarshipList(setEnemyCombination());
        setEnemyWarshipList(userSelect);
        setInitialPosition();
        setEnemyInitialPosition();
        vector<warship> k = warshipList;
        warshipList = EnemyWarshipList;
        EnemyWarshipList = k;
        countryID = "J";
        enemyID = "Q";
    }

    for (int i=0;i<ROW;i++) {
        vector<int> x;
        for (int j=0;j<COL;j++) {
            x.push_back(0);}
        sightRange.push_back(x);
    }

    this->setAutoFillBackground(true);
    this->setWindowTitle("游戏开始");
    this->resize(1600,900);
    this->setMaximumSize(1600,900);

    //设置字体
    QFont ft;
    ft.setPointSize(15);
    QFont sft;
    sft.setPointSize(9);

    //形成血量文字的label
    for (unsigned i=0;i<warshipList.size();i++) {
        QLabel *warshipBloodLabel = new QLabel(this);
        warshipBloodLabel->setFont(sft);
        warshipBloodLabel->setText(QString::number(warshipList[i].life)+"/100");
        warshipBloodLabel->setStyleSheet("color:white");
        warshipBloodLabel->setGeometry(QRect(1360,247+25*i,60,15));
        warshipBlood.push_back(warshipBloodLabel);
    }
    //形成敌人血量文字的label
    for (unsigned i=0;i<EnemyWarshipList.size();i++) {
        QLabel *enemyWarshipBloodLabel = new QLabel(this);
        enemyWarshipBloodLabel->setFont(sft);
        enemyWarshipBloodLabel->setText(QString::number(EnemyWarshipList[i].life)+"/100");
        enemyWarshipBloodLabel->setStyleSheet("color:white");
        enemyWarshipBloodLabel->setGeometry(QRect(1360,707+25*i,60,15));
        enemyWarshipBlood.push_back(enemyWarshipBloodLabel);
    }

    QLabel *nationName = new QLabel(this);
    nationName->setFont(ft);
    nationName->setGeometry(QRect(1330,205,400,30));
    QLabel *enemyName = new QLabel(this);
    enemyName->setFont(ft);
    enemyName->setGeometry(QRect(1330,665,400,30));
    if (country == 0) {
        nationName->setText("大清北洋水师");
        enemyName->setText("日本联合舰队");
    } else {
        nationName->setText("日本联合舰队");
        enemyName->setText("大清北洋水师");
    }

    //输入双方舰名与火力大小
    for (unsigned i=0;i<warshipList.size();i++) {
        QLabel *warshipName = new QLabel(this);
        warshipName->setFont(sft);
        warshipName->setText(warshipList[i].shipName);
        warshipName->setGeometry(QRect(1245,248+25*i,40,15));
        QLabel *warshipFireNum = new QLabel(this);
        warshipFireNum->setFont(sft);
        warshipFireNum->setText("火力:"+QString::number(warshipList[i].firePower));
        warshipFireNum->setGeometry(QRect(1495,248+25*i,80,15));
    }

    for (unsigned i=0;i<EnemyWarshipList.size();i++) {
        QLabel *enemyWarshipName = new QLabel(this);
        enemyWarshipName->setFont(sft);
        enemyWarshipName->setText(EnemyWarshipList[i].shipName);
        enemyWarshipName->setGeometry(QRect(1245,708+25*i,40,15));
        QLabel *enemyWarshipFireNum = new QLabel(this);
        enemyWarshipFireNum->setFont(sft);
        enemyWarshipFireNum->setText("火力:"+QString::number(EnemyWarshipList[i].firePower));
        enemyWarshipFireNum->setGeometry(QRect(1495,708+25*i,80,15));
    }


    shipNumber = 0;
    testship = warshipList[shipNumber];

    gameInfo = new QLabel(this);
    gameInfo->setFont(ft);
    gameInfo->setText(" 目前操作单位:"+testship.shipName);
    gameInfo->setStyleSheet("background-color:white");
    gameInfo->setGeometry(QRect(1240,10,350,30));

    setSightRange();

    setMouseTracking(true);
}

void GameWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (gameRole == 0 && testship.life>0) {
        // 通过鼠标的hover确定落子的标记
        int x = event->x();
        int y = event->y();

        // 获取最近的左上角的点
        int col = x/10;
        int row = y/10;

        // 边缘不能放置战舰
        if (x>= 0 && x<COL*10 && y>=0 && y<ROW*10 && x>=10*(testship.positionX-testship.shipSpeed) && x<=10*(testship.positionX+testship.shipSpeed)
            && y>=10*(testship.positionY-testship.shipSpeed) && y<=10*(testship.positionY+testship.shipSpeed)) {
            clickPosCol = col;
            clickPosRow = row;
        } else if (x>= 0 && x<COL*10 && y>=0 && y<ROW*10 &&
                   (x<10*(testship.positionX-testship.shipSpeed) || x>10*(testship.positionX+testship.shipSpeed) ||
                   y<10*(testship.positionY-testship.shipSpeed) || y>10*(testship.positionY+testship.shipSpeed))){
            if (x>10*(testship.positionX+testship.shipSpeed)) {
                clickPosCol = testship.positionX+testship.shipSpeed;
            } else if (x<10*(testship.positionX-testship.shipSpeed)) {
                clickPosCol = testship.positionX-testship.shipSpeed;
            } else {
                clickPosCol = col;
            }
            if (y>10*(testship.positionY+testship.shipSpeed)) {
                clickPosRow = testship.positionY+testship.shipSpeed;
            } else if (y<10*(testship.positionY-testship.shipSpeed)) {
                clickPosRow = testship.positionY-testship.shipSpeed;
            } else {
                clickPosRow = row;
            }
        }
        update();
    } else if (gameRole == 1) {
        // 通过鼠标的hover确定落子的标记
        int x = event->x();
        int y = event->y();

        // 获取最近的左上角的点
        int col = x/10;
        int row = y/10;

        // 边缘不能打炮
        if (x>= 0 && x<COL*10 && y>=0 && y<ROW*10 &&
            x>=10*(testship.positionX-testship.fireRange) && x<=10*(testship.positionX+testship.fireRange+testship.shipL)
            && y>=10*(testship.positionY-testship.fireRange) && y<=10*(testship.positionY+testship.fireRange+testship.shipH)) {
            firePosCol = col;
            firePosRow = row;
        } else if (x>= 0 && x<COL*10 && y>=0 && y<ROW*10 &&
                   (x<10*(testship.positionX-testship.fireRange) || x>10*(testship.positionX+testship.fireRange+testship.shipL) ||
                   y<10*(testship.positionY-testship.fireRange) || y>10*(testship.positionY+testship.fireRange+testship.shipH))){
            if (x>10*(testship.positionX+testship.fireRange+testship.shipL)) {
                firePosCol = testship.positionX+testship.fireRange+testship.shipL;
            } else if (x<10*(testship.positionX-testship.fireRange)) {
                firePosCol = testship.positionX-testship.fireRange;
            } else {
                firePosCol = col;
            }
            if (y>10*(testship.positionY+testship.fireRange+testship.shipH)) {
                firePosRow = testship.positionY+testship.fireRange+testship.shipH;
            } else if (y<10*(testship.positionY-testship.fireRange)) {
                firePosRow = testship.positionY-testship.fireRange;
            } else {
                firePosRow = row;
            }
        }
    }
    update();
}

void GameWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (gameRole==0 && event->button()==Qt::LeftButton) {
        if (judgeCover(clickPosCol,clickPosRow)) {
            testship.positionX = clickPosCol;
            testship.positionY = clickPosRow;
            warshipList[shipNumber] = testship;

            for (int i=0;i<ROW;i++) {
                for (int j=0;j<COL;j++) {
                    sightRange[i][j]=0;}
            }
            setSightRange();

            gameRole = 1;
        } else {
            gameInfo->setText("非法操作，舰只无法重叠！");
        }
    } else if (gameRole == 1 && event->button()==Qt::LeftButton) {
        for (unsigned i=0;i<EnemyWarshipList.size();i++) {
            if (firePosRow<=(EnemyWarshipList[i].positionY+EnemyWarshipList[i].shipH) &&
                firePosCol<=(EnemyWarshipList[i].positionX+EnemyWarshipList[i].shipL) &&
                firePosRow>=EnemyWarshipList[i].positionY && firePosCol>=EnemyWarshipList[i].positionX) {
                EnemyWarshipList[i].life -= testship.firePower;
        }}
        shipNumber ++;
        while (warshipList[shipNumber].life<=0 && shipNumber<warshipList.size()) {
            shipNumber ++;
        }
        if (shipNumber >= warshipList.size()) {
            shipNumber = 0;
            if(testWin(EnemyWarshipList)) {
                if (country == 0) {
                    QMessageBox message(QMessageBox::NoIcon, "天佑大清，福祚绵长","");
                    message.setIconPixmap(QPixmap(":/images/images/others/QW.png"));
                    message.exec();
                } else {
                    QMessageBox message(QMessageBox::NoIcon, "天皇陛下万岁！！！","");
                    message.setIconPixmap(QPixmap(":/images/images/others/JW.png"));
                    message.exec();
                }
            }
            ComputerMove();
            if(testWin(warshipList)) {
                if (country == 0) {
                    QMessageBox message(QMessageBox::NoIcon, "什么，大清亡了？","");
                    message.setIconPixmap(QPixmap(":/images/images/others/QL.png"));
                    message.exec();
                } else {
                    QMessageBox message(QMessageBox::NoIcon, "落日","");
                    message.setIconPixmap(QPixmap(":/images/images/others/JL.png"));
                    message.exec();
                }
            }
        }
        while (warshipList[shipNumber].life<=0 && shipNumber<warshipList.size() && winOrNot==0) {
            shipNumber ++;
        }
        for (unsigned i=0;i<warshipList.size();i++) {
            if (warshipList[i].life<=0) {
                warshipList[i].positionY = 9999;
                warshipList[i].life=0;
            }
            warshipBlood[i]->setText(QString::number(warshipList[i].life)+"/100");
        }
        for (unsigned i=0;i<EnemyWarshipList.size();i++) {
            if (EnemyWarshipList[i].life<=0) {
                EnemyWarshipList[i].positionY = 9999;
                EnemyWarshipList[i].life=0;
            }
            enemyWarshipBlood[i]->setText(QString::number(EnemyWarshipList[i].life)+"/100");
        }
        testship = warshipList[shipNumber];
        gameInfo->setText("目前操作单位:"+testship.shipName);
        gameRole = 0;
    } else if(gameRole==0 && event->button()==Qt::RightButton) {
        clickPosCol = 9999;
        clickPosRow = 9999;
        gameRole = 1;
    } else if(gameRole==1 && event->button()==Qt::RightButton) {
        firePosCol = 9999;
        firePosRow = 9999;
        shipNumber ++;
        while (warshipList[shipNumber].life<=0 && shipNumber<warshipList.size()) {
            shipNumber ++;
        }
        if (shipNumber >= warshipList.size()) {
            shipNumber = 0;
            if(testWin(EnemyWarshipList)) {
                if (country == 0) {
                    QMessageBox message(QMessageBox::NoIcon, "天佑大清，福祚绵长","");
                    message.setIconPixmap(QPixmap(":/images/images/others/QW.png"));
                    message.exec();
                } else {
                    QMessageBox message(QMessageBox::NoIcon, "天皇陛下万岁！！！","");
                    message.setIconPixmap(QPixmap(":/images/images/others/JW.png"));
                    message.exec();
                }
            }
            ComputerMove();
            if(testWin(warshipList)) {
                if (country == 0) {
                    QMessageBox message(QMessageBox::NoIcon, "什么，大清亡了？","");
                    message.setIconPixmap(QPixmap(":/images/images/others/QL.png"));
                    message.exec();
                } else {
                    QMessageBox message(QMessageBox::NoIcon, "落日","");
                    message.setIconPixmap(QPixmap(":/images/images/others/JL.png"));
                    message.exec();
                }

            }
        }
        while (warshipList[shipNumber].life<=0 && shipNumber<warshipList.size() && winOrNot==0) {
            shipNumber ++;
        }
        for (unsigned i=0;i<warshipList.size();i++) {
            if (warshipList[i].life<=0) {
                warshipList[i].positionY = 9999;
                warshipList[i].life=0;
            }
            warshipBlood[i]->setText(QString::number(warshipList[i].life)+"/100");
        }
        for (unsigned i=0;i<EnemyWarshipList.size();i++) {
            if (EnemyWarshipList[i].life<=0) {
                EnemyWarshipList[i].positionY = 9999;
                EnemyWarshipList[i].life=0;
            }
            enemyWarshipBlood[i]->setText(QString::number(EnemyWarshipList[i].life)+"/100");
        }
        testship = warshipList[shipNumber];
        gameInfo->setText("目前操作单位:"+testship.shipName);
        gameRole = 0;
    }
}

void GameWidget::setWarshipList(vector<int> userSelect) {
    if (userSelect[0] > 0) {
        for (int i=0; i<userSelect[0]; i++) {
            warship newWarship;
            newWarship.shipName = "铁甲"+QString::number(i+1);
            newWarship.shipType = "class1Q";
            newWarship.shipL = 2;
            newWarship.shipH = 4;
            newWarship.shipSpeed = 2;
            newWarship.fireRange = 13;
            newWarship.firePower = 40;
            newWarship.life = 100;
            newWarship.visibleRange = 21;
            newWarship.operationStatus = true;
            newWarship.influence = true;
            warshipList.push_back(newWarship);
    }}
    if (userSelect[1] > 0) {
        for (int i=0; i<userSelect[1]; i++) {
            warship newWarship;
            newWarship.shipName = "装甲"+QString::number(i+1);
            newWarship.shipType = "class2Q";
            newWarship.shipL = 2;
            newWarship.shipH = 3;
            newWarship.shipSpeed = 3;
            newWarship.fireRange = 10;
            newWarship.firePower = 32;
            newWarship.life = 100;
            newWarship.visibleRange = 16;
            newWarship.operationStatus = true;
            newWarship.influence = true;
            warshipList.push_back(newWarship);
    }}
    if (userSelect[2] > 0) {
        for (int i=0; i<userSelect[2]; i++) {
            warship newWarship;
            newWarship.shipName = "穹甲"+QString::number(i+1);
            newWarship.shipType = "class3Q";
            newWarship.shipL = 1;
            newWarship.shipH = 3;
            newWarship.shipSpeed = 4;
            newWarship.fireRange = 10;
            newWarship.firePower = 28;
            newWarship.life = 100;
            newWarship.visibleRange = 16;
            newWarship.operationStatus = true;
            newWarship.influence = true;
            warshipList.push_back(newWarship);
    }}
    if (userSelect[3] > 0) {
        for (int i=0; i<userSelect[3]; i++) {
            warship newWarship;
            newWarship.shipName = "钢壳"+QString::number(i+1);
            newWarship.shipType = "class4Q";
            newWarship.shipL = 1;
            newWarship.shipH = 2;
            newWarship.shipSpeed = 6;
            newWarship.fireRange = 7;
            newWarship.firePower = 14;
            newWarship.life = 100;
            newWarship.visibleRange = 13;
            newWarship.operationStatus = true;
            newWarship.influence = true;
            warshipList.push_back(newWarship);
    }}
    if (userSelect[4] > 0) {
        for (int i=0; i<userSelect[4]; i++) {
            warship newWarship;
            newWarship.shipName = "木壳"+QString::number(i+1);
            newWarship.shipType = "class5Q";
            newWarship.shipL = 0;
            newWarship.shipH = 1;
            newWarship.shipSpeed = 6;
            newWarship.fireRange = 7;
            newWarship.firePower = 12;
            newWarship.life = 100;
            newWarship.visibleRange = 13;
            newWarship.operationStatus = true;
            newWarship.influence = true;
            warshipList.push_back(newWarship);
    }}
}

void GameWidget::setInitialPosition() {
    if (warshipList.size() > 0) {
        warshipList[0].positionX = 25;
        warshipList[0].positionY = 60;
    }
    if (warshipList.size() > 1) {
        for (unsigned i = 1; i < warshipList.size(); i++) {
            warshipList[i].positionX = warshipList[0].positionX + i * 10;
            warshipList[i].positionY = warshipList[0].positionY;
}}}

vector<int> GameWidget::setEnemyCombination() {
    int DecisionLottery;
    vector<vector<int> > CombinationCollection;
    int array_1[5] = {0,1,1,3,2};int array_2[5] = {0,1,2,1,1};int array_3[5] = {1,1,0,1,1};int array_4[5] = {1,0,0,3,2};
    vector<int> lineup_1(array_1,array_1+5);vector<int> lineup_2(array_2,array_2+5);vector<int> lineup_3(array_3,array_3+5);vector<int> lineup_4(array_4,array_4+5);
    CombinationCollection.push_back(lineup_1);CombinationCollection.push_back(lineup_2);CombinationCollection.push_back(lineup_3);CombinationCollection.push_back(lineup_4);
    DecisionLottery = rand() % CombinationCollection.size();
    return CombinationCollection[DecisionLottery];
}

void GameWidget::setEnemyWarshipList(vector<int> Parameters) {
    if (Parameters[0] > 0) {
        for (int i = 0; i < Parameters[0]; i++) {
            warship newWarship;
            newWarship.shipName = "铁甲"+QString::number(i+1);
            newWarship.shipType = "class1J";
            newWarship.shipL = 2;
            newWarship.shipH = 4;
            newWarship.shipSpeed = 2;
            newWarship.fireRange = 13;
            newWarship.firePower = 35;
            newWarship.life = 100;
            newWarship.visibleRange = 23;
            newWarship.operationStatus = true;
            EnemyWarshipList.push_back(newWarship);
        }
    }
    if (Parameters[1] > 0) {
        for (int i = 0; i < Parameters[1]; i++) {
            warship newWarship;
            newWarship.shipName = "装甲"+QString::number(i+1);
            newWarship.shipType = "class2J";
            newWarship.shipL = 2;
            newWarship.shipH = 3;
            newWarship.shipSpeed = 3;
            newWarship.fireRange = 10;
            newWarship.firePower = 27;
            newWarship.life = 100;
            newWarship.visibleRange = 16;
            newWarship.operationStatus = true;
            EnemyWarshipList.push_back(newWarship);
        }
    }
    if (Parameters[2] > 0) {
        for (int i = 0; i < Parameters[2]; i++) {
            warship newWarship;
            newWarship.shipName = "防巡"+QString::number(i+1);
            newWarship.shipType = "class3J";
            newWarship.shipL = 1;
            newWarship.shipH = 3;
            newWarship.shipSpeed = 4;
            newWarship.fireRange = 10;
            newWarship.firePower = 22;
            newWarship.life = 100;
            newWarship.visibleRange = 19;
            newWarship.operationStatus = true;
            EnemyWarshipList.push_back(newWarship);
        }
    }
    if (Parameters[3] > 0) {
        for (int i = 0; i < Parameters[3]; i++) {
            warship newWarship;
            newWarship.shipName = "炮舰"+QString::number(i+1);
            newWarship.shipType = "class4J";
            newWarship.shipL = 1;
            newWarship.shipH = 2;
            newWarship.shipSpeed = 3;
            newWarship.fireRange = 12;
            newWarship.firePower = 13;
            newWarship.life = 100;
            newWarship.visibleRange = 16;
            newWarship.operationStatus = true;
            EnemyWarshipList.push_back(newWarship);
        }
    }
    if (Parameters[4] > 0) {
        for (int i = 0; i < Parameters[4]; i++) {
            warship newWarship;
            newWarship.shipName = "辅巡"+QString::number(i+1);
            newWarship.shipType = "class5J";
            newWarship.shipL = 0;
            newWarship.shipH = 1;
            newWarship.shipSpeed = 4;
            newWarship.fireRange = 8;
            newWarship.firePower = 16;
            newWarship.life = 100;
            newWarship.visibleRange = 19;
            newWarship.operationStatus = true;
            EnemyWarshipList.push_back(newWarship);
        }
    }
}

void GameWidget::setEnemyInitialPosition() {
    if (EnemyWarshipList.size() > 0) {
        EnemyWarshipList[0].positionX = 25;
        EnemyWarshipList[0].positionY = 10;
    }
    if (EnemyWarshipList.size() > 1) {
        for (unsigned i = 1; i < EnemyWarshipList.size(); i++) {
            EnemyWarshipList[i].positionX = EnemyWarshipList[0].positionX + i * 10;
            EnemyWarshipList[i].positionY = EnemyWarshipList[0].positionY;
}}}

bool GameWidget::judgeCover(int x, int y) {
    int passnumber = 0;
    for (warship othership: warshipList) {
        if (othership.positionX==warshipList[shipNumber].positionX || //判断为自己
            ((x+warshipList[shipNumber].shipL<othership.positionX || x>othership.positionX+othership.shipL) ||
             (y>othership.positionY+othership.shipH || y+warshipList[shipNumber].shipH<othership.positionY))) {
            passnumber = 1;
        } else {
            return false;
        }
    }
    for (warship othership: EnemyWarshipList) {
        if (((x+warshipList[shipNumber].shipL<othership.positionX || x>othership.positionX+othership.shipL) ||
             (y>othership.positionY+othership.shipH || y+warshipList[shipNumber].shipH<othership.positionY))) {
            passnumber = 1;
        } else {
            return false;
        }
    }
    return true;
}

vector<tuple<int,int,int> > GameWidget::GenerateOpponentInfo(vector<warship> warshipList) {
    vector<tuple<int,int,int> > OpponentInfo;
    for (unsigned int i=0;i<warshipList.size();i++) {
        tuple<int,int,int> Infotuple = make_tuple(warshipList[i].life,warshipList[i].positionX,warshipList[i].positionY);
        OpponentInfo.push_back(Infotuple);
    }
    return OpponentInfo;
}

vector<vector<int> > GameWidget::GenerateSingleInfluenceMap(warship TargetWarship){
    vector<vector<int>> singleInfluenceMap;
    for (int i=0;i<ROW;i++) {
        vector<int> line;
        singleInfluenceMap.push_back(line);
        for (int j=0;j<COL;j++) {
            if ((j>=TargetWarship.positionX-TargetWarship.fireRange-TargetWarship.shipSpeed) &&
                (j<TargetWarship.positionX+TargetWarship.fireRange+TargetWarship.shipSpeed+TargetWarship.shipL) &&
                (i>=TargetWarship.positionY-TargetWarship.fireRange-TargetWarship.shipSpeed) &&
                (i<TargetWarship.positionY+TargetWarship.fireRange+TargetWarship.shipSpeed+TargetWarship.shipH)) {
                singleInfluenceMap[i].push_back(TargetWarship.firePower);
            } else {
                singleInfluenceMap[i].push_back(0);
            }
        }
    }
    return singleInfluenceMap;
}

vector<vector<int> > GameWidget::GenerateOverallInfluenceMap(vector<warship> targetWarshipList) {
    vector<vector<int> > OverallInfluenceMap;
    for (int i=0;i<ROW;i++) {
        vector<int> line;
        OverallInfluenceMap.push_back(line);
        for (int j=0;j<COL;j++) {
                OverallInfluenceMap[i].push_back(0);
        }
    }
    for (unsigned i=0;i<targetWarshipList.size();i++) {
        if (targetWarshipList[i].life > 0 && targetWarshipList[i].operationStatus == true) {
            vector<vector<int> > singleInfluenceMap = GenerateSingleInfluenceMap(targetWarshipList[i]);
            for (unsigned j=0;j<ROW;j++) {
                for (unsigned k=0;k<COL;k++) {
                    OverallInfluenceMap[j][k] += singleInfluenceMap[j][k];
                }
            }
        }

    }
    return OverallInfluenceMap;
}

bool GameWidget::inAttackRange(warship attacker,warship receiver) {
    vector<vector<int> > attackerInfluence = GenerateSingleInfluenceMap(attacker);
    for(int i=receiver.positionY;i<=receiver.positionY+receiver.shipH;i++) {
        for(int j=receiver.positionX;j<=receiver.positionX+receiver.shipL;j++) {
            if (attackerInfluence[i][j] > 0) return true;
        }
    }
    return false;
}

bool GameWidget::inDirectAttackRange(int x,int y,warship attacker,warship receiver) {
    if ((receiver.positionX+receiver.shipL>x-attacker.fireRange) &&
        (receiver.positionX<x+attacker.shipL+attacker.fireRange) &&
        (receiver.positionY+receiver.shipH>y-attacker.fireRange) &&
        (receiver.positionY<y+attacker.shipH+attacker.fireRange)) {
        return true;
    }
    return false;
}

bool GameWidget::inReachRange(int x, int y, warship myship) {
    if((x>=myship.positionX-myship.shipSpeed) && (x<=myship.positionX+myship.shipSpeed) &&
       (y>=myship.positionY-myship.shipSpeed) && (y<=myship.positionY+myship.shipSpeed)) {
        return true;
    }
    return false;
}

bool GameWidget::JudgeCollision(int x,int y,warship myship) {
    int passnumber = 0;
    for (warship othership: warshipList) {
        if (((x+myship.shipL<othership.positionX || x>othership.positionX+othership.shipL) ||
             (y>othership.positionY+othership.shipH || y+myship.shipH<othership.positionY))) {
            passnumber = 1;
        } else {
            return false;
        }
    }
    for (warship othership: EnemyWarshipList) {
        if (((x+myship.shipL<othership.positionX || x>othership.positionX+othership.shipL) ||
             (y>othership.positionY+othership.shipH || y+myship.shipH<othership.positionY))) {
            passnumber = 1;
        } else {
            return false;
        }
    }
    return true;
}

void GameWidget::SetComputerStage() {
    for (unsigned i=0;i<EnemyWarshipList.size();i++) {
        if (EnemyWarshipList[i].life>0) {
            EnemyWarshipList[i].operationStatus = true;
        }
    }
}

void GameWidget::ConcentrateMode() {
    vector<tuple<int,int,int>> OpponentInfo = GenerateOpponentInfo(warshipList);
    vector<vector<int>> SelfInfluenceMap = GenerateOverallInfluenceMap(EnemyWarshipList);
    while (concentrateControl<OpponentInfo.size()) {
        if (get<0> (OpponentInfo[concentrateControl])>0) {
            if (get<0> (OpponentInfo[concentrateControl]) <= SelfInfluenceMap[get<2> (OpponentInfo[concentrateControl])][get<1> (OpponentInfo[concentrateControl])]) {
                vector<warship> possibleOption;
                for (unsigned j=0;j<EnemyWarshipList.size();j++) {
                    if ((EnemyWarshipList[j].life>0) && (EnemyWarshipList[j].operationStatus == true)
                            && (inAttackRange(EnemyWarshipList[j],warshipList[concentrateControl]))) {
                        possibleOption.push_back(EnemyWarshipList[j]);
                    }
                }
                int taskCarrier =  rand() % possibleOption.size();
                vector<int> x_coordinate;
                vector<int> y_coordinate;
                for (int j=0;j<ROW;j++) {
                    for (int k=0;k<COL;k++) {
                        if ((inDirectAttackRange(k,j,possibleOption[taskCarrier],warshipList[concentrateControl])) && (JudgeCollision(k,j,possibleOption[taskCarrier]))) {
                            x_coordinate.push_back(k);
                            y_coordinate.push_back(j);
                        }
                    }
                }
                int coordinate_decision = rand() % x_coordinate.size();
                EnemyWarshipList[judgeSameShip(possibleOption[taskCarrier],EnemyWarshipList)].positionX = x_coordinate[coordinate_decision];
                EnemyWarshipList[judgeSameShip(possibleOption[taskCarrier],EnemyWarshipList)].positionY = y_coordinate[coordinate_decision];
                warshipList[concentrateControl].life -= possibleOption[taskCarrier].firePower;
                EnemyWarshipList[judgeSameShip(possibleOption[taskCarrier],EnemyWarshipList)].operationStatus = false;
                break;
            }
        }
    concentrateControl += 1;
    }
}

void GameWidget::RandomMode() {
    vector<warship> RestShip;
    vector<warship> RemainingTarget;
    for (unsigned i=0;i<EnemyWarshipList.size();i++) {
        if (EnemyWarshipList[i].operationStatus == true) {
            RestShip.push_back(EnemyWarshipList[i]);
        }
    }
    for (unsigned i=0;i<warshipList.size();i++) {
        if (warshipList[i].life > 0) {
            RemainingTarget.push_back(warshipList[i]);
        }
    }
    for (unsigned i=0;i<RestShip.size();i++) {
        vector<vector<int> > singleInfluencemap = GenerateSingleInfluenceMap(RestShip[i]);
        vector<warship> possibleTarget;
        for (unsigned j=0;j<RemainingTarget.size();j++) {
            if (singleInfluencemap[RemainingTarget[j].positionY][RemainingTarget[j].positionX]>0) {
                possibleTarget.push_back(RemainingTarget[j]);
            }
        }
        if (possibleTarget.size() != 0) {
            int target = rand() % possibleTarget.size();
            vector<int> x_coordinate;
            vector<int> y_coordinate;
            for (int j=0;j<ROW;j++) {
                for (int k=0;k<COL;k++) {
                    if ((inDirectAttackRange(k,j,RestShip[i],possibleTarget[target])) && (JudgeCollision(k,j,RestShip[i])) &&
                        (inReachRange(k,j,RestShip[i]))) {
                        x_coordinate.push_back(k);
                        y_coordinate.push_back(j);
                    }
                }
            }
            int coordinate_decision = rand() % x_coordinate.size();
            EnemyWarshipList[judgeSameShip(RestShip[i],EnemyWarshipList)].positionX = x_coordinate[coordinate_decision];
            EnemyWarshipList[judgeSameShip(RestShip[i],EnemyWarshipList)].positionY = y_coordinate[coordinate_decision];
            warshipList[judgeSameShip(possibleTarget[target],warshipList)].life -= RestShip[i].firePower;
            EnemyWarshipList[judgeSameShip(RestShip[i],EnemyWarshipList)].operationStatus = false;
        } else {
            vector<int> x_coordinate;
            vector<int> y_coordinate;
            switch (country) {
            case 0:
                for (int j=10+RestShip[i].shipSpeed;j<40;j++) {
                    for (int k=0;k<COL;k++) {
                        if (inReachRange(k,j,RestShip[i]) && JudgeCollision(k,j,RestShip[i]) && (k != RestShip[i].positionX) && (j != RestShip[i].positionY)) {
                            x_coordinate.push_back(k);
                            y_coordinate.push_back(j);
                        }
                    }
                }
                break;
            case 1:
                for (int j=30;j<61-RestShip[i].shipSpeed;j++) {
                    for (int k=0;k<COL;k++) {
                        if (inReachRange(k,j,RestShip[i]) && JudgeCollision(k,j,RestShip[i]) && (k != RestShip[i].positionX) && (j != RestShip[i].positionY)) {
                            x_coordinate.push_back(k);
                            y_coordinate.push_back(j);
                        }
                    }
                }
                break;
            default:
                break;
            }
            int coordinate_decision = rand() % x_coordinate.size();
            EnemyWarshipList[judgeSameShip(RestShip[i],EnemyWarshipList)].positionX = x_coordinate[coordinate_decision];
            EnemyWarshipList[judgeSameShip(RestShip[i],EnemyWarshipList)].positionY = y_coordinate[coordinate_decision];
            EnemyWarshipList[judgeSameShip(RestShip[i],EnemyWarshipList)].operationStatus = false;
        }

    }
}

void GameWidget::ComputerMove() {
    SetComputerStage();
    vector<tuple<int,int,int> > OpponentInfo = GenerateOpponentInfo(warshipList);
    while (concentrateControl != OpponentInfo.size()) {
        ConcentrateMode();
    }
    RandomMode();
}

int GameWidget::judgeSameShip(warship ship, vector<warship> shipList) {
    for(unsigned i=0;i<shipList.size();i++) {
        if (ship.shipName == shipList[i].shipName) return i;
    }
    return -1;
}

bool GameWidget::testWin(vector<warship> shipList) {
    for (warship i: shipList) {
        if (i.life>0)
            return false;
    }
    winOrNot = 1;
    return true;
}

void GameWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if (country == 0) {
        painter.drawPixmap(1300,55,215,150,QPixmap(":/images/images/others/QingFlag.jpg"));
        painter.drawPixmap(1300,515,215,150,QPixmap(":/images/images/others/JapanFlag.jpg"));
    } else {
        painter.drawPixmap(1300,55,215,150,QPixmap(":/images/images/others/JapanFlag.jpg"));
        painter.drawPixmap(1300,515,215,150,QPixmap(":/images/images/others/QingFlag.jpg"));
    }
    //绘制血量条
    for (unsigned i=0;i<warshipList.size();i++) {
        if (warshipList[i].life>0) {
            painter.setPen(QColor(0,255,0));
            painter.setBrush(QColor(0,255,0));
            painter.drawRect(1290,250+i*25,warshipList[i].life*2,10);
            painter.setPen(QColor(255,0,0));
            painter.setBrush(QColor(255,0,0));
            painter.drawRect(1290+warshipList[i].life*2,250+i*25,200-warshipList[i].life*2,10);
        }
    }
    for (unsigned i=0;i<EnemyWarshipList.size();i++) {
        if (EnemyWarshipList[i].life>0) {
            painter.setPen(QColor(0,255,0));
            painter.setBrush(QColor(0,255,0));
            painter.drawRect(1290,710+i*25,EnemyWarshipList[i].life*2,10);
            painter.setPen(QColor(255,0,0));
            painter.setBrush(QColor(255,0,0));
            painter.drawRect(1290+EnemyWarshipList[i].life*2,710+i*25,200-EnemyWarshipList[i].life*2,10);
        }
    }

    //画方格
    for(int i=0;i<ROW*10;i+=10) {
        for(int j=0;j<COL*10;j+=10) {
            if (i<=(testship.positionY+testship.shipH)*10 && j<=(testship.positionX+testship.shipL)*10
                       && i>=testship.positionY*10 && j>=testship.positionX*10) {
                painter.setPen(QColor(255,160,90));
                painter.setBrush(QColor(255,160,90));
                painter.drawRect(j,i,10,10);
            } else if (i<=(clickPosRow+testship.shipH)*10 && j<=(clickPosCol+testship.shipL)*10
                       && i>=clickPosRow*10 && j>=clickPosCol*10){
                painter.setPen(QColor(128,138,135));
                painter.setBrush(QColor(128,138,135));
                painter.drawRect(j,i,10,10);
            } else if (i==firePosRow*10 && j == firePosCol*10){
                painter.setPen(QColor(255,0,0));
                painter.setBrush(QColor(255,0,0));
                painter.drawRect(j,i,10,10);
            } else if (i<=(testship2.positionY+testship2.shipH)*10 && j<=(testship2.positionX+testship2.shipL)*10 //敌舰
                  && i>=testship2.positionY*10 && j>=testship2.positionX*10) {
           painter.setPen(QColor(201,0,87));
           painter.setBrush(QColor(201,0,87));
           painter.drawRect(j,i,10,10);
            }  else if (gameRole==0 && j>=10*(testship.positionX-testship.shipSpeed) &&
                       j<=10*(testship.positionX+testship.shipSpeed+testship.shipL) &&
                       i>=10*(testship.positionY-testship.shipSpeed) && i<=10*(testship.positionY+testship.shipSpeed+testship.shipH) &&
                       (i>(testship.positionY+testship.shipH)*10 || j>(testship.positionX+testship.shipL)*10 ||
                       i<testship.positionY*10 || j<testship.positionX*10)) {
                  painter.setPen(QColor(30,144,255));
                  painter.setBrush(QColor(30,144,255));
                  painter.drawRect(j,i,10,10);
              } else if (gameRole==1 && j>=10*(testship.positionX-testship.fireRange) && //绘制火力范围
                         j<=10*(testship.positionX+testship.fireRange+testship.shipL) &&
                         i>=10*(testship.positionY-testship.fireRange) && i<=10*(testship.positionY+testship.fireRange+testship.shipH) &&
                         (i>(testship.positionY+testship.shipH)*10 || j>(testship.positionX+testship.shipL)*10 ||
                         i<testship.positionY*10 || j<testship.positionX*10)) {
                    painter.setPen(QColor(221,160,221));
                    painter.setBrush(QColor(221,160,221));
                    painter.drawRect(j,i,10,10);
              } else {
                painter.setPen(QColor(65,105,255));
                painter.setBrush(QColor(65,105,255));
                painter.drawRect(j,i,10,10);
            }
            //绘制能见范围
            if (sightRange[i/10][j/10]==0) {
                painter.setPen(QColor(8,46,84));
                painter.setBrush(QColor(8,46,84));
                painter.drawRect(j,i,10,10);
            }
        }
    }

    //先绘制敌舰
    for (unsigned n=0;n<EnemyWarshipList.size();n++) {
        if (EnemyWarshipList[n].life>0) {
        int i = EnemyWarshipList[n].positionY*10;
        int j = EnemyWarshipList[n].positionX*10;
        unsigned k = EnemyWarshipList[n].positionX;
        unsigned l = EnemyWarshipList[n].positionY;
        if (EnemyWarshipList[n].shipType == "class1"+enemyID) {
            if(sightRange[l][k]==1) painter.drawPixmap(j,i,10,10,QPixmap(":/images/images/warshipPixel/1_01"+enemyID+".gif"));
            if(sightRange[l][k+1]==1) painter.drawPixmap(j+10,i,10,10,QPixmap(":/images/images/warshipPixel/1_02"+enemyID+".gif"));
            if(sightRange[l][k+2]==1) painter.drawPixmap(j+20,i,10,10,QPixmap(":/images/images/warshipPixel/1_03"+enemyID+".gif"));
            if(sightRange[l+1][k]==1) painter.drawPixmap(j,i+10,10,10,QPixmap(":/images/images/warshipPixel/1_04"+enemyID+".gif"));
            if(sightRange[l+1][k+1]==1) painter.drawPixmap(j+10,i+10,10,10,QPixmap(":/images/images/warshipPixel/1_05"+enemyID+".gif"));
            if(sightRange[l+1][k+2]==1) painter.drawPixmap(j+20,i+10,10,10,QPixmap(":/images/images/warshipPixel/1_06"+enemyID+".gif"));
            if(sightRange[l+2][k]==1)painter.drawPixmap(j,i+20,10,10,QPixmap(":/images/images/warshipPixel/1_07"+enemyID+".gif"));
            if(sightRange[l+2][k+1]==1) painter.drawPixmap(j+10,i+20,10,10,QPixmap(":/images/images/warshipPixel/1_08"+enemyID+".gif"));
            if(sightRange[l+2][k+2]==1) painter.drawPixmap(j+20,i+20,10,10,QPixmap(":/images/images/warshipPixel/1_09"+enemyID+".gif"));
            if(sightRange[l+3][k]==1) painter.drawPixmap(j,i+30,10,10,QPixmap(":/images/images/warshipPixel/1_10"+enemyID+".gif"));
            if(sightRange[l+3][k+1]==1) painter.drawPixmap(j+10,i+30,10,10,QPixmap(":/images/images/warshipPixel/1_11"+enemyID+".gif"));
            if(sightRange[l+3][k+2]==1) painter.drawPixmap(j+20,i+30,10,10,QPixmap(":/images/images/warshipPixel/1_12"+enemyID+".gif"));
            if(sightRange[l+4][k]==1) painter.drawPixmap(j,i+40,10,10,QPixmap(":/images/images/warshipPixel/1_13"+enemyID+".gif"));
            if(sightRange[l+4][k+1]==1) painter.drawPixmap(j+10,i+40,10,10,QPixmap(":/images/images/warshipPixel/1_14"+enemyID+".gif"));
            if(sightRange[l+4][k+2]==1) painter.drawPixmap(j+20,i+40,10,10,QPixmap(":/images/images/warshipPixel/1_15"+enemyID+".gif"));
        } else if (EnemyWarshipList[n].shipType == "class2"+enemyID) {
            if(sightRange[l][k]==1) painter.drawPixmap(j,i,10,10,QPixmap(":/images/images/warshipPixel/2_01"+enemyID+".gif"));
            if(sightRange[l][k+1]==1) painter.drawPixmap(j+10,i,10,10,QPixmap(":/images/images/warshipPixel/2_02"+enemyID+".gif"));
            if(sightRange[l][k+2]==1) painter.drawPixmap(j+20,i,10,10,QPixmap(":/images/images/warshipPixel/2_03"+enemyID+".gif"));
            if(sightRange[l+1][k]==1) painter.drawPixmap(j,i+10,10,10,QPixmap(":/images/images/warshipPixel/2_04"+enemyID+".gif"));
            if(sightRange[l+1][k+1]==1) painter.drawPixmap(j+10,i+10,10,10,QPixmap(":/images/images/warshipPixel/2_05"+enemyID+".gif"));
            if(sightRange[l+1][k+2]==1) painter.drawPixmap(j+20,i+10,10,10,QPixmap(":/images/images/warshipPixel/2_06"+enemyID+".gif"));
            if(sightRange[l+2][k]==1) painter.drawPixmap(j,i+20,10,10,QPixmap(":/images/images/warshipPixel/2_07"+enemyID+".gif"));
            if(sightRange[l+2][k+1]==1) painter.drawPixmap(j+10,i+20,10,10,QPixmap(":/images/images/warshipPixel/2_08"+enemyID+".gif"));
            if(sightRange[l+2][k+2]==1) painter.drawPixmap(j+20,i+20,10,10,QPixmap(":/images/images/warshipPixel/2_09"+enemyID+".gif"));
            if(sightRange[l+3][k]==1) painter.drawPixmap(j,i+30,10,10,QPixmap(":/images/images/warshipPixel/2_10"+enemyID+".gif"));
            if(sightRange[l+3][k+1]==1) painter.drawPixmap(j+10,i+30,10,10,QPixmap(":/images/images/warshipPixel/2_11"+enemyID+".gif"));
            if(sightRange[l+3][k+2]==1) painter.drawPixmap(j+20,i+30,10,10,QPixmap(":/images/images/warshipPixel/2_12"+enemyID+".gif"));
        } else if (EnemyWarshipList[n].shipType == "class3"+enemyID) {
            if(sightRange[l][k]==1) painter.drawPixmap(j,i,10,10,QPixmap(":/images/images/warshipPixel/3_01"+enemyID+".gif"));
            if(sightRange[l][k+1]==1) painter.drawPixmap(j+10,i,10,10,QPixmap(":/images/images/warshipPixel/3_02"+enemyID+".gif"));
            if(sightRange[l+1][k]==1) painter.drawPixmap(j,i+10,10,10,QPixmap(":/images/images/warshipPixel/3_03"+enemyID+".gif"));
            if(sightRange[l+1][k+1]==1) painter.drawPixmap(j+10,i+10,10,10,QPixmap(":/images/images/warshipPixel/3_04"+enemyID+".gif"));
            if(sightRange[l+2][k]==1) painter.drawPixmap(j,i+20,10,10,QPixmap(":/images/images/warshipPixel/3_05"+enemyID+".gif"));
            if(sightRange[l+2][k+1]==1) painter.drawPixmap(j+10,i+20,10,10,QPixmap(":/images/images/warshipPixel/3_06"+enemyID+".gif"));
            if(sightRange[l+3][k]==1) painter.drawPixmap(j,i+30,10,10,QPixmap(":/images/images/warshipPixel/3_07"+enemyID+".gif"));
            if(sightRange[l+3][k+1]==1) painter.drawPixmap(j+10,i+30,10,10,QPixmap(":/images/images/warshipPixel/3_08"+enemyID+".gif"));
        } else if (EnemyWarshipList[n].shipType == "class4"+enemyID) {
            if(sightRange[l][k]==1) painter.drawPixmap(j,i,10,10,QPixmap(":/images/images/warshipPixel/4_01"+enemyID+".gif"));
            if(sightRange[l][k+1]==1) painter.drawPixmap(j+10,i,10,10,QPixmap(":/images/images/warshipPixel/4_02"+enemyID+".gif"));
            if(sightRange[l+1][k]==1) painter.drawPixmap(j,i+10,10,10,QPixmap(":/images/images/warshipPixel/4_03"+enemyID+".gif"));
            if(sightRange[l+1][k+1]==1) painter.drawPixmap(j+10,i+10,10,10,QPixmap(":/images/images/warshipPixel/4_04"+enemyID+".gif"));
            if(sightRange[l+2][k]==1) painter.drawPixmap(j,i+20,10,10,QPixmap(":/images/images/warshipPixel/4_05"+enemyID+".gif"));
            if(sightRange[l+2][k+1]==1) painter.drawPixmap(j+10,i+20,10,10,QPixmap(":/images/images/warshipPixel/4_06"+enemyID+".gif"));
        } else if (EnemyWarshipList[n].shipType == "class5"+enemyID) {
            if(sightRange[l][k]==1) painter.drawPixmap(j,i,10,10,QPixmap(":/images/images/warshipPixel/5_01"+enemyID+".gif"));
            if(sightRange[l+1][k]==1) painter.drawPixmap(j,i+10,10,10,QPixmap(":/images/images/warshipPixel/5_02"+enemyID+".gif"));
        }
    }}

    //绘制舰船图标
    for (unsigned n=0;n<warshipList.size();n++) {
        int i = warshipList[n].positionY*10;
        int j = warshipList[n].positionX*10;
        if (warshipList[n].shipType == "class1"+countryID) {
            painter.drawPixmap(j,i,10,10,QPixmap(":/images/images/warshipPixel/1_01"+countryID+".gif"));
            painter.drawPixmap(j+10,i,10,10,QPixmap(":/images/images/warshipPixel/1_02"+countryID+".gif"));
            painter.drawPixmap(j+20,i,10,10,QPixmap(":/images/images/warshipPixel/1_03"+countryID+".gif"));
            painter.drawPixmap(j,i+10,10,10,QPixmap(":/images/images/warshipPixel/1_04"+countryID+".gif"));
            painter.drawPixmap(j+10,i+10,10,10,QPixmap(":/images/images/warshipPixel/1_05"+countryID+".gif"));
            painter.drawPixmap(j+20,i+10,10,10,QPixmap(":/images/images/warshipPixel/1_06"+countryID+".gif"));
            painter.drawPixmap(j,i+20,10,10,QPixmap(":/images/images/warshipPixel/1_07"+countryID+".gif"));
            painter.drawPixmap(j+10,i+20,10,10,QPixmap(":/images/images/warshipPixel/1_08"+countryID+".gif"));
            painter.drawPixmap(j+20,i+20,10,10,QPixmap(":/images/images/warshipPixel/1_09"+countryID+".gif"));
            painter.drawPixmap(j,i+30,10,10,QPixmap(":/images/images/warshipPixel/1_10"+countryID+".gif"));
            painter.drawPixmap(j+10,i+30,10,10,QPixmap(":/images/images/warshipPixel/1_11"+countryID+".gif"));
            painter.drawPixmap(j+20,i+30,10,10,QPixmap(":/images/images/warshipPixel/1_12"+countryID+".gif"));
            painter.drawPixmap(j,i+40,10,10,QPixmap(":/images/images/warshipPixel/1_13"+countryID+".gif"));
            painter.drawPixmap(j+10,i+40,10,10,QPixmap(":/images/images/warshipPixel/1_14"+countryID+".gif"));
            painter.drawPixmap(j+20,i+40,10,10,QPixmap(":/images/images/warshipPixel/1_15"+countryID+".gif"));
        } else if (warshipList[n].shipType == "class2"+countryID) {
            painter.drawPixmap(j,i,10,10,QPixmap(":/images/images/warshipPixel/2_01"+countryID+".gif"));
            painter.drawPixmap(j+10,i,10,10,QPixmap(":/images/images/warshipPixel/2_02"+countryID+".gif"));
            painter.drawPixmap(j+20,i,10,10,QPixmap(":/images/images/warshipPixel/2_03"+countryID+".gif"));
            painter.drawPixmap(j,i+10,10,10,QPixmap(":/images/images/warshipPixel/2_04"+countryID+".gif"));
            painter.drawPixmap(j+10,i+10,10,10,QPixmap(":/images/images/warshipPixel/2_05"+countryID+".gif"));
            painter.drawPixmap(j+20,i+10,10,10,QPixmap(":/images/images/warshipPixel/2_06"+countryID+".gif"));
            painter.drawPixmap(j,i+20,10,10,QPixmap(":/images/images/warshipPixel/2_07"+countryID+".gif"));
            painter.drawPixmap(j+10,i+20,10,10,QPixmap(":/images/images/warshipPixel/2_08"+countryID+".gif"));
            painter.drawPixmap(j+20,i+20,10,10,QPixmap(":/images/images/warshipPixel/2_09"+countryID+".gif"));
            painter.drawPixmap(j,i+30,10,10,QPixmap(":/images/images/warshipPixel/2_10"+countryID+".gif"));
            painter.drawPixmap(j+10,i+30,10,10,QPixmap(":/images/images/warshipPixel/2_11"+countryID+".gif"));
            painter.drawPixmap(j+20,i+30,10,10,QPixmap(":/images/images/warshipPixel/2_12"+countryID+".gif"));
        } else if (warshipList[n].shipType == "class3"+countryID) {
            painter.drawPixmap(j,i,10,10,QPixmap(":/images/images/warshipPixel/3_01"+countryID+".gif"));
            painter.drawPixmap(j+10,i,10,10,QPixmap(":/images/images/warshipPixel/3_02"+countryID+".gif"));
            painter.drawPixmap(j,i+10,10,10,QPixmap(":/images/images/warshipPixel/3_03"+countryID+".gif"));
            painter.drawPixmap(j+10,i+10,10,10,QPixmap(":/images/images/warshipPixel/3_04"+countryID+".gif"));
            painter.drawPixmap(j,i+20,10,10,QPixmap(":/images/images/warshipPixel/3_05"+countryID+".gif"));
            painter.drawPixmap(j+10,i+20,10,10,QPixmap(":/images/images/warshipPixel/3_06"+countryID+".gif"));
            painter.drawPixmap(j,i+30,10,10,QPixmap(":/images/images/warshipPixel/3_07"+countryID+".gif"));
            painter.drawPixmap(j+10,i+30,10,10,QPixmap(":/images/images/warshipPixel/3_08"+countryID+".gif"));
        } else if (warshipList[n].shipType == "class4"+countryID) {
            painter.drawPixmap(j,i,10,10,QPixmap(":/images/images/warshipPixel/4_01"+countryID+".gif"));
            painter.drawPixmap(j+10,i,10,10,QPixmap(":/images/images/warshipPixel/4_02"+countryID+".gif"));
            painter.drawPixmap(j,i+10,10,10,QPixmap(":/images/images/warshipPixel/4_03"+countryID+".gif"));
            painter.drawPixmap(j+10,i+10,10,10,QPixmap(":/images/images/warshipPixel/4_04"+countryID+".gif"));
            painter.drawPixmap(j,i+20,10,10,QPixmap(":/images/images/warshipPixel/4_05"+countryID+".gif"));
            painter.drawPixmap(j+10,i+20,10,10,QPixmap(":/images/images/warshipPixel/4_06"+countryID+".gif"));
        } else if (warshipList[n].shipType == "class5"+countryID) {
            painter.drawPixmap(j,i,10,10,QPixmap(":/images/images/warshipPixel/5_01"+countryID+".gif"));
            painter.drawPixmap(j,i+10,10,10,QPixmap(":/images/images/warshipPixel/5_02"+countryID+".gif"));
        }
    }
    if(winOrNot == 1) {
        if (testWin(warshipList) && country==0) {
            painter.drawPixmap(0,0,width(),height(),QPixmap(":/images/images/others/JQ2.png"));
        } else if (testWin(warshipList) && country==1) {
            painter.drawPixmap(0,0,width(),height(),QPixmap(":/images/images/others/JQ1.png"));
        } else if (testWin(EnemyWarshipList) && country==0) {
            painter.drawPixmap(0,0,width(),height(),QPixmap(":/images/images/others/JQ1.png"));
        } else if (testWin(EnemyWarshipList) && country==1) {
            painter.drawPixmap(0,0,width(),height(),QPixmap(":/images/images/others/JQ2.png"));
        }
    }
}

void GameWidget::setSightRange() {
    for (warship s: warshipList) {
        for(int x=s.positionX-s.visibleRange;x<=s.positionX+s.visibleRange;x++) {
            for (int y=s.positionY-s.visibleRange;y<=s.positionY+s.visibleRange;y++) {
                if ((x-s.positionX)*(x-s.positionX)+(y-s.positionY)*(y-s.positionY)<s.visibleRange*s.visibleRange
                     && x>=0 && y>=0 && x<COL && y<ROW) {
                    sightRange[y][x] = 1;
                }
            }
        }
    }
}


