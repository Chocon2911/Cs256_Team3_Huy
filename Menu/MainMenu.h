#pragma once

#include "../Other/Utils.cpp"
#include "../Other/LevelCode.h"
#include "../Other/EmployeeLevel.h"
#include "../Other/Level.h"
#include "../Employee/Employee.h"
#include "../Employee/Manager.h"
#include "../Employee/Staff.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <conio.h>
#include <limits>
using namespace std;

class MainMenu
{
    public:
    //============================================Menu============================================
    int mainMenu();
    int addNewEmployeeMenu();
    int findEmployeeMenu();
    void modifyEmployeeLevelMenu(vector<EmployeeLevel*> employeeLevels);
    void allInformationMenu(vector<Staff*> staffs, vector<Manager*> managers);
    void exitMenu();

    //==========================================Display===========================================
    //Main Menu
    int displayMainMenu();

    //Find Employee
    void displayFindEmployee(int id);

    //Add New Employee
    void displayAddNewEmployee(string* job, string* name, int* id, float* moneyPerHour, LevelCode* levelCode);

    //modify EmployeeLevel
    int displayEmployeeLevelTable();
    EmployeeLevel* displayModifyEmployeeLevel(vector<EmployeeLevel*> employeeLevel, int index, float moneyPerWorkHour, int creditPointRequired);
    bool checkIfMoneyPerWorkHourGood(vector<EmployeeLevel*> employeeLevels, int index, float moneyPerWorkHour);
    bool checkIfCreditPointGood(vector<EmployeeLevel*> employeeLevels, int index, int creditPointRequired);

    //All Information
    void displayManagerIn4(vector<Manager*> managers);
    void displayStaffIn4(vector<Staff*> staffs);

    //Other
    void displayWrongInput();
    //===========================================Other============================================

};