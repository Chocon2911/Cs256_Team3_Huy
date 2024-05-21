#include "MainMenu.h"
//============================================================================================
//==========================================Display===========================================
//============================================================================================

//=========================================Main Menu==========================================
int MainMenu::mainMenu()
{
    int choice = this->displayMainMenu();

    if (choice < 1 || choice > 5)
    {
        cout << "Your choice must be in range 1 - 5." << endl;
        this->displayWrongInput();
        return this->mainMenu();
    }

    return choice;
}

int MainMenu::displayMainMenu()
{
    clearScreen();

    int choice = -1;
    coutTitle("CorpManagement", "=");
    coutContent("1. Add New Employee", "=");
    coutContent("2. Find Employee", "=");
    coutContent("3. Modify Employee Level Table", "=");
    coutContent("4. Display All Employee Information", "=");
    coutContent("5. Exit", "=");

    cout << "Enter your choice: ";
    if (!cinInt(&choice))
    {
        this->displayWrongInput();
        return this->displayMainMenu();
    }

    return choice;
}

//======================================Add New Employee======================================
int MainMenu::addNewEmployeeMenu()
{
    string job = "_____";
    string name = "_____";
    int id = -1;
    float moneyPerHour = -1;
    LevelCode levelCode = LevelCode::Zero;

    this->displayAddNewEmployee(&job, &name, &id, &moneyPerHour, &levelCode);
    
    if (job == "Exit")
    {
        return 0;
    }

    //Write File Base on Job
    if (job == "Manager") 
    {
        cout << "Done, press any key to continue." << endl;
        pressAnyKey();

        Manager* newManager = new Manager(vector<Work*>(), 0, moneyPerHour, vector<Work*>(), vector<Work*>(), name, id);
        WriteManagerFile(newManager);

        return id;
    }
    else if (job == "Staff")
    {
        EmployeeLevel* employeeLevel = ReadLevelFile(levelCode);
        Level* newLevel = new Level(employeeLevel->getCreditPointRequired(), employeeLevel->getLevelCode()); 
        float newMoneyPerHour = employeeLevel->getMoneyPerWorkHour();

        cout << "Done, press any key to continue." << endl;
        pressAnyKey();

        Staff* newStaff = new Staff(newLevel, 0, newMoneyPerHour, vector<Work*>(), vector<Work*>(), name, id);
        WriteStaffFile(newStaff);

        return id;
    }

    cout << "Error!" << endl;
    return -1;
}

void MainMenu::displayAddNewEmployee(string* job, string* name, int* id, float* moneyPerHour, LevelCode* levelCode)
{
    clearScreen();

    string choice = "";
    string idStr = "_____";
    if (*id >= 0) idStr = to_string(*id);

    if (*job == "_____")
    {
        coutTitle("Add New Employee", "=");
        cout << "Choose a job: " << endl;
        cout << "1. Manager" << endl;
        cout << "2. Staff" << endl;
        cout << "3. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> (choice);

        if (choice == "1") *job = "Manager";
        else if (choice == "2") *job = "Staff";
        else if (choice == "3") 
        {
            *job = "Exit";
            return;
        }
        else
        {
            cout << "Your choice must be in range 1 - 2." << endl;
            this->displayWrongInput();
        }
        
        return this->displayAddNewEmployee(job, name, id, moneyPerHour, levelCode);
    }

    coutTitle("Add New Employee", "=");
    coutContent("Job: " + *job, "=");

    if (*job == "Manager")
    {
        if (*moneyPerHour <= 0.0f)
        {
            coutContent("Money Per Hour: _____", "=");
        }
        else
        {
            string moneyPerHourStr = to_string(*moneyPerHour);
            removeLast4Char(&moneyPerHourStr);

            coutContent("Money Per Hour: " + moneyPerHourStr + "$", "=");
        }
    }

    coutContent("Name: " + *name, "=");
    coutContent("ID: " + idStr, "=");
    coutContent("=", "=");

    if (*moneyPerHour <= 0.0f && *job == "Manager")
    {
        cout << "Enter money per hour: ";
        if (!cinFloat(moneyPerHour))
        {
            if (*moneyPerHour <= 0.0f) 
            {
                *moneyPerHour = -1;
                cout << "Money per hour must be greater than 0." << endl;
            }

            this->displayWrongInput();
            return this->displayAddNewEmployee(job, name, id, moneyPerHour, levelCode);
        }
    }

    else if (*name == "_____")
    {
        cout << "Enter name: ";
        cinString(name);
    }

    else if (*id <= 0)
    {
        random8Number(id);
    }

    else if (*levelCode == LevelCode::Zero && *job == "Staff")
    {
        cout << "Choose a level: " << endl;
        cout << "1. Itern" << endl;
        cout << "2. Fresher" << endl;
        cout << "3. Junior" << endl;
        cout << "4. Senior" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == "1") *levelCode = LevelCode::Intern;
        else if (choice == "2") *levelCode = LevelCode::Fresher;
        else if (choice == "3") *levelCode = LevelCode::Junior;
        else if (choice == "4") *levelCode = LevelCode::Senior;
        else
        {
            cout << "Your choice must be in range 1 - 4." << endl;
            this->displayWrongInput();
        }
    }

    else
    {        
        return;
    }

    return this->displayAddNewEmployee(job, name, id, moneyPerHour, levelCode);
}

//=======================================Find Employee========================================
int MainMenu::findEmployeeMenu()
{
    int id = -1;

    this->displayFindEmployee(id);
    cout << "Enter the Id: ";

    if (!cinInt(&id))
    {
        this->displayWrongInput();
        return findEmployeeMenu();
    }
    
    this->displayFindEmployee(id);
    cout << "Done, press any key to continue." << endl;
    pressAnyKey();

    clearScreen();
    return id;
}

void MainMenu::displayFindEmployee(int id)
{
    clearScreen();

    string idStr = "_____";
    if (id >= 0) idStr = to_string(id);

    coutTitle("Find Employee", "=");
    coutContent("Id: " + idStr, "=");
    coutContent("=", "=");
}

//====================================Modify EmployeeLevel====================================
void MainMenu::modifyEmployeeLevelMenu(vector<EmployeeLevel*> employeeLevels)
{
    //Display Table
    clearScreen();

    int index = this->displayEmployeeLevelTable();
    float moneyPerWorkHour = employeeLevels[index]->getMoneyPerWorkHour();
    int creditPoint = employeeLevels[index]->getCreditPointRequired();
    EmployeeLevel* newEmployeeLevel = displayModifyEmployeeLevel(employeeLevels, index, moneyPerWorkHour, creditPoint);
    employeeLevels[index] = newEmployeeLevel;

    //Write File
    WriteLevelFile(employeeLevels[index]->getLevelCode(), employeeLevels[index]->getMoneyPerWorkHour(), employeeLevels[index]->getCreditPointRequired());

    //Display Main Menu
    cout << "Done, press any key to continue." << endl;
    pressAnyKey();
}

int MainMenu::displayEmployeeLevelTable()
{
    clearScreen();

    coutTitle("Modify Employee Level Table", "=");
    coutContent("1. Intern", "=");
    coutContent("2. Fresher", "=");
    coutContent("3. Junior", "=");
    coutContent("4. Senior", "=");
    coutContent("=", "=");

    int choice;
    cout << "Enter your choice: ";

    if (!cinInt(&choice))
    {
        if (choice < 1 || choice > 4)
        {
            cout << "Your choice must be in range 1 - 4." << endl;
            this->displayWrongInput();
            this->displayEmployeeLevelTable();
        }
    }

    return choice - 1;
}

EmployeeLevel* MainMenu::displayModifyEmployeeLevel(vector<EmployeeLevel*> employeeLevels, int index, float moneyPerWorkHour, int creditPointRequired)
{
    clearScreen();

    string levelCodeStr = getLevelCodeStr(employeeLevels[index]->getLevelCode());

    string moneyrPerWorkHourStr = to_string(moneyPerWorkHour);
    removeLast4Char(&moneyrPerWorkHourStr);

    string creditPointRequiredStr = to_string(creditPointRequired);


    coutTitle(levelCodeStr, "=");
    coutContent("Current Money Per Work Hour: " + moneyrPerWorkHourStr, "=");
    coutContent("Current Credit Point Required: " + creditPointRequiredStr, "=");
    coutTitle("=", "=");

    // New Money Per Work Hour
    float newMoneyPerWorkHour = -1;
    cout << "Enter new Money Per Work Hour: ";
    if (!cinFloat(&newMoneyPerWorkHour))
    {
        this->displayWrongInput();
        return this->displayModifyEmployeeLevel(employeeLevels, index, moneyPerWorkHour, creditPointRequired);
    }

    else if (!this->checkIfMoneyPerWorkHourGood(employeeLevels, index, newMoneyPerWorkHour))
    {
        this->displayWrongInput();
        return this->displayModifyEmployeeLevel(employeeLevels, index, moneyPerWorkHour, creditPointRequired);
    }

    // New Credit Point Required
    int newCreditPointRequired = -1;
    cout << "Enter new Credit Point Required: ";

    if (!cinInt(&newCreditPointRequired))
    {
        this->displayWrongInput();
        return this->displayModifyEmployeeLevel(employeeLevels, index, moneyPerWorkHour, creditPointRequired);
    }

    else if (!this->checkIfCreditPointGood(employeeLevels, index, newCreditPointRequired))
    {
        this->displayWrongInput();
        return this->displayModifyEmployeeLevel(employeeLevels, index, moneyPerWorkHour, creditPointRequired);
    }

    return new EmployeeLevel(employeeLevels[index]->getLevelCode(), newMoneyPerWorkHour, newCreditPointRequired);
}

bool MainMenu::checkIfMoneyPerWorkHourGood(vector<EmployeeLevel*> employeeLevels, int index, float moneyPerWorkHour)
{
    // MoneyPerWorkHour of previous and next employeeLevel (Ex: curr: Fresher, previous: Intern, next: Junior)
    float previousMoneyPerWorkHour = -1;
    float nextMoneyPerWorkHour = -1;

    if (index <= 0)
    {
        previousMoneyPerWorkHour = 0;
        nextMoneyPerWorkHour = employeeLevels[index + 1]->getMoneyPerWorkHour();
    }

    else if (index >= employeeLevels.size() - 1)
    {
        previousMoneyPerWorkHour = employeeLevels[index - 1]->getMoneyPerWorkHour();
        nextMoneyPerWorkHour = INFINITY;
    }

    else 
    {
        previousMoneyPerWorkHour = employeeLevels[index - 1]->getMoneyPerWorkHour();
        nextMoneyPerWorkHour = employeeLevels[index + 1]->getMoneyPerWorkHour();
    }

    if (moneyPerWorkHour > previousMoneyPerWorkHour && moneyPerWorkHour < nextMoneyPerWorkHour)
    {
        return true;
    }

    cout << "Your new Money Per Work Hour must be in range (" << previousMoneyPerWorkHour << ", " << nextMoneyPerWorkHour << ")" << endl;
    return false;
}

bool MainMenu::checkIfCreditPointGood(vector<EmployeeLevel*> employeeLevels, int index, int creditPointRequired)
{
    // CreditPointRequired of previous and next employeeLevel (Ex: curr: Fresher, previous: Intern, next: Junior)
    int previousCreditPointRequired = -1;
    int nextCreditPointRequired = -1;

    if (index <= 0)
    {
        previousCreditPointRequired = 0;
        nextCreditPointRequired = employeeLevels[index + 1]->getCreditPointRequired();
    }

    else if (index >= employeeLevels.size() - 1)
    {
        previousCreditPointRequired = employeeLevels[index - 1]->getCreditPointRequired();
        nextCreditPointRequired = numeric_limits<int>::max();
    }

    else
    {
        previousCreditPointRequired = employeeLevels[index - 1]->getCreditPointRequired();
        nextCreditPointRequired = employeeLevels[index + 1]->getCreditPointRequired();
    }

    if (creditPointRequired > previousCreditPointRequired && creditPointRequired < nextCreditPointRequired)
    {
        return true;
    }

    cout << "Your new Credit Point Required must be in range (" << previousCreditPointRequired << ", " << nextCreditPointRequired << ")" << endl;
    return false;
}

//======================================All Information=======================================
void MainMenu::allInformationMenu(vector<Staff*> staffs, vector<Manager*> managers)
{
    clearScreen();
    
    coutTitle("Manager", "=");
    this->displayManagerIn4(managers);
    coutTitle("Staff", "=");
    this->displayStaffIn4(staffs);

    cout << "Press any key to continue." << endl;
    pressAnyKey();
}

void MainMenu::displayManagerIn4(vector<Manager*> managers)
{
    cout << "Id - Name - Salary" << endl;
    for (int i = 0; i < managers.size(); i++)
    {
        managers[i]->displayPublicInfo();
    }
}

void MainMenu::displayStaffIn4(vector<Staff*> staffs)
{
    cout << "Id - Name - Current Level - Credit Point - Salary" << endl;
    for (int i = 0; i < staffs.size(); i++)
    {
        staffs[i]->displayPublicInfo();
    }
}

//============================================Exit============================================
void MainMenu::exitMenu()
{
    clearScreen();
    coutTitle("Thank you for using CorpManagement", "=");
    exit(0);
}

//===========================================Other============================================
void MainMenu::displayWrongInput()
{
    cout << "Press any Key to try again." << endl;
    pressAnyKey();
}
