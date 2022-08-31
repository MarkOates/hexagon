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

      protected:


      public:
         Objective(std::string title="Unnamed Objective", std::string description="This objective has not yet been defined.", bool completed=false);
         ~Objective();

         void set_title(std::string title);
         void set_description(std::string description);
         std::string get_title() const;
         std::string get_description() const;
         bool get_completed() const;
         void mark_as_completed();
      };
   }
}



