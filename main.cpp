#include <iostream>

#include "BaseStation.h"
#include "UserEquipment.h"
#include "initialize.h"

using namespace std;

void episode();
//void chooseAnAction();
void getBSDistance();


int main()
{
    initialize();

    for ( int i = 1; i <= 20; ++i )
    {
        cout << "\n\n\nIn episode " << i << endl;
        episode();
    }
    return 0;
}


void episode()
{
    cout << UE_1;

    getBSDistance();

    UE_1.randomMove();
}

void getBSDistance()
{
    int count = BaseStation::getNumberOfBS();
    for ( int i = 1; i <= count; ++i )
    {
        BaseStation &BS = *BSMap[ i ];
        cout << "\nDistance between UE & BS_" << i << " = "
             << UE_1.getDistance( BS )
             << "\nNumber of UE in BS_" << i << " = "
             << BS.getNumberOfUE() << "\n";
    }
}
