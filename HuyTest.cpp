#include <iostream>
#include <limits>
#include <vector>

//Other
#include "Other/Utils.cpp"
#include "Other/EmployeeLevel.cpp"
#include "Other/Level.cpp"

// Employee
#include "Employee/Stat.cpp"
#include "Employee/Employee.cpp"
#include "Employee/Work.cpp"
#include "Employee/Manager.cpp"
#include "Employee/Staff.cpp"

//Menu
#include "Menu/MainMenu.cpp"
#include "Menu/ManagerMenu.cpp"
#include "Menu/StaffMenu.cpp"

using namespace std;

int main() 
{
    start();

    MainMenu mainMenu;
    StaffMenu staffMenu;
    ManagerMenu managerMenu;

    vector<Staff*> staffs;
    vector<Manager*> managers;
    vector<EmployeeLevel*> employeeLevels;

    employeeLevels = ReadAllLevelFile();
    staffs = ReadAllStaffFile();
    managers = ReadAllManagerFile();

    while(true)
    {
        int choice = mainMenu.mainMenu();

        //======================================Add New Employee======================================
        if (choice == 1)
        {   
            bool found = false;
            int newEmployeeId = mainMenu.addNewEmployeeMenu();

            staffs = ReadAllStaffFile();
            managers = ReadAllManagerFile();

            if (newEmployeeId == -1) continue;
            
            for (int i = 0; i < staffs.size(); i++)
            {
                if (staffs[i]->getId() == newEmployeeId)
                {
                    staffMenu.mainMenu(staffs[i]);
                    
                    found = true;
                    staffs = ReadAllStaffFile();
                    managers = ReadAllManagerFile();
                    break;
                }
            }

            if (found) continue;

            for (int i = 0; i < managers.size(); i++)
            {
                if (managers[i]->getId() == newEmployeeId)
                {
                    managerMenu.mainMenu(managers[i]);

                    found = true;
                    staffs = ReadAllStaffFile();
                    managers = ReadAllManagerFile();
                    break;
                }
            }

            if (!found) cout << "Error in Adding New Employee" << endl;
        }

        //=======================================Find Employee========================================
        else if (choice == 2)
        {
            bool foundId = false;
            int inputId = mainMenu.findEmployeeMenu();

            for (int i = 0; i < staffs.size(); i++)
            {
                if (staffs[i]->getId() == inputId)
                {
                    staffMenu.mainMenu(staffs[i]);

                    foundId = true;
                    staffs = ReadAllStaffFile();
                    managers = ReadAllManagerFile();
                    break;
                }
            }

            if (foundId) continue;

            for (int i = 0; i < managers.size(); i++)
            {
                if (managers[i]->getId() == inputId)
                {           
                    managerMenu.mainMenu(managers[i]);
                    
                    foundId = true;
                    staffs = ReadAllStaffFile();
                    managers = ReadAllManagerFile(); 
                    break;
                }
            }

            if (foundId) continue; 
            
            cout << "Id " + to_string(inputId) + " not found" << endl;
            cout << "Press any key to continue..." << endl;
            pressAnyKey();
        }

        //===================================Modify Employee Level====================================
        else if (choice == 3)
        {
            mainMenu.modifyEmployeeLevelMenu(employeeLevels);

            // Update Level File List
            employeeLevels = ReadAllLevelFile();
        }
        
        //======================================All Information=======================================
        else if (choice == 4)
        {
            staffs = ReadAllStaffFile();
            managers = ReadAllManagerFile();
            mainMenu.allInformationMenu(staffs, managers);
        }

        //============================================Exit============================================
        else if (choice == 5)
        {
            mainMenu.exitMenu();
            break;
        }

        //========================================Wrong Input=========================================
        else
        {
            cout << "Wrong Choice" << endl;
            mainMenu.displayWrongInput();
            continue;
        }
    }

    return 0;
}
