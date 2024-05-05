#include "Level.h"

vector<EmployeeLevel*> Level::employeeLevels;

//========================================Constructor=========================================
Level::Level()
{
    this->currCreditPoint = 0;
    this->levelCode = LevelCode::Zero;
}

Level::Level(int currCreditPoint, LevelCode levelCode)
{
    this->currCreditPoint = currCreditPoint;
    this->levelCode = levelCode;
}

//==========================================Get Set===========================================
int Level::getCurrCreditPoint() const
{
    return this->currCreditPoint;
}

LevelCode Level::getLevelCode() const
{
    return this->levelCode;
}

vector<EmployeeLevel*> Level::getEmployeeLevels() const
{
    return this->employeeLevels;
}

void Level::setCurrCreditPoint(int currCreditPoint)
{
    this->currCreditPoint = currCreditPoint;
}

void Level::setLevelCode(LevelCode levelCode)
{
    this->levelCode = levelCode;
}

void Level::setEmployeeLevels(vector<EmployeeLevel*> employeeLevels)
{
    this->employeeLevels = employeeLevels;
}

void Level::addEmployeeLevel(EmployeeLevel* employeeLevel)
{
    this->employeeLevels.push_back(employeeLevel);
}

void Level::removeEmployeeLevel(EmployeeLevel* deleteEmployeeLevel)
{
    for (auto employeeLevel = employeeLevels.begin(); employeeLevel != employeeLevels.end(); ++employeeLevel)
    {
        if (*employeeLevel == deleteEmployeeLevel)
        {
            employeeLevels.erase(employeeLevel);
            break;
        }
    }

    cout << "Error: Can't find any employee the same as this LevelCode: " + deleteEmployeeLevel->getLevelCode() << endl;
}

//========================================Modify Level========================================
bool Level::Promote()
{
    if (this->levelCode >= this->employeeLevels.size()) return false;
    if (this->currCreditPoint < this->employeeLevels[this->levelCode - 1]->getCreditPointRequired()) return false;
    
    this->levelCode = static_cast<LevelCode>(static_cast<int>(this->levelCode) + 1);
    return true;
}

bool Level::Demote()
{
    if (this->levelCode <= 1) return false;
    this->levelCode = static_cast<LevelCode>(static_cast<int>(this->levelCode) - 1);
    return true;
}