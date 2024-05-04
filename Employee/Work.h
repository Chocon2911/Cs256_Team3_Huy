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
    int managerId;
    int staffId;

    public:
    //========================================Constructor=========================================
    Work();
    Work(int creditPoint, float money, int managerId, int staffId, string name, int id);

    //============================================Get=============================================
    int getCreditPoint() const;
    float getMoney() const;
    int getManagerId() const;
    int getStaffId() const;

    //============================================Set=============================================
    void setCreditPoint(int creditPoint);
    void setMoney(float money);
    void setManagerId(int managerId);
    void setStaffId(int staffId);
};