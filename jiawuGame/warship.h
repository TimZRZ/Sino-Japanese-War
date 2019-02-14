#ifndef WARSHIP_H
#define WARSHIP_H
#include <iostream>
#include <QString>
using namespace std;

class warship
{
public:
    QString shipName;
    QString shipType;
    QString shipIMG;
    int positionX;//战舰的x坐标
    int positionY;//战舰的y坐标
    int shipL;//战舰的长
    int shipH;//战舰的宽
    int shipSpeed;//战舰速度
    int fireRange;//战舰射程
    int firePower;//炮火威力
    int life;//战舰生命值
    int visibleRange;//能见范围
    bool operationStatus;//可运行状态
    bool influence;//势力考虑状态
    void Initial(QString shipName, QString shipType, QString shipIMG);
};

#endif // WARSHIP_H
