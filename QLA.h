//
// Created by sunka on 2019/3/13.
//

#ifndef QLA_H
#define QLA_H

#include <array>




class QLA {
public:

    int reward( int, int, int );

    void stateUpdate();

    void chooseAction();

    int moveMatch();

    int serviceMatch();


private:

    struct State {
        int serviceType;
        int moveState;
        int signalStrength;
        int loadState;
    } curState;



    //std::array< std::array< int, 2 >, 40 > Q;



};


#endif //QLA_H
