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

         public:
            OpenDocumentationInBrowser();
            virtual ~OpenDocumentationInBrowser();

            virtual bool execute();
            std::string build_shell_command_to_open_browser();
         };
      }
   }
}



