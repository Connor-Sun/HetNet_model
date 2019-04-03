//
// Created by sunka on 2019/3/6.
//
#ifndef USEREQUIPMENT_H
#define USEREQUIPMENT_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>

#include "initialize.h"
#include "BaseStation.h"

extern std::array< std::array< std::array< std::array< int, 5 >, 2 >, 2 >, 2 > Qtable;

class BaseStation;

class UserEquipment
{

    // friend std::ostream &operator<<( std::ostream &, const UserEquipment & );

public:
    UserEquipment( const int, const int );
    //~UserEquipment();

    int getSignalStrength( const BaseStation & ) const;
    void randomMove();

    //获取回报
    int reward( int, int, int );
    // 移动状态与所选网络的匹配系数
    int moveMatch();
    // 业务请求类型与所选网络的匹配系数
    int serviceMatch();

    // 选择一个动作
    void chooseAction();
    // 随机选择动作
    int getRandomAction();
    // 获取最大回报对应的动作或Q值
    int getMaxAction( const int, const bool );

    // 更新状态
    void updateState();

    // 执行学习过程
    void episode();


private:
    void setLocation( const int x, const int y );

    int xCoordinate;
    int yCoordinate;
    int connectedBSID;

    struct State {
        int serviceType;
        int moveState;
        int signalStrength[2];
        int loadState[2];
    } curState;

};


#endif // USEREQUIPMENT_H
