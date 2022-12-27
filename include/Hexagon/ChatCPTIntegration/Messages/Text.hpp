#pragma once


#include <Hexagon/ChatCPTIntegration/Messages/Base.hpp>
#include <string>


namespace Hexagon
{
   namespace ChatCPTIntegration
   {
      namespace Messages
      {
         class Text : public Hexagon::ChatCPTIntegration::Messages::Base
         {
         public:
            static constexpr char* TYPE = (char*)"Messages/Text";

         private:
            std::string body;

         protected:


         public:
            Text(std::string body="[unset-body]");
            ~Text();

            void set_body(std::string body);
            std::string get_body() const;
         };
      }
   }
}



