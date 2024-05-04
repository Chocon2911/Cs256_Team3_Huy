#pragma once 
#include "LevelCode.h"
#include "EmployeeLevel.h"
#include<iostream>
#include<vector>
using namespace std;

class Level
{
    private:
    int currCreditPoint;
    LevelCode levelCode;
    static vector<EmployeeLevel*> employeeLevels;

    public:
    Level();
    Level(int currCreditPoint, LevelCode levelCode);
    ~Level();

    //==========================================Get Set===========================================
    int getCurrCreditPoint() const;
    LevelCode getLevelCode() const;
    vector<EmployeeLevel*> getEmployeeLevels() const;

    void setCurrCreditPoint(int currCreditPoint);
    void setLevelCode(LevelCode levelCode);
    void addEmployeeLevel(EmployeeLevel* employeeLevel);
    void removeEmployeeLevel(EmployeeLevel* deleteEmployeeLevel);

    //========================================Modify Level========================================
    bool Promote();
    bool Demote();
};
