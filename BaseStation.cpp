//
// Created by sunka on 2019/3/6.
//
#include "BaseStation.h"
#include "initialize.h"

using namespace std;

unsigned int BaseStation::numberOfBS = 0;

std::vector< BaseStation * > BSMap;


BaseStation::BaseStation(const int x, const int y,
                                   const int type)
        : xCoordinate( x ), yCoordinate( y ),
          typeOfBS( type ), BSID( numberOfBS++ )
{
    numberOfUE = 3 + rand() % 4;
    BSMap[ BSID ] = this;
}

int BaseStation::getXCoordinate() const {
    return xCoordinate;
}

int BaseStation::getYCoordinate() const {
    return yCoordinate;
}

int BaseStation::getNumberOfUE() const {
    return numberOfUE;
}

int BaseStation::getType() const {
    return typeOfBS;
}

int BaseStation::getBSID() const {
    return BSID;
}

unsigned int BaseStation::getNumberOfBS() {
    return numberOfBS;
}

