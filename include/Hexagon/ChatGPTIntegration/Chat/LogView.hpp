#pragma once


#include <string>


namespace Hexagon
{
   namespace ChatGPTIntegration
   {
      namespace Chat
      {
         class LogView
         {
         private:
            std::string source_filename;

         protected:


         public:
            LogView(std::string source_filename="[unset-source_filename]");
            ~LogView();

            void set_source_filename(std::string source_filename);
            std::string get_source_filename() const;
            std::string get_log_text();
         };
      }
   }
}



