#include "ManagerMenu.h"
using namespace std;

//============================================Menu============================================
//============================================Main============================================
void ManagerMenu::mainMenu(Manager* manager)
{
    while (true)
    {
        int choice = this->displayMain(manager);

        if (choice == 1) this->informationMenu(manager);
        else if (choice == 2) this->assignWorkMenu(manager->getStaffs(), manager);
        else if (choice == 3) this->paySalaryMenu(manager);
        else if (choice == 4) 
        {
            this->quitMenu();
            return;
        }
    }
}

int ManagerMenu::displayMain(Manager* manager)
{
    clearScreen();

    coutTitle("Manager Menu", "=");
    coutContent("1. Information", "=");
    coutContent("2. Assign Work", "=");
    coutContent("3. Pay Salary", "=");
    coutContent("4. Quit", "=");
    
    cout << "Enter your choice: ";
    int choice = -1;

    if (!cinInt(&choice) || choice < 1 || choice > 4)
    {
        this->displayWrongInput();
        return this->displayMain(manager);
    }
    
    return choice;
}

//========================================Information=========================================
void ManagerMenu::informationMenu(Manager* manager)
{
    clearScreen();
    
    this->displayInformation(manager);
    this->displayPressAnyKey();
}

void ManagerMenu::displayInformation(Manager* manager)
{
    manager->displayPrivateInfo();
}

//========================================Assign Work=========================================
void ManagerMenu::assignWorkMenu(vector<Staff*> staffs, Manager* manager)
{
    clearScreen();

    this->displayAssignWork();
    Staff* chosenStaff = this->displayChooseStaff(staffs);

    if (chosenStaff == nullptr) return;

    vector<Work*> works = manager->getNotAssignedWorks();
    Work* chosenWork = this->displayChooseWork(works, manager);

    if (chosenWork == nullptr)
    {
        this->assignWorkMenu(staffs, manager);
        return;
    }

    WriteWorkFile(chosenWork);
    manager->assignWork(chosenStaff, chosenWork);
}

void ManagerMenu::displayAssignWork()
{
    coutTitle("Assign Work", "=");
}

Staff* ManagerMenu::displayChooseStaff(vector<Staff*> staffs)
{
    clearScreen();

    coutTitle("Choose Staff", "=");
    coutContent("0. Back", "=");

    for (int i = 0; i < staffs.size(); i++)
    {
        string content = to_string(i + 1) + ". " + staffs[i]->getName();
        coutContent(content, "=");
    }

    int choice = -1;
    cout << "Choose Staff: ";
    if (!cinInt(&choice) || choice <= -1 || choice >= staffs.size() + 1)
    {
        this->displayWrongInput();
        return this->displayChooseStaff(staffs);
    }

    if (choice == 0) return nullptr;

    return staffs[choice - 1];
}

Work* ManagerMenu::displayChooseWork(vector<Work*> works, Manager* manager)
{
    clearScreen();

    coutTitle("Choose Work", "=");
    coutContent("0. Create New Work", "=");
    for (int i = 0; i < works.size(); i++)
    {
        string content = to_string(i + 1) + ". " + works[i]->getName();
        coutContent(content, "=");
    }

    int choice = -1;
    cout << "Choose Work: ";
    if (!cinInt(&choice) || choice < 0 || choice > works.size())
    {
        this->displayWrongInput();
        return this->displayChooseWork(works, manager);
    }

    if (choice == 0) 
    {
        return this->displayCreateNewWork(manager);
    }

    return works[choice - 1];
}

Work* ManagerMenu::displayCreateNewWork(Manager* manager)
{
    clearScreen();

    int managerId = manager->getId();
    string name = "_____";
    int bonusCreditPoint = -1;
    float bonusMoney = -1;
    int id = -1;

    string managerIdStr = to_string(managerId);
    string bonusCreditPointStr = "_____";
    string bonusMoneyStr = "_____";
    string idStr = "_____";

    while (true)
    {
        clearScreen();

        if (bonusCreditPoint <= 0) bonusCreditPointStr = "_____";
        if (bonusMoney <= 0) bonusMoneyStr = "_____";
        if (id <= 0) idStr = "_____";

        coutTitle("Create New Work", "=");
        coutContent("Manager Id: " + managerIdStr, "=");
        coutContent("Name: " + name, "=");
        coutContent("Bonus Credit Point: " + bonusCreditPointStr, "=");
        coutContent("Bonus Money: " + bonusMoneyStr, "=");
        coutContent("Id: " + idStr, "=");
        coutContent("=","=");

        if (name == "_____")
        {
            cout << "Enter Name: ";
            cinString(&name);
        }

        else if (bonusCreditPoint <= 0)
        {
            cout << "Enter Bonus Credit Point: ";
            if (!cinInt(&bonusCreditPoint))
            {
                this->displayWrongInput();
                continue;
            }

            if (bonusCreditPoint < 0)
            {
                bonusCreditPoint = -1;
                cout << "Your bonus credit point must be greater than 0" << endl;
                this->displayWrongInput();
                continue;
            }

            bonusCreditPointStr = to_string(bonusCreditPoint);
        }

        else if (bonusMoney <= 0)
        {
            cout << "Enter Bonus Money: ";
            if (!cinFloat(&bonusMoney))
            {
                this->displayWrongInput();
                continue;
            }

            if (bonusMoney < 0)
            {
                bonusMoney = -1;
                cout << "Your bonus money must be greater than 0" << endl;
                this->displayWrongInput();
                continue;
            }

            bonusMoneyStr = to_string(bonusMoney);

            id = random8Number();
            idStr = to_string(id);
        }

        else 
        {
            cout << "Create New Work Successfully" << endl;
            this->displayPressAnyKey();
            break;
        }
    }

    Work* newWork = new Work(bonusCreditPoint, bonusMoney, managerId, name, id);
    return newWork;
}

//=========================================Pay Salary=========================================
void ManagerMenu::paySalaryMenu(Manager* manager)
{
    this->displayPaySalary();
    bool choice = this->displayPaySalary();

    if (choice)
    {
        manager->paySalary();
        this->displayAcceptPaySalary();
        this->displayPressAnyKey();
        return;
    }
    else
    {
        this->displayRefusePaySalary();
        this->displayPressAnyKey();
        return;
    }
}

bool ManagerMenu::displayPaySalary()
{
    clearScreen();

    coutTitle("Pay Salary", "=");
    coutContent("Do you want to pay salary: ", "=");
    coutContent("1. Yes", "=");
    coutContent("2. No", "=");

    int choice = -1;
    cout << "Enter your choice: ";
    if (!cinInt(&choice) || choice <= 0 || choice >= 3)
    {
        this->displayWrongInput();
        return this->displayPaySalary();
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

void ManagerMenu::displayAcceptPaySalary()
{
    cout << "You has pay salary successfully" << endl;
}

void ManagerMenu::displayRefusePaySalary()
{
    cout << "You has refuse to pay salary" << endl;
}

//============================================Quit============================================
bool ManagerMenu::quitMenu()
{
    bool choice = this->displayQuit();
    return choice;
}

bool ManagerMenu::displayQuit()
{
    clearScreen();

    coutTitle("Quit", "=");
    coutContent("1. Yes", "=");
    coutContent("2. No", "=");

    int choice = -1;
    cout << "Enter your choice: ";
    if (!cinInt(&choice) || choice < 1 || choice > 2)
    {
        this->displayWrongInput();
        return this->displayQuit();
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

//===========================================Other============================================
void ManagerMenu::displayWrongInput()
{
    cout << "Wrong Input!" << endl;
    cout << "Press Any Key To Try Again." << endl;
    pressAnyKey();
}

void ManagerMenu::displayPressAnyKey()
{
    cout << "Press Any Key To Continue..." << endl;
    pressAnyKey();
}