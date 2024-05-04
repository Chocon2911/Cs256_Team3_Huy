#pragma once
#include <iostream>
#include <limits>
#include <cstdlib>
#include <conio.h>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;

// Other
#include "LevelCode.h"
#include "EmployeeLevel.h"
#include "Level.h"

// Employee
#include "../Employee/Stat.h"
#include "../Employee/Employee.h"
#include "../Employee/Manager.h"
#include "../Employee/Staff.h"
#include "../Employee/Work.h"
using namespace std;

//============================================Cin=============================================
bool cinInt(int* number)
{
    if (!(cin >> *number)) 
    {
        cout << "Invalid input. Please enter an integer" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

bool cinFloat(float* number)
{
    if (!(cin >> *number)) 
    {
        cout << "Invalid input. Please enter a float" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

void cinString(string* str)
{
    cin.ignore();
    getline(cin, *str);
}

//============================================Cout============================================
void coutTitle(string title, string sign)
{
    int length = 92;
    string result;
    length -= title.size();

    for (int i = 0; i < length / 2; i++)
    {
        result.append(sign);
        cout << sign;
    }
    result.append(title);
    cout << title;

    if (length % 2 != 0) length = length / 2 + 1;
    else length = length / 2;
    for (int i = 0; i < length; i++)
    {
        result.append(sign);
        cout << sign;
    }

    cout << endl;
}

void coutContent(string content, string sign)
{
    int length = 92;
    string result;
    int startLength = 4;

    length -= 4;
    length -= content.size();

    for (int i = 0; i < 4; i++)
    {
        result.append(sign);
    }

    result.append(content);

    for (int i = 0; i < length; i++)
    {
        result.append(sign);
    }

    cout << result << endl;
}

//===========================================Other============================================
void clearScreen()
{
    system("cls");
}

void random8Number(int* number)
{
    int result = 0;
    for (int i = 0; i < 8; i++)
    {
        result = result * 10 + rand() % 10;
    }

    *number = result;

    // check if it is duplicated
}

int random8Number()
{
    int result = 0;
    for (int i = 0; i < 8; i++)
    {
        result = result * 10 + rand() % 10;
    }

    // check if it is duplicated

    return result; 
}

void pressAnyKey()
{
    string input;
    input = _getch();
}

void start()
{
    srand(time(nullptr));
}

//===========================================Level============================================
void ConvertLevelCodeToName(LevelCode levelCode, string* name)
{
    if (levelCode == LevelCode::Intern) *name = "Intern";
    else if (levelCode == LevelCode::Fresher) *name = "Fresher";
    else if (levelCode == LevelCode::Junior) *name = "Junior";
    else if (levelCode == LevelCode::Senior) *name = "Senior";
    else *name = "Zero";
}

string getLevelCodeStr(LevelCode levelCode)
{
    if (levelCode == LevelCode::Intern) return "Intern";
    else if (levelCode == LevelCode::Fresher) return "Fresher";
    else if (levelCode == LevelCode::Junior) return "Junior";
    else if (levelCode == LevelCode::Senior) return "Senior";
    else return "Zero"; 
}

LevelCode getLevelCode(string levelCode)
{
    if (levelCode == "Intern") return LevelCode::Intern;
    else if (levelCode == "Fresher") return LevelCode::Fresher;
    else if (levelCode == "Junior") return LevelCode::Junior;
    else if (levelCode == "Senior") return LevelCode::Senior;
    else return LevelCode::Zero;
}





//============================================================================================
//============================================File============================================
//============================================================================================






//===========================================Level============================================
void WriteLevelFile(LevelCode levelCode, float moneyPerWorkHour, int creditPointRequired)
{
    string fileName;
    if (levelCode == LevelCode::Zero)
    {
        cout << "No Zero File in LevelCode" << endl;
        return;
    }

    if (levelCode == LevelCode::Intern) fileName = "Intern.txt";
    else if (levelCode == LevelCode::Fresher) fileName = "Fresher.txt";
    else if (levelCode == LevelCode::Junior) fileName = "Junior.txt";
    else if (levelCode == LevelCode::Senior) fileName = "Senior.txt";

    ofstream file("Data/Level/" + fileName);
    file << moneyPerWorkHour << endl;
    file << creditPointRequired << endl;
    file.close();
}

EmployeeLevel* ReadLevelFile(LevelCode levelCode)
{
    string fileName;
    if (levelCode == LevelCode::Intern) fileName = "Intern.txt";
    else if (levelCode == LevelCode::Fresher) fileName = "Fresher.txt";
    else if (levelCode == LevelCode::Junior) fileName = "Junior.txt";
    else if (levelCode == LevelCode::Senior) fileName = "Senior.txt";
    else 
    {
        cout << "Invalid level code" << endl;
        return new EmployeeLevel(LevelCode::Zero, 0, 0);
    }

    float moneyPerWorkHour;
    int creditPointRequired;

    ifstream file("Data/Level/" + fileName);
    file >> moneyPerWorkHour;
    file >> creditPointRequired;
    file.close();

    return new EmployeeLevel(levelCode, moneyPerWorkHour, creditPointRequired);
}

vector<EmployeeLevel*> ReadAllLevelFile()
{
    vector<EmployeeLevel*> result;

    for (int i = 1; i < 5; i++)
    {
        result.push_back(ReadLevelFile(static_cast<LevelCode>(i)));
    }

    return result;
}

//============================================Work============================================
void WriteWorkFile(Work* work)
{
    string id = to_string(work->getId());
    string name = work->getName();
    string creditPoint = to_string(work->getCreditPoint());
    string money = to_string(work->getMoney());
    string managerId = to_string(work->getManagerId());
    string staffId = to_string(work->getStaffId());

    string filePath = "Data/Work/" + id + ".txt";

    ofstream file(filePath);

    file << id << endl;
    file << name << endl;
    file << creditPoint << endl;
    file << money << endl;
    file << managerId << endl;
    file << staffId << endl;

    file.close();
}

Work* ReadWorkFile(string id)
{
    string filePath = "Data/Work/" + id + ".txt";

    ifstream file(filePath);

    string idStr;
    string nameStr;
    string creditPointStr;
    string moneyStr;
    string managerIdStr;
    string staffIdStr;

    getline(file, idStr);
    getline(file, nameStr);
    getline(file, creditPointStr);
    getline(file, moneyStr);
    getline(file, managerIdStr);
    getline(file, staffIdStr);

    file.close();

    return new Work(stoi(creditPointStr), stof(moneyStr), stoi(managerIdStr), stoi(staffIdStr), nameStr, stoi(idStr));
}

vector<Work*> ReadAllWorkFile()
{
    vector<Work*> works;
    fs::path folderfilePath = "Data/Work/";

    if (fs::is_directory(folderfilePath) && fs::exists(folderfilePath))
    {
        for (const auto& entry : fs::directory_iterator(folderfilePath))
        {
            string id = entry.path().filename().string();
            id = id = id.erase(id.length() - 4);
            works.push_back(ReadWorkFile(id));
        }
    }

    else
    {
        cout << "The folder Work doesn't exist" << endl;
        cout << "Press any key to continue..." << endl;
        pressAnyKey();
    }

    return works;
}

//==========================================Manager===========================================
void WriteManagerFile(Manager* manager)
{
    string id = to_string(manager->getId());
    string name = manager->getName();
    string workHour = to_string(manager->getWorkHour());
    string moneyPerHour = to_string(manager->getMoneyPerHour());
    vector<Work*> unfinishedWork = manager->getWorkUFs();
    vector<Work*> workDone = manager->getWorkDones();
    vector<Work*> notAssignedWorks = manager->getNotAssignedWorks();

    string filePath = "Data/Manager/" + id + ".txt";

    ofstream file(filePath);
    file << id << endl;
    file << name << endl;
    file << workHour << endl;
    file << moneyPerHour << endl;

    // Unfinished Work
    file << "Unfinished Work" << endl;
    for (Work* work : unfinishedWork)
    {
        file << work->getId() << endl;
    }

    // Work Done
    file << "Work Done" << endl;
    for (Work* work : workDone)
    {
        file << work->getId() << endl;
    }

    // Not Assigned Work
    file << "Not Assigned Work" << endl;
    for (Work* work : notAssignedWorks)
    {
        file << work->getId() << endl;
    }

    file.close();
}

Manager* ReadManagerFile(string id)
{
    string filePath = "Data/Manager/" + id + ".txt";

    if (!fs::exists(filePath)) return nullptr;

    ifstream file(filePath);

    string idStr;
    string nameStr;
    string workHourStr;
    string moneyPerHourStr;

    vector<string> unfinishedWorkStr;
    vector<string> workDoneStr;
    vector<string> notAssignedWorkStr;

    getline(file, idStr);
    getline(file, nameStr);
    getline(file, workHourStr);
    getline(file, moneyPerHourStr);

    // Unfinished Work
    string unfinishedWorkStrTag;

    while (getline(file, unfinishedWorkStrTag))
    {
        if (unfinishedWorkStrTag == "Unfinished Work") continue;
        if (unfinishedWorkStrTag == "Work Done") break;

        unfinishedWorkStr.push_back(unfinishedWorkStrTag);
    }

    for (string str : unfinishedWorkStr)
    {
        cout << str << endl;
    }

    // Work Done
    string workDoneStrTag;

    while (getline(file, workDoneStrTag))
    {
        if (workDoneStrTag == "Work Done") continue;
        if (workDoneStrTag == "Not Assigned Work") break;

        workDoneStr.push_back(workDoneStrTag);
    }

    // Not Assigned Work
    string notAssignedWorkStrTag;

    while (getline(file, notAssignedWorkStrTag))
    {
        if (notAssignedWorkStrTag == "Not Assigned Work") continue;

        notAssignedWorkStr.push_back(notAssignedWorkStrTag);
    }

    file.close();

    vector<Work*> unfinishedWork;
    if (unfinishedWorkStr.size() != 0)
    {
        for (string str : unfinishedWorkStr)
        {
            unfinishedWork.push_back(ReadWorkFile(str));
        }
    }   

    vector<Work*> workDone;
    if (workDoneStr.size() != 0)
    {
        for (string str : workDoneStr)
        {
            workDone.push_back(ReadWorkFile(str));
        }
    }

    vector<Work*> notAssignedWork;
    if (notAssignedWorkStr.size() != 0)
    {
        for (string str : notAssignedWorkStr)
        {
            notAssignedWork.push_back(ReadWorkFile(str));
        }
    }

    return new Manager(notAssignedWork, stof(workHourStr), stof(moneyPerHourStr), workDone, unfinishedWork, nameStr, stoi(idStr));
}

vector<Manager*> ReadAllManagerFile()
{
    vector<Manager*> managers;

    fs::path folderPath = ("Data/Manager/");

    if (fs::is_directory(folderPath) && fs::exists(folderPath))
    {
        for (const auto& entry : fs::directory_iterator(folderPath))
        {
            string id = entry.path().filename().string();
            id = id.erase(id.length() - 4);
            managers.push_back(ReadManagerFile(id));
        }
    }

    else 
    {
        cout << "The folder Manager doesn't exist" << endl;
        pressAnyKey();
    }

    return managers;
}

//===========================================Staff============================================
void WriteStaffFile(Staff* staff)
{
    string id = to_string(staff->getId());
    string name = staff->getName();
    string workHour = to_string(staff->getWorkHour());
    string moneyPerHour = to_string(staff->getMoneyPerHour());

    Level* currLevel = staff->getCurrLevel();
    string currLevelCode = getLevelCodeStr(currLevel->getLevelCode());
    string creditPoint = to_string(currLevel->getCurrCreditPoint());

    vector<Work*> workDoneList = staff->getWorkDones();
    vector<Work*> unfinishedWork = staff->getWorkUFs();

    string filePath = "Data/Staff/" + id + ".txt";

    ofstream file(filePath);
    file << id << endl;
    file << name << endl;
    file << workHour << endl;
    file << moneyPerHour << endl;
    file << currLevelCode << endl;
    file << creditPoint << endl;

    // Work Done
    file << "Work Done" << endl;
    for (Work* work : workDoneList)
    {
        file << to_string(work->getId()) << endl;
    }

    // Unfinished Work
    file << "Unfinished Work" << endl;
    for (Work* work : unfinishedWork)
    {
        file << to_string(work->getId()) << endl;
    }

    file.close();
}

Staff* ReadStaffFile(string id)
{
    string filePath = "Data/Staff/" + id + ".txt";

    if (!fs::exists(filePath)) return nullptr;

    ifstream file(filePath);

    string idStr;
    string nameStr;
    string workHourStr;
    string moneyPerHourStr;
    string currLevelCodeStr;
    string creditPointStr;

    vector<string> workDoneStr;
    vector<string> unfinishedWorkStr;

    getline(file, idStr);
    getline(file, nameStr);
    getline(file, workHourStr);
    getline(file, moneyPerHourStr);
    getline(file, currLevelCodeStr);
    getline(file, creditPointStr);

    // Work Done
    string workDoneStrTag;

    while (getline(file, workDoneStrTag))
    {
        if (workDoneStrTag == "Work Done") continue;
        if (workDoneStrTag == "Unfinished Work") break;

        workDoneStr.push_back(workDoneStrTag);
    }

    // Unfinished Work
    string unfinishedWorkStrTag;

    while (getline(file, unfinishedWorkStrTag))
    {
        if (unfinishedWorkStrTag == "Unfinished Work") continue;

        unfinishedWorkStr.push_back(unfinishedWorkStrTag);
    }

    file.close();

    // Work Done
    vector<Work*> workDones;
    if (workDoneStr.size() != 0)
    {
        for (string str : workDoneStr)
        {
            int id = stoi(str);
            workDones.push_back(ReadWorkFile(to_string(id)));
        }
    }

    // Unfinished Work
    vector<Work*> workUFs;
    if (unfinishedWorkStr.size() != 0)
    {
        for (string str : unfinishedWorkStr)
        {
            int id = stoi(str);
            workUFs.push_back(ReadWorkFile(to_string(id)));
        }
    }

    Level* currLevel = new Level(stoi(creditPointStr), getLevelCode(currLevelCodeStr));

    return new Staff(currLevel, stof(workHourStr), stof(moneyPerHourStr), workDones, workUFs,  nameStr, stoi(idStr));
}

vector<Staff*> ReadAllStaffFile()
{
    vector<Staff*> staffs;

    fs::path folderPath = ("Data/Staff/");
    
    if (fs::is_directory(folderPath) && fs::exists(folderPath))
    {
        for (const auto& entry : fs::directory_iterator(folderPath))
        {
            string id = entry.path().filename().string();
            id = id = id.erase(id.length() - 4);
            staffs.push_back(ReadStaffFile(id));
        }
    }

    else 
    {
        cout << "The folder Staff doesn't exist" << endl;
        cout << "Press any key to continue..." << endl;
        pressAnyKey();
    }

    Manager().setStaffs(staffs);

    return staffs;
}
