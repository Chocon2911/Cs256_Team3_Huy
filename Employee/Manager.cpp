#include "Manager.h"
using namespace std;

vector<Staff*> Manager::staffs;

//========================================Constructor=========================================
Manager::Manager()
{
    notAssignedWorks;
    this->setWorkHour(0);
    this->setMoneyPerHour(0);
    this->setName("");
    this->setId(random8Number());
}

Manager::Manager(vector<Work*> notAssignedWorks, float workHour, float moneyPerHour, vector<Work*> workDones, vector<Work*> workUFs, string name, int id)
{
    this->notAssignedWorks = notAssignedWorks;
    this->setWorkHour(workHour);
    this->setMoneyPerHour(moneyPerHour);
    this->setWorkDones(workDones);
    this->setWorkUFs(workUFs);
    this->setName(name);
    this->setId(id);
}

//============================================Get=============================================
vector<Work*> Manager::getNotAssignedWorks() const
{
    return this->notAssignedWorks;
}

vector<Staff*> Manager::getStaffs() const
{
    return this->staffs;
}

float Manager::getTotalMoneyFromWorkHour()
{
    return this->getWorkHour() * this->getMoneyPerHour();
}

float Manager::getTotalMoneyFromWork()
{
    float totalMoney = 0;
    for (int i = 0; i < this->getNotAssignedWorks().size(); i++)
    {
        totalMoney += this->getNotAssignedWorks()[i]->getMoney() * 0.5;
    }
    return totalMoney;
}

//============================================Set=============================================
void Manager::setNotAssignedWorks(vector<Work*> notAssignedWorks)
{
    this->notAssignedWorks = notAssignedWorks;
}

void Manager::setStaffs(vector<Staff*> staffs)
{
    this->staffs = staffs;
}

//===========================================Other============================================
void Manager::addNotAssignedWorks(Work* work)
{
    this->notAssignedWorks.push_back(work);
}

void Manager::removeNotAssignedWorks(Work* work)
{
    for (int i = 0; i < this->notAssignedWorks.size(); i++)
    {
        if (this->notAssignedWorks[i]->getId() == work->getId())
        {
            this->notAssignedWorks.erase(this->notAssignedWorks.begin() + i);
            return;
        }
    }
}

//==========================================Display===========================================
void Manager::displayPrivateInfo()
{
    string idStr = to_string(this->getId());
    string nameStr = this->getName();
    string workHourStr = to_string(this->getWorkHour());
    string moneyPerHourStr = to_string(this->getMoneyPerHour());

    coutTitle("Manager Information", "=");
    cout << "Id: " + idStr << endl;
    cout << "Name: " + nameStr << endl;
    cout << "Work Hour: " + workHourStr + "h" << endl;
    cout << "Money Per Hour: " + moneyPerHourStr + "$" << endl;
    
    cout << endl;

    coutTitle("Work Done Information", "=");
    cout << "Id - Name - Credit Point - Money" << endl;

    for (int i = 0; i < this->getWorkDones().size(); i++)
    {
        string workDoneId = to_string(this->getWorkDones()[i]->getId());
        string workDoneName = this->getWorkDones()[i]->getName();
        string workDoneCreditPoint = to_string(this->getWorkDones()[i]->getCreditPoint());
        string workDoneMoney = to_string(this->getWorkDones()[i]->getMoney());

        cout << i + 1 << ". " << workDoneId << " - " << workDoneName << " - " << workDoneCreditPoint << " - " << workDoneMoney << endl;
    }

    cout << endl;

    coutTitle("Unfinshed Work", "=");
    cout << "Id - Name - Credit Point - Money" <<endl;

    for (int i = 0; i < this->getWorkUFs().size(); i++)
    {
        string workUFId = to_string(this->getWorkUFs()[i]->getId());
        string workUFName = this->getWorkUFs()[i]->getName();
        string workUFCreditPoint = to_string(this->getWorkUFs()[i]->getCreditPoint());
        string workUFMoney = to_string(this->getWorkUFs()[i]->getMoney());

        cout << i + 1 << ". " << workUFId << " - " << workUFName << " - " << workUFCreditPoint << " - " << workUFMoney << endl;
    }

    cout << endl;

    coutTitle("Not Assigned Work", "=");
    cout << "Id - Name - Credit Point - Money" << endl;
    
    for (int i = 0; i < this->getNotAssignedWorks().size(); i++)
    {
        string notAssignedWorkId = to_string(this->getNotAssignedWorks()[i]->getId());
        string notAssignedWorkName = this->getNotAssignedWorks()[i]->getName();
        string notAssignedWorkCreditPoint = to_string(this->getNotAssignedWorks()[i]->getCreditPoint());
        string notAssignedWorkMoney = to_string(this->getNotAssignedWorks()[i]->getMoney());

        cout << i + 1 << ". " << notAssignedWorkId << " - " << notAssignedWorkName << " - " << notAssignedWorkCreditPoint << " - " << notAssignedWorkMoney << endl;
    }
}

void Manager::displayPublicInfo()
{
    string idStr = to_string(this->getId());
    string nameStr = this->getName();
    string workHourStr = to_string(this->getWorkHour());
    string moneyPerHourStr = to_string(this->getMoneyPerHour());
    string workDoneAmountStr = to_string(this->getWorkDones().size());
    string workUFAmountStr = to_string(this->getWorkUFs().size());
    string notAssignedWorkAmountStr = to_string(this->getNotAssignedWorks().size());

    // cout << "Id - Name - Work Hour - Money Per Hour - Work Done Amount - Unfinshed Work Amount - Not Assigned Work Amount" << endl;
    cout << idStr << " - " << nameStr << " - " << workHourStr << " - " << moneyPerHourStr << " - " << workDoneAmountStr << " - " << workUFAmountStr << " - " << notAssignedWorkAmountStr << endl;
}

//===========================================Other============================================

bool Manager::assignWork(Staff* staff, Work* work)
{
    staff->addWorkUF(work);
    this->removeNotAssignedWorks(work);
    this->addWorkUF(work);

    WriteStaffFile(staff);
    WriteManagerFile(this);

    return true;
}