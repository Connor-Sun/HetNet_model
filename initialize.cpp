//
// Created by sunka on 2019/3/7.
//

#include "initialize.h"

using namespace std;



void initialize()
{
    srand( static_cast< unsigned int > ( time( nullptr) ) );

    cout << "\nStart" << endl;

    vector< BaseStation * > BSMap( 3 );

    BaseStation LTE( 0, 0, 0 );
    BaseStation WLAN( 125, 0, 1 );
}
