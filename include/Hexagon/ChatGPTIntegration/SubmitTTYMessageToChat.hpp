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
         std::string conversation_id;
         std::string last_parent_id;
         std::string shell_command_output;
         bool output_command_to_cout;

      protected:


      public:
         SubmitTTYMessageToChat(std::string tty_location="[unset-tty_location]", std::string message="[unset-message]", std::string conversation_id="[unset-conversation_id]", std::string last_parent_id="[unset-last_parent_id]");
         ~SubmitTTYMessageToChat();

         void set_tty_location(std::string tty_location);
         void set_message(std::string message);
         void set_conversation_id(std::string conversation_id);
         void set_last_parent_id(std::string last_parent_id);
         void set_shell_command_output(std::string shell_command_output);
         void set_output_command_to_cout(bool output_command_to_cout);
         std::string get_tty_location() const;
         std::string get_message() const;
         std::string get_conversation_id() const;
         std::string get_last_parent_id() const;
         std::string get_shell_command_output() const;
         bool get_output_command_to_cout() const;
         std::string submit();
      };
   }
}



