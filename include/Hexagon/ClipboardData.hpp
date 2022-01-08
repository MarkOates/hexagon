#pragma once



#include <string>
#include <vector>



class ClipboardData  // TODO: move to Hexagon:: namespace
{
public:
   static bool clear();
   static bool store(std::string lines);
   static bool store(std::vector<std::string> &lines);
   static std::vector<std::string> retrieve();
};



