//
// Created by sunka on 2019/3/13.
//

#include "QLA.h"

using namespace std;

void QLA() {

    cout << "Start" << endl;


    for ( int i = 0; i < 1000; ++i ) {
        for (int j = 0; j < counts / 1000; ++j) {
            UE_1.episode();
            update( i * ( counts / 1000 ) + j );
            //cout << i << "\n";
        }
        if ( !( ( i + 1 ) % 100 ) || i + 1 == 10 || i + 1 == 30 ||i + 1 == 50 || !i ) {
            cout << "episode : " << ( i + 1 ) * ( counts / 1000 ) << " times" << endl;
            evaluate();
        }

}

    cout << "End" << endl;

    //cout << "\ntotal : " << UE_1.strongcount << endl;
    printQtable();
}

void update( int count ) {
    epsilon = 1 - count / ( counts * 1.25 );
    alpha = 1 - count / ( counts * 1.25 );
}

void printQtable() {

    cout << "\nQtable:\n";
    for ( int i = 0; i < 2500; ++i ) {
        cout << "\n" << setw(4) << i
             << setw(10) << Qtable[i][0]
             << setw(10) << Qtable[i][1];
    }
}

// 评估用户效用
void evaluate() {

    int count = 0;
    double totalpf_max = 0;
    double totalpf_ran = 0;
    double averagepf_max;
    double averagepf_ran;

    for ( int i = -200; i < 200; i += 10 ) {
        for ( int j = -200; j < 200; j += 10 ) {
            if ( sqrt( pow(i, 2) + pow(j, 2) ) <= 200 ) {
                for (int k = 0; k < 2; ++k) {
                    for (int l = 0; l < 2; ++l) {
                        for (int m = 0; m < 5; ++m) {
                            for (int n = 0; n < 5; ++n) {
                                ++count;
                                UE_evaluate.evaluateState( i, j, k, l, m, n );
                                UE_evaluate.getMaxAction();
                                totalpf_max += UE_evaluate.getPF();
                                UE_evaluate.getRandomAction();
                                totalpf_ran += UE_evaluate.getPF();

                                //cout << "count = " << count << "totalpf = " << totalpf << "\n";
                            }
                        }
                    }
                }
            } else
                continue;
        }

    }

    averagepf_max = totalpf_max / count;
    averagepf_ran = totalpf_ran / count;

    cout << "averagepf_max = " << averagepf_max << "\n";
    cout << "averagepf_ran = " << averagepf_ran << "\n";


}