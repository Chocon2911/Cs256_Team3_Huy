#pragma once
#include <iostream>
#include <string>

#include "Stat.h"
#include "Employee.h"
using namespace std;

class Work : public Stat
{
    private:
    int creditPoint;
    float money;

    public:
    //========================================Constructor=========================================
    Work();
    Work(int creditPoint, float money, string name, int id);

    //============================================Get=============================================
    int getCreditPoint() const;
    float getMoney() const;

    //============================================Set=============================================
    void setCreditPoint(int creditPoint);
    void setMoney(float money);
};