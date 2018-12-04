


#include <Hexagon/Action.hpp>



Action::Action(std::string name, ActionData data1)
   : name(name)
   , data1(data1)
{}



Action::~Action()
{}



std::string Action::get_name()
{
   return name;
}



ActionData Action::get_data1()
{
   return data1;
}



