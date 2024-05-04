#pragma once
#include <iostream>
#include <vector>

#include "../Other/Utils.cpp"
#include "Work.h"
using namespace std;

class Employee
{
    private:
    float workHour;
    float moneyPerHour;
    vector<Work*> workDoneList;
    vector<Work*> workUFList;

    public:
    //========================================Constructor=========================================
    Employee();
    Employee(float workHour, float moneyPerHour, vector<Work*> workDoneList, vector<Work*> workUFList);

    //============================================Get=============================================
    float getWorkHour() const;
    float getMoneyPerHour() const;
    vector<Work*> getWorkDones() const;
    vector<Work*> getWorkUFs() const;

    float getSalary();
    virtual float getTotalMoneyFromWorkHour();
    virtual float getTotalMoneyFromWork();

    //============================================Set=============================================
    void setWorkHour(float workHour);
    void setMoneyPerHour(float moneyPerHour);
    void setWorkDones(vector<Work*> workDoneList);
    void setWorkUFs(vector<Work*> workUFList);

    //============================================Work============================================
    void addWorkDone(Work* work);
    void addWorkUF(Work* work);
    void removeWorkDone(Work* work);
    void removeWorkUF(Work* work);
    void addWorkHour(float workHour);

    //=========================================Pay Salary=========================================    
    void paySalary();
    void removeAllWorkDone();
    void removeAllWorkHour();
    
};