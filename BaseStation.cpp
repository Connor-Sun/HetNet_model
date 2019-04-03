//
// Created by sunka on 2019/3/6.
//
#include "BaseStation.h"
#include "initialize.h"

using namespace std;

unsigned int BaseStation::numberOfBS = 0;


BaseStation::BaseStation(const int x, const int y,
                                   const int type)
        : xCoordinate( x ), yCoordinate( y ),
          typeOfBS( type ), BSID( numberOfBS++ )
{
    updateNumberOfUE();
    BSMap[ BSID ] = this;
}

int BaseStation::getXCoordinate() const {
    return xCoordinate;
}

int BaseStation::getYCoordinate() const {
    return yCoordinate;
}

int BaseStation::getLoadState() const {

    return numberOfUE / 20;
}

void BaseStation::updateNumberOfUE() {

    numberOfUE = rand() % 100;
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

