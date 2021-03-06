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

// 输出当前状态
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
        setLocation( 0, 0 );

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
        if ( distance <= 50 )
            return 4;
        else if ( distance <= 100 )
            return 3;
        else if ( distance <= 130 )
            return 2;
        else if ( distance <= 150 )
            return 1;
        else
            return 0;
    } else if ( BS.getType() == 1 ) {
        if ( distance <= 20 )
            return 4;
        else if ( distance <= 30 )
            return 3;
        else if ( distance <= 40 )
            return 2;
        else if ( distance <= 50 )
            return 1;
        else
            return 0;
    }
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




// 选择一个动作
void UserEquipment::chooseAction() {

    if ( static_cast< int >( ( rand() % counts ) / ( epsilon * counts ) ) ) {
        getMaxAction();
    } else {
        getRandomAction();
    }
    //cout << "Action : " << action << endl;
}


void UserEquipment::getRandomAction() {
    //cout << "rand() = " << rand() << endl;
    action = rand() % 2;
}

// 获取最大回报对应的动作
void UserEquipment::getMaxAction() {

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

    action = maxAction;
}



// 更新Q表
void UserEquipment::updateQtable() {

    Qtable[calculateState()][action]
        = ( 1 - alpha ) * Qtable[calculateState()][action]
          + alpha * reward();
}

// 计算当前状态在Q表中的位置
int UserEquipment::calculateState() {
    int state = curState.serviceType * 1250 + curState.moveState * 625
                + curState.signalStrength[0] * 125 + curState.signalStrength[1] * 25
                + curState.loadState[0] * 5 + curState.loadState[1];
    return state;
}

// 获取回报
double UserEquipment::reward() {

    double reward = ( 5 - curState.loadState[action] )
                * ( moveMatch() + serviceMatch() )
                * ( curState.signalStrength[action] + 1 );
    //cout << "reward = " << reward << endl;
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

// 更新状态
void UserEquipment::evaluateState( int x, int y, int st, int ms, int ls0, int ls1 ) {

    // 20%概率请求语音服务，80%概率请求数据服务
    curState.serviceType = st;
    // 50%移动，50%静止
    curState.moveState = ms;

    // 更新基站中用户设备数量 并 获取基站负载

    curState.loadState[0] = ls0;
    curState.loadState[1] = ls1;


    // 设置用户设备位置 并 获取信号强度
    setLocation( x, y );

    for ( int i = 0; i < 2; ++i ) {
        curState.signalStrength[i] = getSignalStrength( *BSMap[i] );
    }

// 输出当前状态
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

double UserEquipment::getPF() {
    double pf = curState.serviceType
           * ( 4 - curState.loadState[action] + curState.signalStrength[action] ) / 2
           + moveMatch() + serviceMatch();
    return pf;
}



