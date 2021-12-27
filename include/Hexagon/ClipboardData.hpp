#pragma once



#include <string>
#include <vector>



class ClipboardData
{
public:
   static bool clear();
   static bool store(std::string lines);
   static bool store(std::vector<std::string> &lines);
   static std::vector<std::string> retrieve();
};



