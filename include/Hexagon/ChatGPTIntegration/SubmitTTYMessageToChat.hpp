#pragma once


#include <string>


namespace Hexagon
{
   namespace ChatGPTIntegration
   {
      class SubmitTTYMessageToChat
      {
      private:
         std::string tty_location;
         std::string message;
         std::string shell_command_output;
         bool output_command_to_cout;

      protected:


      public:
         SubmitTTYMessageToChat();
         ~SubmitTTYMessageToChat();

         void set_shell_command_output(std::string shell_command_output);
         void set_output_command_to_cout(bool output_command_to_cout);
         std::string get_shell_command_output() const;
         bool get_output_command_to_cout() const;
         std::string submit();
      };
   }
}



