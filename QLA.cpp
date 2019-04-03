//
// Created by sunka on 2019/3/13.
//

#include "QLA.h"

std::array< std::array< std::array< std::array< int, 5 >, 2 >, 2 >, 2 > Qtable;

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

//获取最大回报对应的动作和Q值
int getMaxAction( const int state, const bool returnType ) {
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

int reward( const int action ) {

    int reward = static_cast<int>( R[currentState][action] + ( gamma * maximum( action, false ) ) );

    return reward;
}