//
// Created by sunka on 2019/3/13.
//

#include "QLA.h"

int QLA::reward(int, int, int) {

    int b;  //负载因子，网络中剩余频谱百分比

    int reward = b * ( moveMatch() + serviceMatch() );


}


int QLA::moveMatch() {
    if ( ( curState.moveState == 0 && BStype == 1 )
        || ( curState.moveState == 1 && BStype == 0 ) ) {
        return 5;
    } else {
        return 1;
    }
}

int QLA::serviceMatch() {
    if ( ( curState.serviceType == 0 && BStype == 0 )
         || ( curState.serviceType == 1 && BStype == 1 ) ) {
        return 5;
    } else {
        return 1;
    }
}

void QLA::chooseAction() {

    int num = rand() % 10;

    if ( num ) {
        getMax();
    } else {
        getRandom();
    }
}

int getRandomAction( const int lowerBound, const int upperBound ) {

    int action;
    int range = (upperBound - lowerBound) + 1;

    // 随机选择行为，直到选择到的行为有效为止
    do {
        // 获取一个0到5的随机整数
        action = lowerBound + rand() % range;
    } while ( R[currentState][action] == -1 );

    return action;
}

int reward( const int action ) {

    int reward = static_cast<int>( R[currentState][action] + ( gamma * maximum( action, false ) ) );

    return reward;
}