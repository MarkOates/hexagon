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
         class CheckGitSyncAndUpdatePowerbar : public ::Action
         {
         private:
            std::string repo_name;
            std::string repos_directory;
            Hexagon::Powerbar::Powerbar* powerbar;

         public:
            CheckGitSyncAndUpdatePowerbar(std::string repo_name="blast", std::string repos_directory="~/Repos", Hexagon::Powerbar::Powerbar* powerbar=nullptr);
            ~CheckGitSyncAndUpdatePowerbar();

            std::string get_repo_name() const;
            std::string get_repos_directory() const;
            bool execute() override;
         };
      }
   }
}



