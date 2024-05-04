#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Employee.h"
#include "Stat.h"
#include "../Other/Level.h"
#include "../Employee/Work.h"
#include "../Other/Utils.cpp"
using namespace std;

class Staff : public Employee, public Stat
{
    private:
    Level* currLevel;

    public:
    //========================================Constructor=========================================
    Staff();
    Staff(Level* Level, float workHour, float moneyPerHour, vector<Work*> workDones, vector<Work*> workUFs, string name, int id);

    //============================================Get=============================================
    Level* getCurrLevel() const;
    float getTotalMoneyFromWorkHour() override;
    float getTotalMoneyFromWork() override;

    //============================================Set=============================================
    void setCurrLevel(Level* currLevel);

    //==========================================Display===========================================
    void displayPrivateInfo();
    void displayPublicInfo();

    //==========================================Account===========================================
    void removeAccount();
};