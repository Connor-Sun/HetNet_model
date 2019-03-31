//
// Created by sunka on 2019/3/6.
//
#ifndef USEREQUIPMENT_H
#define USEREQUIPMENT_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>

#include "initialize.h"
#include "BaseStation.h"


class BaseStation;

class UserEquipment
{
    friend std::ostream &operator<<( std::ostream &, const UserEquipment & );

public:
    UserEquipment( const int, const int );
    //~UserEquipment();

    double getDistance( const BaseStation & ) const;
    void randomMove();

    //int reward() const;


private:
    void setLocation( const int x, const int y );

    int xCoordinate;
    int yCoordinate;
    int connectedBSID = 1;

};


#endif // USEREQUIPMENT_H
