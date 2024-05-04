#pragma once
#include <iostream>
#include <string>

#include "../Other/Utils.cpp"
using namespace std;

class Stat
{
    private:
    string name;
    int id;

    public:
    //========================================Constructor=========================================
    Stat();
    Stat(string name, int id);

    //============================================Get=============================================
    string getName() const;
    int getId() const;

    //============================================Set=============================================
    void setName(string name);
    void setId(int id);
};