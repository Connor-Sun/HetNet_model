//
// Created by sunka on 2019/3/6.
//

#include "UserEquipment.h"

using namespace std;



UserEquipment::UserEquipment(const int x, const int y)
{
    setLocation( x, y );
}

void UserEquipment::setLocation(const int x, const int y)
{
    xCoordinate = x;
    yCoordinate = y;
}


double UserEquipment::getDistance( const BaseStation &BS ) const
{
    int xDistance = xCoordinate - BS.getXCoordinate();
    int yDistance = yCoordinate - BS.getYCoordinate();

    double distance = sqrt( pow( xDistance, 2 ) + pow( yDistance, 2 ) );

    return distance;
}

void UserEquipment::randomMove()
{
    int xChange = rand() % 41 - 20;
    int yChange = rand() % 41 - 20;

    xCoordinate += xChange;
    yCoordinate += yChange;

    cout << "\nChange of location is ["
         << setw(4) << xChange << ","
         << setw(4) << yChange << "]"
         << "\nLocation of UE_1 is ["
         << setw(4) << xCoordinate << ","
         << setw(4) << yCoordinate << "] now"
         << endl;
}

// 重载流插入运算符
ostream &operator<<( ostream &output, const UserEquipment &UE )
{
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

