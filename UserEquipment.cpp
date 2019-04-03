//
// Created by sunka on 2019/3/6.
//

#include "UserEquipment.h"

using namespace std;


UserEquipment::UserEquipment(const int x, const int y) {
    setLocation( x, y );
}

void UserEquipment::setLocation(const int x, const int y) {
    xCoordinate = x;
    yCoordinate = y;
}




void UserEquipment::episode() {
    // 更新状态
    updateState();

    // 首先选择一个当前状态的有效行为，然后在达到目标状态前不断重复选择
    do {
        chooseAnAction();
    } while ( currentState < 5 );

    cout << "Get out Successfully.\n" << endl;
}


void UserEquipment::updateState() {


}





int UserEquipment::getSignalStrength( const BaseStation &BS ) const {
    int xDistance = xCoordinate - BS.getXCoordinate();
    int yDistance = yCoordinate - BS.getYCoordinate();

    double distance = sqrt( pow( xDistance, 2 ) + pow( yDistance, 2 ) );

    if ( BS.getType() == 0 ) {
        if ( distance >= 100 )
            return 0;
        else
            return 1;
    } else if ( BS.getType() == 1 ) {
        if ( distance >= 20 )
            return 0;
        else
            return 1;
    }
}

void UserEquipment::randomMove() {
    int xChange = rand() % 41 - 20;
    int yChange = rand() % 41 - 20;

    xCoordinate += xChange;
    yCoordinate += yChange;

    cout << "\nChange of location is ["
         << setw(4) << xChange << ","
         << setw(4) << yChange << "]"
         << "\nLocation of UE_1 is ["
         << setw(4) << xCoordinate << ","
         << setw(4) << yCoordinate << "] now"
         << endl;
}

// 重载流插入运算符
/*
ostream &operator<<( ostream &output, const UserEquipment &UE ) {
    const BaseStation &BS = *BSMap[ UE.connectedBSID ];

    output << "\nInformation of UE :"
           << "\nLocation is [ "
           << setw(4) << UE.xCoordinate<< ","
           << setw(4) << UE.yCoordinate << "]"

           << "\n\nInformation of connected BS :"
           << "\nThe ID of BS is : " << BS.getBSID()
           << "\nLocation is ["
           << setw(4) << BS.getXCoordinate() << ","
           << setw(4) << BS.getYCoordinate() << "]"
           << "\nNumber of UEs = " << BS.getNumberOfUE()
           << "\nThe type of BS is : type " << BS.getType()
           << endl;

    return output;
}
*/



int UserEquipment::reward(int, int, int) {

    int b;  //负载因子，网络中剩余频谱百分比
    int reward = b * ( moveMatch() + serviceMatch() );
    return reward;
}

int UserEquipment::moveMatch() {
    if ( ( curState.moveState == 0 && BStype == 1 )
         || ( curState.moveState == 1 && BStype == 0 ) ) {
        return 5;
    } else {
        return 1;
    }
}

int UserEquipment::serviceMatch() {
    if ( ( curState.serviceType == 0 && BStype == 0 )
         || ( curState.serviceType == 1 && BStype == 1 ) ) {
        return 5;
    } else {
        return 1;
    }
}

void UserEquipment::chooseAction() {

    int num = rand() % 10;
    if ( num ) {
        getMaxAction();
    } else {
        getRandomAction();
    }
}



int UserEquipment::getRandomAction() {

    int action;

    // 随机选择行为，直到选择到的行为有效为止
    do {
        // 获取一个0到5的随机整数
        action = lowerBound + rand() % range;
    } while ( R[currentState][action] == -1 );

    return action;
}

//获取最大回报对应的动作和Q值
int UserEquipment::getMaxAction( const int state, const bool returnType ) {
// 若 returnType = true, 返回对应的动作
// 若 returnType = false, 返回对应的Q值

    int maxElement = 0;

    // 找最大值
    for ( int i = 0; i < qSize; i++ ) {
        if( i != maxElement ){     // 避免自我比较
            if(Q[state][i] > Q[state][maxElement]){
                maxElement = i;
            }
        }
    } // i

    return ( returnType ? maxElement : Q[state][maxElement] );
}




