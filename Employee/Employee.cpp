#include "Employee.h"
using namespace std;

//========================================Constructor=========================================
Employee::Employee()
{
    this->workHour = 0;
    this->moneyPerHour = 0;
    this->workDoneList;
    this->workUFList;
}

Employee::Employee(float workHour, float moneyPerHour, vector<Work*> workDoneList, vector<Work*> workUFList)
{
    this->workHour = workHour;
    this->moneyPerHour = moneyPerHour;
    this->workDoneList = workDoneList;
    this->workUFList = workUFList;
}

//============================================Get=============================================
float Employee::getWorkHour() const
{
    return this->workHour;
}

float Employee::getMoneyPerHour() const
{
    return this->moneyPerHour;
}

vector<Work*> Employee::getWorkDones() const
{
    return this->workDoneList;
}

vector<Work*> Employee::getWorkUFs() const
{
    return this->workUFList;
}

float Employee::getSalary()
{
    return this->getTotalMoneyFromWorkHour() + this->getTotalMoneyFromWork();
}

float Employee::getTotalMoneyFromWorkHour() 
{
    return 0;
}

float Employee::getTotalMoneyFromWork()
{
    return 0;
}

//============================================Set=============================================
void Employee::setWorkHour(float workHour)
{
    this->workHour = workHour;
}

void Employee::setMoneyPerHour(float moneyPerHour)
{
    this->moneyPerHour = moneyPerHour;
}

void Employee::setWorkDones(vector<Work*> workDoneList)
{
    this->workDoneList = workDoneList;
}

void Employee::setWorkUFs(vector<Work*> workUFList)
{
    this->workUFList = workUFList;
}

//============================================Work============================================
void Employee::addWorkDone(Work* work)
{
    this->workDoneList.push_back(work);
}

void Employee::addWorkUF(Work* work)
{
    this->workUFList.push_back(work);
}

void Employee::removeWorkDone(Work* work)
{
    for (int i = 0; i < this->workDoneList.size(); i++)
    {
        if (this->workDoneList[i] == work)
        {
            this->workDoneList.erase(this->workDoneList.begin() + i);
            return;
        }
    }
    cout << "Can't find work" << endl;
    pressAnyKey();
}

void Employee::removeWorkUF(Work* work)
{
    for (int i = 0; i < this->workUFList.size(); i++)
    {
        if (this->workUFList[i] == work)
        {
            this->workUFList.erase(this->workUFList.begin() + i);
            return;
        }
    }
    cout << "Can't find work" << endl;
    pressAnyKey();
}

void Employee::addWorkHour(float workHour)
{
    this->workHour += workHour;
}

//=========================================Pay Salary=========================================
void Employee::paySalary()
{
    this->removeAllWorkHour();
    this->removeAllWorkDone();
}

void Employee::removeAllWorkHour()
{
    this->workHour = 0;
}

void Employee::removeAllWorkDone()
{
    this->workDoneList.clear();
}