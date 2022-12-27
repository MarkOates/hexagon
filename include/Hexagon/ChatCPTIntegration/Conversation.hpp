#pragma once


#include <Hexagon/ChatCPTIntegration/Messages/Base.hpp>
#include <cstdint>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace ChatCPTIntegration
   {
      class Conversation
      {
      private:
         std::vector<Hexagon::ChatCPTIntegration::Messages::Base*> messages;

      protected:


      public:
         Conversation();
         ~Conversation();

         std::vector<Hexagon::ChatCPTIntegration::Messages::Base*> get_messages() const;
         void append_text_message(std::string body="[unset-append_text_message]");
         void clear();
         std::vector<Hexagon::ChatCPTIntegration::Messages::Base*> get_last_n_messages(uint32_t count=3);
         void load_from_log_text_file(std::string log_text_filename="[unset-log_text_filename]");
      };
   }
}



