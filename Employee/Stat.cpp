#include "Stat.h"
using namespace std;

//========================================Constructor=========================================
Stat::Stat()
{
    this->name = "";
    this->id = 0;
}

Stat::Stat(string name, int id)
{
    this->name = name;
    this->id = id;
}

//============================================Get=============================================
string Stat::getName() const
{
    return this->name;
}

int Stat::getId() const
{
    return this->id;
}

//============================================Set=============================================
void Stat::setName(string name)
{
    this->name = name;
}

void Stat::setId(int id)
{
    this->id = id;
}
