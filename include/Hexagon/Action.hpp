#pragma once



#include <Hexagon/ActionData.hpp>
#include <string>



class Action
{
private:
   std::string name;
   ActionData data1;

public:
   Action(std::string name, ActionData data1);
   ~Action();

   std::string get_name();
   ActionData get_data1();
};



