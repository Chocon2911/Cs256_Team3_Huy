#include "Staff.h"
using namespace std;

//========================================Constructor=========================================
Staff::Staff()
{
    this->currLevel = NULL;
    this->setWorkHour(0);
    this->setMoneyPerHour(0);
    this->setName("");
    this->setId(0);
}

Staff::Staff(Level* level, float workHour, float moneyPerHour, vector<Work*> workDones, vector<Work*> workUFs , string name, int id)
{
    this->currLevel = level;
    this->setWorkHour(workHour);
    this->setMoneyPerHour(moneyPerHour);
    this->setWorkDones(workDones);
    this->setWorkUFs(workUFs);
    this->setName(name);
    this->setId(id);
}

//============================================Get=============================================
Level* Staff::getCurrLevel() const
{
    return this->currLevel;
}

float Staff::getTotalMoneyFromWorkHour()
{
    return this->getWorkHour() * this->getMoneyPerHour();
}

float Staff::getTotalMoneyFromWork()
{
    float totalMoney = 0;

    for (int i = 0; i < this->getWorkDones().size(); i++)
    {
        totalMoney += this->getWorkDones()[i]->getMoney() * 0.3;
    }

    return totalMoney;
}

//============================================Set=============================================
void Staff::setCurrLevel(Level* currLevel)
{
    this->currLevel = currLevel;
}

//==========================================Display===========================================
void Staff::displayPrivateInfo()
{
    string idStr = to_string(this->getId());
    string nameStr = this->getName();

    string workHourStr = to_string(this->getWorkHour());
    removeLast4Char(&workHourStr);

    string moneyPerHourStr = to_string(this->getMoneyPerHour());
    removeLast4Char(&moneyPerHourStr);

    string currLevelStr = getLevelCodeStr(this->getCurrLevel()->getLevelCode());
    string currCreditPointStr = to_string(this->getCurrLevel()->getCurrCreditPoint());

    coutTitle("Staff Information", "=");
    coutContent("Id: " + idStr, "=");
    coutContent("Name: " + nameStr, "=");
    coutContent("Work Hour: " + workHourStr + "h", "=");
    coutContent("Money Per Hour: " + moneyPerHourStr + "$", "=");
    coutContent("Current Level: " + currLevelStr, "=");
    coutContent("Credit Point: " + currCreditPointStr, "=");

    cout << endl;
    
    coutTitle("Finished Work: ", "=");
    cout << "id - name - credit point - money" << endl;
    
    for (int i = 0; i < this->getWorkDones().size(); i++)
    {
        cout << i + 1 << ". ";
        this->getWorkDones()[i]->displayInformation();    
    }

    cout << endl;

    coutTitle("Unfinished Work: ", "=");
    cout << "id - name - credit point - money" << endl;

    for (int i = 0; i < this->getWorkUFs().size(); i++)
    {
        cout << i + 1 << ". ";
        this->getWorkUFs()[i]->displayInformation();
    }

    cout << "Press any key to continue" << endl;
    pressAnyKey();
}

void Staff::displayPublicInfo()
{
    string idStr = to_string(this->getId());
    string nameStr = this->getName();
    string currCreditPointStr = to_string(this->getCurrLevel()->getCurrCreditPoint());
    string currLevelStr = getLevelCodeStr(this->getCurrLevel()->getLevelCode());

    string totalSalary = to_string(this->getSalary()); 
    removeLast4Char(&totalSalary);
    totalSalary += "$";

    // cout << "Id - Name - Current Level - Credit Point - Total Salary" << endl;
    cout << idStr + " - " + nameStr + " - " + currLevelStr + " - " + currCreditPointStr + " - " + totalSalary << endl;
}

//==========================================Account===========================================
void Staff::removeAccount()
{
    for (int i = 0; i < this->getWorkUFs().size(); i++)
    {
        Manager* manager = ReadManagerFile(to_string(this->getWorkUFs()[i]->getManagerId()));
        Staff* staff = this;

        manager->removeWorkUF(this->getWorkUFs()[i]);
        manager->addNotAssignedWorks(this->getWorkUFs()[i]);

        WriteManagerFile(manager);
        RemoveStaffFile(to_string(this->getId()));
    }
}