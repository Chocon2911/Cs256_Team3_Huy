#include "EmployeeLevel.h"

//========================================Constructor=========================================
EmployeeLevel::EmployeeLevel()
{
    this->levelCode = LevelCode::Zero;
    this->moneyPerWorkHour = 0;
    this->creditPointRequired = 0;
}

EmployeeLevel::EmployeeLevel(LevelCode levelCode, float moneyPerWorkHour, int creditPointRequired)
{
    this->levelCode = levelCode;
    this->moneyPerWorkHour = moneyPerWorkHour;
    this->creditPointRequired = creditPointRequired;
}

EmployeeLevel::~EmployeeLevel() 
{
    cout << "Destructor of EmployeeLevel" << endl;
}

//==========================================Operator==========================================
void EmployeeLevel::operator=(const EmployeeLevel* other)
{
    this->moneyPerWorkHour = other->getMoneyPerWorkHour();
    this->creditPointRequired = other->getCreditPointRequired();
}

//==========================================Get Set===========================================
LevelCode EmployeeLevel::getLevelCode() const
{
    return this->levelCode;
}
float EmployeeLevel::getMoneyPerWorkHour() const
{
    return this->moneyPerWorkHour;
}

int EmployeeLevel::getCreditPointRequired() const
{
    return this->creditPointRequired;
}

void EmployeeLevel::setLevelCode(LevelCode levelCode)
{
    this->levelCode = levelCode;
}

void EmployeeLevel::setMoneyPerWorkHour(float moneyPerWorkHour)
{
    this->moneyPerWorkHour = moneyPerWorkHour;
}

void EmployeeLevel::setCreditPointRequired(float creditPointRequired)
{
    this->creditPointRequired = creditPointRequired;
}

//==========================================Display===========================================
void EmployeeLevel::display() const
{
    cout << "Money Per Work Hour: " << this->getMoneyPerWorkHour() << endl;
    cout << "Credit Point Required: " << this->getCreditPointRequired() << endl;
    cout << "Level Code: " << this->getLevelCode() << endl;
}
