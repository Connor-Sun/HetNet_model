//
// Created by sunka on 2019/3/6.
//

#include "UserEquipment.h"

using namespace std;

UserEquipment::UserEquipment() {
    setLocation( 0, 0 );
}

UserEquipment::UserEquipment(const int x, const int y ) {
    setLocation( x, y );
}

void UserEquipment::setLocation(const int x, const int y) {
    xCoordinate = x;
    yCoordinate = y;
}


// 学习过程
void UserEquipment::episode() {

    // 更新状态
    updateState();

    // 选择一个行为
    chooseAction();

    // 更新Q表
    updateQtable();

    //cout << "1" << endl;
}

// 更新状态
void UserEquipment::updateState() {

    // 20%概率请求语音服务，80%概率请求数据服务
    curState.serviceType = ( rand() % 5 ) ? 1 : 0;
    // 50%移动，50%静止
    curState.moveState = rand() % 2;

    // 更新基站中用户设备数量 并 获取基站负载
    for ( int i = 0; i < 2; ++i ) {
        BSMap[i]->updateNumberOfUE();
        curState.loadState[i] = BSMap[i]->getLoadState();
    }

    // 移动用户设备 并 获取信号强度
    randomMove();
    for ( int i = 0; i < 2; ++i ) {
        curState.signalStrength[i] = getSignalStrength( *BSMap[i] );
    }
/*
    cout << "\nState:\n"
         << setw(2) << curState.moveState
         << setw(2) << curState.serviceType
         << setw(2) << curState.signalStrength[0]
         << setw(2) << curState.signalStrength[1]
         << setw(2) << curState.loadState[0]
         << setw(2) << curState.loadState[1]
         << "\n" << setw(4) << calculateState() << endl;

*/
}

// 随机移动用户设备
void UserEquipment::randomMove() {
    int xChange = rand() % 601 - 300;
    int yChange = rand() % 601 - 300;

    setLocation( xChange, yChange );

    if ( getDistance( 0, 0 ) >= 200 )
        randomMove();

/*
    cout << "\nChange of location is ["
         << setw(4) << xChange << ","
         << setw(4) << yChange << "]"
         << "\nLocation of UE_1 is ["
         << setw(4) << xCoordinate << ","
         << setw(4) << yCoordinate << "] now"
         << endl;
*/
}

double UserEquipment::getDistance(int x, int y) const {
    int xDistance = xCoordinate - x;
    int yDistance = yCoordinate - y;
    double distance = sqrt( pow(xDistance, 2) + pow(yDistance, 2) );

    return distance;
}

int UserEquipment::getSignalStrength( const BaseStation &BS )  {

    double distance = getDistance( BS.getXCoordinate(), BS.getYCoordinate() );

    if ( BS.getType() == 0 ) {
        if ( distance >= 150 )
            return 0;
        else
            return 1;
    } else if ( BS.getType() == 1 ) {
        if ( distance >= 80 )
            return 0;
        else{
            strongcount++;
            return 1;
        }
    }
}

/*
// 重载流插入运算符
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




// 选择一个动作
void UserEquipment::chooseAction() {

    if ( static_cast< int >( ( rand() % counts ) / ( epsilon * counts ) ) ) {
        action = getMaxAction();
    } else {
        action = getRandomAction();
    }
    //cout << "Action : " << action << endl;
}


int UserEquipment::getRandomAction() {
    //cout << "rand() = " << rand() << endl;
    return rand() % 2;
}

// 获取最大回报对应的动作
int UserEquipment::getMaxAction() {

    int maxAction = 0;
    int state = calculateState();

    // 找最大值
    for ( int i = 0; i < 2; i++ ) {
        if( i != maxAction ){     // 避免自我比较
            if(Qtable[state][i] > Qtable[state][maxAction]){
                maxAction = i;
            }
        }
    } // i

    return maxAction;
}



// 更新Q表
void UserEquipment::updateQtable() {

    Qtable[calculateState()][action]
        = ( 1 - alpha ) * Qtable[calculateState()][action]
          + alpha * reward();
}

// 计算当前状态在Q表中的位置
int UserEquipment::calculateState() {
    int state = curState.serviceType * 200 + curState.moveState * 100
                + curState.signalStrength[0] * 50 + curState.signalStrength[1] * 25
                + curState.loadState[0] * 5 + curState.loadState[1];
    return state;
}

// 获取回报
double UserEquipment::reward() {

    double reward = ( 5 - curState.loadState[action] )
                * ( moveMatch() + serviceMatch() )
                * ( curState.signalStrength[action] ? 5 : 1 );
    return reward;
}

int UserEquipment::moveMatch() {
    if ( ( curState.moveState == 0 && BSMap[action]->getType() == 1 )
         || ( curState.moveState == 1 && BSMap[action]->getType() == 0 ) ) {
        return 5;
    } else {
        return 1;
    }
}

int UserEquipment::serviceMatch() {
    if ( ( curState.serviceType == 0 && BSMap[action]->getType() == 0 )
         || ( curState.serviceType == 1 && BSMap[action]->getType() == 1 ) ) {
        return 5;
    } else {
        return 1;
    }
}





