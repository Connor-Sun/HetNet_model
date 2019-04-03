//
// Created by sunka on 2019/3/13.
//

#include "QLA.h"

using namespace std;

void QLA() {

    cout << "Start" << endl;

    for ( int i = 0; i < counts; ++i ) {
        UE_1.episode();
        update( i );
    }

    cout << "End" << endl;

    cout << "\ntotal : " << UE_1.strongcount << endl;
    printQtable();
}

void update( int count ) {
    epsilon = 1 - count / counts;
    alpha = 1 -  count / ( counts * 1.25 );
}

void printQtable() {

    cout << "\nQtable:\n";
    for ( int i = 0; i < 400; ++i ) {
        cout << "\n" << setw(4) << i
             << setw(10) << Qtable[i][0]
             << setw(10) << Qtable[i][1];
    }
}
