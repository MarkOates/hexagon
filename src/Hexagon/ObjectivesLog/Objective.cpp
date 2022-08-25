

#include <Hexagon/ObjectivesLog/Objective.hpp>



namespace Hexagon
{
namespace ObjectivesLog
{


Objective::Objective(std::string title, std::string description, bool completed)
   : title(title)
   , description(description)
   , completed(completed)
{
}


Objective::~Objective()
{
}


void Objective::set_title(std::string title)
{
   this->title = title;
}


void Objective::set_description(std::string description)
{
   this->description = description;
}


std::string Objective::get_title() const
{
   return title;
}


std::string Objective::get_description() const
{
   return description;
}


bool Objective::get_completed() const
{
   return completed;
}


void Objective::mark_as_completed()
{
   completed = true;
   return;
}
} // namespace ObjectivesLog
} // namespace Hexagon


