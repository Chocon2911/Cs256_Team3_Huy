#include "StaffMenu.h"
using namespace std;

//============================================Menu============================================
//============================================Main============================================
void StaffMenu::mainMenu(Staff* staff)
{
    while(true)
    {
        int choice = this->displayMain();
        if (choice == 1)
        {
            this->informationMenu(staff);
        }
        else if (choice == 2)
        {
            this->addWorkHourAmountMenu(staff);
        }
        else if (choice == 3)
        {
            this->paySalaryMenu(staff);
        }
        else if (choice == 4)
        {
            this->promoteMenu(staff);
        }
        else if (choice == 5)
        {
            this->demoteMenu(staff);
        }

        else if (choice == 6)
        {
            if (!this->removeAccountMenu(staff)) continue;
            break;
        }

        else if (choice == 7)
        {
            if (!this->quitMenu()) continue;
            break;
        }
        else
        {
            this->wrongInput();
        }
    }
}

int StaffMenu::displayMain()
{
    clearScreen();

    int choice = -1;

    coutTitle("Staff Menu", "=");
    coutContent("1. Information", "=");
    coutContent("2. Add Work Hour Amount", "=");
    coutContent("3. Pay Salary", "=");
    coutContent("4. Promote", "=");
    coutContent("5. Demote", "=");
    coutContent("6. Remove Account", "=");
    coutContent("7. Quit", "=");
    cout << "Enter Choice: ";
    if (!cinInt(&choice) || choice < 1 || choice > 7)
    {
        this->wrongInput();
        return this->displayMain();
    }

    return choice;
}

//=========================================Infomation=========================================
void StaffMenu::informationMenu(Staff* staff)
{
    this->displayInformation(staff);
}

void StaffMenu::displayInformation(Staff* staff)
{
    staff->displayPrivateInfo();
}

//====================================Add Work Hour Amount====================================
void StaffMenu::addWorkHourAmountMenu(Staff* staff)
{
    this->displayAddWorkHourAmount(staff, 0);
}

void StaffMenu::displayAddWorkHourAmount(Staff* staff, float addWorkHour)
{
    clearScreen();

    string workHourStr = "_____";
    if (addWorkHour > 0) workHourStr = to_string(addWorkHour);

    coutTitle("Add Work Hour Amount", "=");
    coutContent("Add Work Hour Amoount: " + workHourStr + " (hour)", "=");

    if (addWorkHour <= 0)
    {
        cout << "Enter Add Work Hour Amount: ";
        if (!cinFloat(&addWorkHour))
        {
            addWorkHour = 0;
        }

        this->displayAddWorkHourAmount(staff, addWorkHour);
    }

    else
    {
        staff->addWorkHour(addWorkHour);
        WriteStaffFile(staff);

        cout << "Add Work Hour Success!" << endl;
        cout << "Press any key to continue..." << endl;
        pressAnyKey();
    }
}

//==========================================Promote===========================================
void StaffMenu::promoteMenu(Staff* staff)
{
    int nextLevelIndex = int(staff->getCurrLevel()->getLevelCode()) + 1;
    if (nextLevelIndex > staff->getCurrLevel()->getEmployeeLevels().size())
    {
        //Can make it upgrade to Manager
        this->displayCantPromote();
        return;
    }

    EmployeeLevel* nextLevel = staff->getCurrLevel()->getEmployeeLevels()[nextLevelIndex - 1];
    int creditPointRequired2LevelUp = nextLevel->getCreditPointRequired();
    float nextLevelMoneyPerHour = nextLevel->getMoneyPerWorkHour(); 
    LevelCode currLevelCode = staff->getCurrLevel()->getLevelCode();

    string nextLevelCreditPointStr = to_string(creditPointRequired2LevelUp);
    string nextLevelMoneyPerHourStr = to_string(nextLevelMoneyPerHour);
    string nextLevelCodeStr = getLevelCodeStr(nextLevel->getLevelCode());

    bool choice = this->displayPromote(nextLevelCodeStr, nextLevelCreditPointStr, nextLevelMoneyPerHourStr);

    if (!choice)
    {
        this->displayRefusePromote();
        return;
    }

    else
    {
        this->displayAcceptPromote();
        staff->getCurrLevel()->Promote();
        WriteStaffFile(staff);
        return;
    }
}

bool StaffMenu::displayPromote(string nextLevelCode, string nextLevelCreditPoint, string nextLevelMoneyPerHour)
{
    clearScreen();
    coutTitle("Promote", "=");
    coutContent("Next Level: " + nextLevelCode, "=");
    coutContent("Credit Point Required: " + nextLevelCreditPoint, "=");
    coutContent("Money Per Work Hour: " + nextLevelMoneyPerHour, "=");

    cout << "Do you want to promote?: " << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;

    int choice = -1;
    cout << "Enter your choice: ";
    if (!cinInt(&choice) || choice < 1 || choice > 2)
    {
        this->wrongInput();
        return this->displayPromote(nextLevelCode, nextLevelCreditPoint, nextLevelMoneyPerHour);
    }

    else 
    {
        if (choice == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

void StaffMenu::displayRefusePromote()
{
    cout << "Refuse promote!" << endl;
    cout << "Press any key to continue..." << endl;
    pressAnyKey();
}

void StaffMenu::displayAcceptPromote()
{
    cout << "Accept promote!" << endl;
    cout << "Press any key to continue..." << endl;
    pressAnyKey();
}

void StaffMenu::displayCantPromote()
{
    cout << "Can't promote Any further!" << endl;
    cout << "Press any key to continue..." << endl;
    pressAnyKey();
}

//===========================================Demote===========================================
void StaffMenu::demoteMenu(Staff* staff)
{
    int prevLevelIndex = int(staff->getCurrLevel()->getLevelCode()) - 1;
    if (prevLevelIndex <= 1)
    {
        //Can make it upgrade to Manager
        this->displayCantDemote();
        return;
    }

    EmployeeLevel* prevLevel = staff->getCurrLevel()->getEmployeeLevels()[prevLevelIndex];
    int creditPointRequired2LevelUp = prevLevel->getCreditPointRequired();
    float prevLevelMoneyPerHour = prevLevel->getMoneyPerWorkHour(); 
    LevelCode currLevelCode = staff->getCurrLevel()->getLevelCode();

    string prevLevelCreditPointStr = to_string(creditPointRequired2LevelUp);
    string prevLevelMoneyPerHourStr = to_string(prevLevelMoneyPerHour);
    string prevLevelCodeStr = getLevelCodeStr(prevLevel->getLevelCode());

    bool choice = this->displayDemote(prevLevelCodeStr, prevLevelCreditPointStr, prevLevelMoneyPerHourStr);

    if (!choice)
    {
        this->displayRefuseDemote();
        return;
    }

    else
    {
        staff->getCurrLevel()->Demote();
        this->displayAcceptDemote();
        WriteStaffFile(staff);
        return;
    }
}

bool StaffMenu::displayDemote(string prevLevelCode, string prevLevelCreditPoint, string LevelMoneyPerHour)
{
    clearScreen();
    coutTitle("Demote", "=");
    coutContent("Prev Level: " + prevLevelCode, "=");
    coutContent("Credit Point Required: " + prevLevelCreditPoint, "=");
    coutContent("Money Per Work Hour: " + LevelMoneyPerHour, "=");

    cout << "Do you want to demote?: " << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;

    int choice = -1;
    cout << "Enter your choice: ";
    if (!cinInt(&choice) || choice < 1 || choice > 2)
    {
        this->wrongInput();
        return this->displayDemote(prevLevelCode, prevLevelCreditPoint, LevelMoneyPerHour);
    }

    else
    {
        if (choice == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    return false;
}

void StaffMenu::displayCantDemote()
{
    clearScreen();
    cout << "Can't demote Any further!" << endl;
    cout << "Press any key to continue..." << endl;
    pressAnyKey();
}

void StaffMenu::displayRefuseDemote()
{
    clearScreen();
    cout << "Staff didn't level up" << endl;
    cout << "Press any key to continue..." << endl;
    pressAnyKey();
}

void StaffMenu::displayAcceptDemote()
{
    clearScreen();
    cout << "Staff has been level up successfully" << endl;
    cout << "Press any key to continue..." << endl;
    pressAnyKey();
}

//=========================================Pay Salary=========================================
void StaffMenu::paySalaryMenu(Staff* staff)
{
    float workHourAmount = staff->getWorkHour();
    string workHourAmountStr = to_string(workHourAmount);

    bool choice = this->displayPaySalary(workHourAmountStr);

    if (choice)
    {
        staff->paySalary();
        this->displayAcceptPaySalary();
        cout << "Press Any Key to Continue..." << endl;
        pressAnyKey();
    }

    else
    {
        this->displayRefusePaySalary();
        cout << "Press Any Key to Continue..." << endl;
        pressAnyKey();
    }
}

bool StaffMenu::displayPaySalary(string workHourAmount)
{
    clearScreen();
    coutTitle("Pay Salary", "=");
    coutContent("Work Hour Amount: " + workHourAmount + " (Hour)", "=");
    coutContent("Do you want to pay salary: ", "=");
    coutContent("1. Yes", "=");
    coutContent("2. No", "=");

    int choice = -1;
    if (!cinInt(&choice) || choice < 1 || choice > 2)
    {
        this->wrongInput();
        return this->displayPaySalary(workHourAmount);
    }

    else
    {
        if (choice == 1)
        {
            return true;
        }               

        else 
        {
            return false;
        }                                                                                     
    }

    return false;
}

void StaffMenu::displayAcceptPaySalary()
{
    clearScreen();
    cout << "You has pay salary successfully" << endl;
}

void StaffMenu::displayRefusePaySalary()
{
    clearScreen();
    cout << "You hasn't pay salary" << endl;
}

//=======================================Remove Account=======================================
bool StaffMenu::removeAccountMenu(Staff* staff)
{
    bool choice = this->displayRemoveAccount();

    if (choice)
    {
        staff->removeAccount();
        this->displayAcceptRemoveAccount();
        cout << "Press Any Key to Continue..." << endl;
        pressAnyKey();
        return true;
    }

    else 
    {
        this->displayRefuseRemoveAccount();
        cout << "Press Any Key to Continue..." << endl;
        pressAnyKey();
        return false;
    }

    return false;
}

bool StaffMenu::displayRemoveAccount()
{
    clearScreen();

    coutTitle("Remove Account", "=");
    coutContent("Do you want to remove this account?", "=");
    coutContent("1. Yes", "=");
    coutContent("2. No", "=");

    int choice = -1;
    if (!cinInt(&choice) || choice < 1 || choice > 2)
    {
        this->wrongInput();
        return this->displayRemoveAccount();
    }

    else 
    {
        if (choice == 1)
        {
            return true;
        }

        else 
        {
            return false;
        }
    }

    return false;
}

void StaffMenu::displayAcceptRemoveAccount()
{
    cout << "Remove Account Successfully!" << endl;
}

void StaffMenu::displayRefuseRemoveAccount()
{
    cout << "Remove Account Failed!" << endl;
}

//============================================Quit============================================
bool StaffMenu::quitMenu()
{
    bool choice = this->displayQuit();

    if (choice)
    {
        this->displayAcceptQuit();
        cout << "Press Any Key to Continue..." << endl;
        pressAnyKey();
        return choice;
    }

    this->displayRefuseQuit();
    cout << "Press Any Key to Continue" << endl;
    pressAnyKey();
    return choice;
}

bool StaffMenu::displayQuit()
{
    clearScreen();
    coutTitle("Quit", "=");
    coutContent("1. Yes", "=");
    coutContent("2. No", "=");

    int choice = -1;
    if (!cinInt(&choice) || choice <= 0 || choice >= 3)
    {
        this->wrongInput();
        return this->displayQuit();
    }

    else
    {
        if (choice == 1)
        {
           return true; 
        }

        else if (choice == 2)
        {
            return false;
        }
    }

    return false;
}

void StaffMenu::displayAcceptQuit()
{
    cout << "You has Quit successfully" << endl;
}

void StaffMenu::displayRefuseQuit()
{
    cout << "You has refuse to Quit" << endl;
}

//===========================================Other============================================
void StaffMenu::wrongInput()
{
    cout << "Wrong input!" << endl;
    cout << "Press Any Key To Try Again." << endl;
    pressAnyKey();
}
