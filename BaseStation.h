//
// Created by sunka on 2019/3/6.
//
#ifndef BASESTATION_H
#define BASESTATION_H

#include <cstdlib>

#include "initialize.h"


class BaseStation {

    //friend class UserEquipment;

public:

    BaseStation(const int x, const int y, const int type );
    //~BaseStation();

    int getXCoordinate() const;
    int getYCoordinate() const;
    int getType() const;
    int getLoadState() const;
    void updateNumberOfUE();

    int getBSID() const;
    static unsigned int getNumberOfBS();

private:

    const int xCoordinate;  // 基站所在位置横坐标
    const int yCoordinate;  // 基站所在位置纵坐标
    const int typeOfBS;     // 基站类型
    unsigned int numberOfUE; // 基站中的用户数
    const int BSID; // 基站的ID
    static unsigned int numberOfBS; // 基站数量
};




#endif // BASESTATION_H
