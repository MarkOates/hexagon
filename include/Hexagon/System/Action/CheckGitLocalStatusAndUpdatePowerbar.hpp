#pragma once


#include <Hexagon/Action.hpp>
#include <Hexagon/Powerbar/Powerbar.hpp>
#include <string>


namespace Hexagon
{
   namespace System
   {
      namespace Action
      {
         class CheckGitLocalStatusAndUpdatePowerbar : public ::Action
         {
         private:
            std::string current_project_directory;
            Hexagon::Powerbar::Powerbar* powerbar;

         public:
            CheckGitLocalStatusAndUpdatePowerbar(std::string current_project_directory="/Users/markoates/Repos/hexagon/", Hexagon::Powerbar::Powerbar* powerbar=nullptr);
            ~CheckGitLocalStatusAndUpdatePowerbar();


            std::string get_current_project_directory();
         bool execute() override;
         };
      }
   }
}



