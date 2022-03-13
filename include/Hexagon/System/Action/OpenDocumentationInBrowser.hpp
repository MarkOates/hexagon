#pragma once


#include <Hexagon/Action.hpp>
#include <string>


namespace Hexagon
{
   namespace System
   {
      namespace Action
      {
         class OpenDocumentationInBrowser : public ::Action
         {
         private:
            static std::string DOCUMENTATION_FILENAME;
            std::string project_path;

         public:
            OpenDocumentationInBrowser(std::string project_path="/Users/markoates/Repos/hexagon");
            virtual ~OpenDocumentationInBrowser();

            virtual bool execute();
            std::string build_shell_command_to_open_browser();
         };
      }
   }
}



