#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "../Other/EmployeeLevel.h"
#include "Stat.h"
#include "Work.h"
#include "Staff.h"
using namespace std;

class Manager : public Employee, public Stat
{
    private:
    vector<Work*> notAssignedWorks;
    static vector<Staff*> staffs;

    public:
    //========================================Constructor=========================================
    Manager();
    Manager(vector<Work*> notAssignedWorks, float workHour, float moneyPerHour, vector<Work*> workDones, vector<Work*> workUFs, string name, int id);

    //============================================Get=============================================
    vector<Work*> getNotAssignedWorks() const;
    vector<Staff*> getStaffs() const;
    float getTotalMoneyFromWorkHour() override;
    float getTotalMoneyFromWork() override;

    //============================================Set=============================================
    void setNotAssignedWorks(vector<Work*> notAssignedWorks);
    void setStaffs(vector<Staff*> staffs);

    //==========================================Display===========================================
    void displayPrivateInfo();
    void displayPublicInfo();

    //===========================================Other============================================
    void addNotAssignedWorks(Work* work);
    void removeNotAssignedWorks(Work* work);
    bool assignWork(Staff* staff, Work* work);  
};