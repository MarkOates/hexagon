#pragma once


#include <Hexagon/Action.hpp>
#include <Hexagon/Powerbar/Powerbar.hpp>


namespace Hexagon
{
   namespace System
   {
      namespace Action
      {
         class CheckGitLocalStatusAndUpdatePowerbar : public ::Action
         {
         private:
            Hexagon::Powerbar::Powerbar* powerbar;

         public:
            CheckGitLocalStatusAndUpdatePowerbar(Hexagon::Powerbar::Powerbar* powerbar=nullptr);
            ~CheckGitLocalStatusAndUpdatePowerbar();


         bool execute() override;
         };
      }
   }
}



