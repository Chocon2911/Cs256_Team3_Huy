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
    string moneyPerHourStr = to_string(this->getMoneyPerHour());
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
    
    coutTitle("Finished Work: ", "-");
    cout << "id - name - money" << endl;
    
    for (int i = 0; i < this->getWorkDones().size(); i++)
    {
        string workDoneName = this->getWorkDones()[i]->getName();
        string workDoneMoney = to_string(this->getWorkDones()[i]->getMoney() * 0.3) + "$";
        string workDoneId = to_string(this->getWorkDones()[i]->getId());

        cout << i + 1 << ". " << workDoneId << " - " << workDoneName << " - " << workDoneMoney << endl; 
    }

    cout << endl;

    coutTitle("Unfinished Work: ", "-");
    cout << "id - name - money" << endl;

    for (int i = 0; i < this->getWorkUFs().size(); i++)
    {
        string workUFName = this->getWorkUFs()[i]->getName();
        string workUFMoney = to_string(this->getWorkUFs()[i]->getMoney() * 0.3) + "$";
        string workUFId = to_string(this->getWorkUFs()[i]->getId());

        cout << i + 1 << ". " << workUFId << " - " << workUFName << " - " << workUFMoney << endl;
    }

    coutContent("=", "=");

    coutTitle("Press any key to continue", "=");
    pressAnyKey();
}

void Staff::displayPublicInfo()
{
    string idStr = to_string(this->getId());
    string nameStr = this->getName();
    string currCreditPointStr = to_string(this->getCurrLevel()->getCurrCreditPoint());
    string currLevelStr = getLevelCodeStr(this->getCurrLevel()->getLevelCode());
    string workHourStr = to_string(this->getWorkHour());
    string moneyPerHourStr = to_string(this->getMoneyPerHour());
    string workDoneAmount = to_string(this->getWorkDones().size());
    string workUFAmount = to_string(this->getWorkUFs().size());
    string totalMoneyFromWorkHour = to_string(this->getTotalMoneyFromWorkHour());
    string totalMoneyFromWorkDone = to_string(this->getTotalMoneyFromWork());
    string totalSalary = to_string(this->getSalary()); 

    // cout << "Id - Name - Credit Point - Current Level - Work Hour - Money Per Hour - Work Done - Work Unfinished - Total Money From Work Hour - Total Money from Work Done - Total Salary" << endl;
    cout << idStr + " - " + nameStr + " - " + currLevelStr + " - " + workHourStr + " - " + moneyPerHourStr + " - " + currCreditPointStr + " - " + workDoneAmount + " - " + workUFAmount + " - " + totalMoneyFromWorkHour + " - " + totalMoneyFromWorkDone + " - " + totalSalary << endl;
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