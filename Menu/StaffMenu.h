#pragma once
#include <iostream>
#include <string>

#include "../Other/Utils.cpp"
#include "../Employee/Staff.h"
using namespace std;

class StaffMenu
{
    public:
    //============================================Menu============================================
    void mainMenu(Staff* staff);
    void informationMenu(Staff* staff);
    void addWorkHourAmountMenu(Staff* staff);
    void promoteMenu(Staff* staff);
    void demoteMenu(Staff* staff);
    void paySalaryMenu(Staff* staff);
    bool removeAccountMenu(Staff* staff);
    bool quitMenu();

    //==========================================Display===========================================
    //Main
    int displayMain();

    //Information Menu
    void displayInformation(Staff* staff);

    //Add Work Hour Amount Menu
    void displayAddWorkHourAmount(Staff* staff, float addWorkHour);

    // Promote
    bool displayPromote(string nextLevelCode, string nextLevelCreditPoint, string nextLevelMoneyPerHour);
    void displayCantPromote();
    void displayRefusePromote();
    void displayAcceptPromote();

    // Demote
    bool displayDemote(string prevLevelCode, string prevLevelCreditPoint, string prevLevelMoneyPerHour);
    void displayCantDemote();
    void displayRefuseDemote();
    void displayAcceptDemote();

    // Pay Salary
    bool displayPaySalary(string workHourAmount);
    void displayAcceptPaySalary();
    void displayRefusePaySalary();

    // Remove Account   
    bool displayRemoveAccount();
    void displayAcceptRemoveAccount();
    void displayRefuseRemoveAccount();

    //Quit
    bool displayQuit();
    void displayAcceptQuit();
    void displayRefuseQuit();

    //===========================================Other============================================
    void wrongInput();

};