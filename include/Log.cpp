#include "Log.hpp"

Log::Log() : NonTool(-1, "Unknown Log", "Log", 0){}

Log::Log(int id, int quantity) : NonTool(id, "-", "Log", quantity)
{
    switch(id)
    {
        case 1 : name = "Oak Log"; break;
        case 2 : name = "Spruce Log"; break;
        case 3 : name = "Birch Log"; break;
        default : name = "Unknown Log";
    }
}

Log::Log(const Log& log) : NonTool(log){}

Log& Log::operator=(const Log& log)
{
    NonTool::operator=(log);
    return *this;
}

Log::~Log()
{
    // cout<<"Log Destroyed"<<endl;
}