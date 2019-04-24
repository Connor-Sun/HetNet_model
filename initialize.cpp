//
// Created by sunka on 2019/3/7.
//

#include "initialize.h"

using namespace std;

vector< BaseStation * > BSMap( 2 );

BaseStation LTE( 0, 0, 0 );
BaseStation WLAN( 125, 0, 1 );

array< array< double, 2 >, 2500 > Qtable{};

UserEquipment UE_1;
UserEquipment UE_evaluate;

double epsilon = 1;
double alpha = 1;

const int counts = 1000000;

void initialize() {
    srand( static_cast< unsigned int > ( time( nullptr) ) );

    cout << "\nInitialized" << endl;
}
