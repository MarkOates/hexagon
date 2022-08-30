

#include <Hexagon/BuildSystem/Builds/Base.hpp>
#include <iostream>


namespace Hexagon
{
namespace BuildSystem
{
namespace Builds
{


Base::Base(std::string type, std::vector<Hexagon::BuildSystem::BuildStages::Base*> build_stages)
   : type(type)
   , build_stages(build_stages)
   , started_at(0)
   , ended_at(0)
   , status(STATUS_NOT_STARTED)
{
}


Base::~Base()
{
}


void Base::set_build_stages(std::vector<Hexagon::BuildSystem::BuildStages::Base*> build_stages)
{
   this->build_stages = build_stages;
}


void Base::set_started_at(float started_at)
{
   this->started_at = started_at;
}


void Base::set_ended_at(float ended_at)
{
   this->ended_at = ended_at;
}


void Base::set_status(std::string status)
{
   this->status = status;
}


std::string Base::get_type() const
{
   return type;
}


std::vector<Hexagon::BuildSystem::BuildStages::Base*> Base::get_build_stages() const
{
   return build_stages;
}


float Base::get_started_at() const
{
   return started_at;
}


float Base::get_ended_at() const
{
   return ended_at;
}


std::string Base::get_status() const
{
   return status;
}


bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}

void Base::run()
{
   // set all the statuses to STATUS_NOT_STARTED
   for (auto &build_stage : build_stages)
   {
      build_stage->set_status(Hexagon::BuildSystem::BuildStages::Base::STATUS_NOT_STARTED);
   }

   // run the stages one-by-one, or halt when one fails
   for (auto &build_stage : build_stages)
   {
      build_stage->set_status(Hexagon::BuildSystem::BuildStages::Base::STATUS_RUNNING);
      try
      {
         build_stage->execute();
         build_stage->set_status(Hexagon::BuildSystem::BuildStages::Base::STATUS_FINISHED);
      }
      catch (const std::exception& e)
      {
         std::cout << "There was an error during the execution of build stage." << std::endl;
         build_stage->set_status(Hexagon::BuildSystem::BuildStages::Base::STATUS_ERROR);

         status = STATUS_ERROR;
         return;
      }
   }

   // set the status to STATUS_FINISHED when all the stages are completed (without error)
   status = STATUS_FINISHED;
   return;
}
} // namespace Builds
} // namespace BuildSystem
} // namespace Hexagon

