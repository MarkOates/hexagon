#pragma once


#include <Hexagon/Action.hpp>
#include <string>


namespace Hexagon
{
   namespace System
   {
      namespace Action
      {
         class OpenFolderInOS : public ::Action
         {
         private:
            std::string folder;
            std::string project_path;

         protected:


         public:
            OpenFolderInOS(std::string folder="documentation/", std::string project_path="/Users/markoates/Repos/hexagon");
            virtual ~OpenFolderInOS();

            virtual bool execute();
            std::string build_shell_command_to_open_folder_in_os();
         };
      }
   }
}



