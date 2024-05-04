#pragma once
#include "LevelCode.h"
#include <iostream>
using namespace std;

class EmployeeLevel
{
    private:
    LevelCode levelCode;
    float moneyPerWorkHour;
    int creditPointRequired;

    public:
    //========================================Constructor=========================================
    EmployeeLevel();
    EmployeeLevel(LevelCode levelCode, float moneyPerWorkHour, int creditPointRequired);
    ~EmployeeLevel();

    //==========================================Operator==========================================
    void operator=(const EmployeeLevel* other);

    //==========================================Get Set===========================================
    LevelCode getLevelCode() const;
    float getMoneyPerWorkHour() const;
    int getCreditPointRequired() const;

    void setLevelCode(LevelCode levelCode);
    void setMoneyPerWorkHour(float moneyPerWorkHour);
    void setCreditPointRequired(float creditPointRequired);

    //==========================================Display===========================================
    void display() const;
};