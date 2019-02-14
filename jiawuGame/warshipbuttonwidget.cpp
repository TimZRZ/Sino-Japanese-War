#include "warshipButtonWidget.h"

warshipButtonWidget::warshipButtonWidget(QWidget *parent) : QWidget(parent)
{
    warshipInfo = setCSVList("warshipInfo.csv");
    warshipMap = setWarshipMap(warshipInfo);
    warshipButtonMap = setWarshipButtonMap(warshipMap,80,100,60);

    QToolBox* warshipToolBoxQing = new QToolBox();
    QGroupBox* class1Q = new QGroupBox(); warshipToolBoxQing->addItem((QWidget*)class1Q,QObject::tr("铁甲舰"));
    QGroupBox* class2Q = new QGroupBox(); warshipToolBoxQing->addItem((QWidget*)class2Q,QObject::tr("装甲巡洋舰"));
    QGroupBox* class3Q = new QGroupBox(); warshipToolBoxQing->addItem((QWidget*)class3Q,QObject::tr("穹甲巡洋舰"));
    QGroupBox* class4Q = new QGroupBox(); warshipToolBoxQing->addItem((QWidget*)class4Q,QObject::tr("钢壳快船"));
    QGroupBox* class5Q = new QGroupBox(); warshipToolBoxQing->addItem((QWidget*)class5Q,QObject::tr("木壳快船"));

    QToolBox* warshipToolBoxJapan = new QToolBox();
    QGroupBox* class1J = new QGroupBox(); warshipToolBoxJapan->addItem((QWidget*)class1J,QObject::tr("铁甲舰"));
    QGroupBox* class2J = new QGroupBox(); warshipToolBoxJapan->addItem((QWidget*)class2J,QObject::tr("装甲巡洋舰"));
    QGroupBox* class3J = new QGroupBox(); warshipToolBoxJapan->addItem((QWidget*)class3J,QObject::tr("防护巡洋舰"));
    QGroupBox* class4J = new QGroupBox(); warshipToolBoxJapan->addItem((QWidget*)class4J,QObject::tr("炮舰"));
    QGroupBox* class5J = new QGroupBox(); warshipToolBoxJapan->addItem((QWidget*)class5J,QObject::tr("辅助巡洋舰"));

    QHBoxLayout* Q1box = new QHBoxLayout; QHBoxLayout* J1box = new QHBoxLayout;
    QHBoxLayout* Q2box = new QHBoxLayout; QHBoxLayout* J2box = new QHBoxLayout;
    QHBoxLayout* Q3box = new QHBoxLayout; QHBoxLayout* J3box = new QHBoxLayout;
    QHBoxLayout* Q4box = new QHBoxLayout; QHBoxLayout* J4box = new QHBoxLayout;
    QHBoxLayout* Q5box = new QHBoxLayout; QHBoxLayout* J5box = new QHBoxLayout;

    //将warship button按照相应信息分组中
    for (map<QString,QToolButton*>::iterator i = warshipButtonMap.begin();i != warshipButtonMap.end();i++) {
        QString type = warshipMap[i->first].shipType;
        if (type == QString("class1Q")) {Q1box->addWidget(i->second);} if (type == QString("class1J")) {J1box->addWidget(i->second);}
        if (type == QString("class2Q")) {Q2box->addWidget(i->second);} if (type == QString("class2J")) {J2box->addWidget(i->second);}
        if (type == QString("class3Q")) {Q3box->addWidget(i->second);} if (type == QString("class3J")) {J3box->addWidget(i->second);}
        if (type == QString("class4Q")) {Q4box->addWidget(i->second);} if (type == QString("class4J")) {J4box->addWidget(i->second);}
        if (type == QString("class5Q")) {Q5box->addWidget(i->second);} if (type == QString("class5J")) {J5box->addWidget(i->second);}
    }

    class1Q->setLayout(Q1box); class2Q->setLayout(Q2box); class3Q->setLayout(Q3box); class4Q->setLayout(Q4box); class5Q->setLayout(Q5box);
    class1J->setLayout(J1box); class2J->setLayout(J2box); class3J->setLayout(J3box); class4J->setLayout(J4box); class5J->setLayout(J5box);

    Qing = new QVBoxLayout;
    Japan = new QVBoxLayout;
    warshipToolBoxQing->setMinimumSize(400,260); warshipToolBoxQing->setMaximumSize(400,260);
    warshipToolBoxJapan->setMinimumSize(400,260); warshipToolBoxJapan->setMaximumSize(400,260);
    QLabel* QingLabel = new QLabel; QingLabel->setText(QObject::tr("大清北洋水师")); QingLabel->setMaximumHeight(50);
    QLabel* JapanLabel = new QLabel; JapanLabel->setText(QObject::tr("日本联合舰队")); JapanLabel->setMaximumHeight(50);
    Qing->addWidget(QingLabel); Qing->addWidget(warshipToolBoxQing);
    Japan->addWidget(JapanLabel); Japan->addWidget(warshipToolBoxJapan);



}

//生成CSV文件的读取路径（绝对地址）
QString warshipButtonWidget::setCSVPath(QString CSVName)
{
    QDir dir;
    QString currentPath = dir.currentPath();
    QString path = currentPath.section('/',0,-2);
    QString fileName = path+"/jiawuGame/files/"+CSVName;
    return fileName;
}

//将CSV文件内容转化为QStringList
QStringList warshipButtonWidget::setCSVList(QString CSVName)
{
    QString CSVPath = setCSVPath(CSVName);
    QFile csvFile(CSVPath);
    QStringList CSVList;
    if (csvFile.open(QIODevice::ReadWrite)) {
        QTextStream stream(&csvFile);
        while (!stream.atEnd()) {
            CSVList.append(stream.readLine());
        }
        csvFile.close();
    }
    return CSVList;
}

//生成warship的map
map<QString,warship> warshipButtonWidget::setWarshipMap(QStringList CSVList)
{
    map<QString,warship> warshipMap;
    for (int i = 1; i < CSVList.count(); i++){
        QStringList warshipInfoList = CSVList[i].split(",");
        warship warshipObject;
        warshipObject.shipName = warshipInfoList[1];
        warshipObject.shipIMG = warshipInfoList[2];
        warshipObject.shipType = warshipInfoList[3];
        warshipMap.insert (pair<QString,warship> (warshipInfoList[0],warshipObject));
    }
    return warshipMap;
}

//输出warship的map
map<QString,warship> warshipButtonWidget::outputWarshipMap()
{
    return warshipButtonWidget::warshipMap;
}

//生成每个相关warship的button
QToolButton* warshipButtonWidget::setWarshipButton(QString buttonText, QString buttonIcon,int buttonHeight,int buttonWidth,int iconHeight){
    QToolButton* warshipButton = new QToolButton();
    warshipButton->setText(buttonText);
    warshipButton->setIcon(QPixmap(buttonIcon));
    warshipButton->setIconSize(QSize(buttonWidth,iconHeight));
    warshipButton->setAutoRaise(true);
    warshipButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    warshipButton->setMinimumSize(buttonWidth,buttonHeight);
    return warshipButton;
}

//生成每个warship button的map
map<QString,QToolButton*> warshipButtonWidget::setWarshipButtonMap(map<QString,warship> warshipMap,int buttonHeight,
                                                                   int buttonWidth,int iconHeight)
{
    map<QString,QToolButton*> warshipButtonMap;
    for (map<QString,warship>::iterator i = warshipMap.begin();i != warshipMap.end();i++) {
        QToolButton* warshipButton = setWarshipButton((i->second).shipName,(i->second).shipIMG,buttonHeight,buttonWidth,iconHeight);
        warshipButtonMap.insert (pair<QString,QToolButton*> (i->first,warshipButton));
    }
    return warshipButtonMap;
}
