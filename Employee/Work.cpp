#include "Work.h"
using namespace std;

//========================================Constructor=========================================
Work::Work()
{
    this->creditPoint = 0;
    this->money = 0;
    this->managerId = 0;
    this->setName("");
    this->setId(0);
}

Work::Work(int creditPoint, float money, int managerId, string name, int id)
{
    this->creditPoint = creditPoint;
    this->money = money;
    this->managerId = managerId;
    this->setName(name);
    this->setId(id);
}

//============================================Get=============================================
int Work::getCreditPoint() const
{
    return this->creditPoint;
}

float Work::getMoney() const
{
    return this->money;
}

int Work::getManagerId() const
{
    return this->managerId;
}

//============================================Set=============================================
void Work::setCreditPoint(int creditPoint)
{
    this->creditPoint = creditPoint;
}

void Work::setMoney(float money)
{
    this->money = money;
}

void Work::setManagerId(int managerId)
{
    this->managerId = managerId;
}