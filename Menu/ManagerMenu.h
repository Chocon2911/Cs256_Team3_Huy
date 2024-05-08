#pragma once
#include<iostream>

#include "../Other/Utils.cpp"
#include "../Employee/Manager.h"
#include "../Employee/Staff.h"
#include "../Employee/Work.h"
using namespace std;

class ManagerMenu
{
    public:
    //============================================Menu============================================
    void mainMenu(Manager* manager);
    void informationMenu(Manager* manager);
    void addWorkHourMenu(Manager* manager);
    void setMoneyPerWorkHourMenu(Manager* manager);
    void assignWorkMenu(vector<Staff*> staffs, Manager* manager);
    void paySalaryMenu(Manager* manager);
    void removeAccount();
    bool quitMenu();

    //==========================================Display===========================================
    //Main
    int displayMain(Manager* manager);

    //Information
    void displayInformation(Manager* manager);

    // add work hour
    void displayAddWorkHour(Manager* manager, float addWorkHour);

    // set money per hour
    void displaySetMoneyPerWorkHour(Manager* manager, float moneyPerWorkHour);

    //Assign work
    void displayAssignWork();
    Staff* displayChooseStaff(vector<Staff*>);
    Work* displayChooseWork(vector<Work*>, Manager*);
    Work* displayCreateNewWork(Manager*);

    //Pay salary
    bool displayPaySalary(string totalSalary);
    void displayAcceptPaySalary();
    void displayRefusePaySalary();

    //Quit
    bool displayQuit();

    //Other
    void displayWrongInput();
    void displayPressAnyKey();
};