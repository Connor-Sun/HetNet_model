//
// Created by sunka on 2019/3/7.
//
#ifndef INITIALIZE_H
#define INITIALIZE_H

#include <cstdlib>
#include <ctime>
#include <array>
#include <vector>

#include "BaseStation.h"
#include "UserEquipment.h"
#include "QLA.h"


class BaseStation;
class UserEquipment;

extern std::vector< BaseStation * > BSMap;
extern UserEquipment UE_1;

extern BaseStation LTE;
extern BaseStation WLAN;

extern std::array< std::array< double, 2 >, 2500 > Qtable;

extern double epsilon;
extern double alpha;

extern const int counts;


void initialize();

#endif //INITIALIZE_H
