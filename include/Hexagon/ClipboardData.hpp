#pragma once



#include <string>
#include <vector>



class ClipboardData
{
public:
   static bool store(std::vector<std::string> &lines);
   static std::vector<std::string> retrieve();
};



