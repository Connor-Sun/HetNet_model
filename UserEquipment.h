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


class BaseStation;

class UserEquipment
{

    // friend std::ostream &operator<<( std::ostream &, const UserEquipment & );

public:
    UserEquipment();
    UserEquipment( const int, const int );
    //~UserEquipment();



    // 执行学习过程
    void episode();


    // 更新状态
    void updateState();
    // 随机移动用户设备
    void randomMove();

    double getDistance(int, int) const;
    // 获取与基站间的信号强度
    int getSignalStrength( const BaseStation & ) ;



    // 选择一个动作
    void chooseAction();
    // 随机选择动作
    void getRandomAction();
    // 获取最大回报对应的动作或Q值
    void getMaxAction();


    //更新Q表
    void updateQtable();

    int calculateState();
    //获取回报
    double reward();
    // 移动状态与所选网络的匹配系数
    int moveMatch();
    // 业务请求类型与所选网络的匹配系数
    int serviceMatch();

    void evaluateState( int, int, int, int, int, int );

    double getPF();

    int strongcount = 0;

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

    int action;



};


#endif // USEREQUIPMENT_H
