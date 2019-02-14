#include "warship.h"
#include <iostream>
#include <Qstring>
using namespace std;

void warship::Initial(QString shipName, QString shipType, QString shipIMG)
{
    this->shipName = shipName;
    this->shipType = shipType;
    this->shipIMG = shipIMG;
}
