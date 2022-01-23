#pragma once


#include <string>


namespace Hexagon
{
   namespace ObjectivesLog
   {
      class Objective
      {
      private:
         std::string title;
         std::string description;
         bool completed;

      public:
         Objective(std::string title="Unnamed Objective", std::string description="This objective has not yet been defined.", bool completed=false);
         ~Objective();

         void set_title(std::string title);
         void set_description(std::string description);
         std::string get_title();
         std::string get_description();
         bool get_completed();
         void mark_as_completed();
      };
   }
}



