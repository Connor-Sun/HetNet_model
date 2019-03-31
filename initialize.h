//
// Created by sunka on 2019/3/7.
//
#ifndef INITIALIZE_H
#define INITIALIZE_H

#include <cstdlib>
#include <ctime>
#include <vector>

#include "BaseStation.h"
#include "UserEquipment.h"

class BaseStation;
class UserEquipment;

extern std::vector< BaseStation * > BSMap;
extern UserEquipment UE_1;

void initialize();

#endif //INITIALIZE_H
