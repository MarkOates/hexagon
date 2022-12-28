#pragma once


#include <string>


namespace Hexagon
{
   namespace ChatCPTIntegration
   {
      namespace Messages
      {
         class Base
         {
         public:
            static constexpr char* TYPE = (char*)"Messages/Base";

         private:
            std::string type;
            int author_id;
            std::string conversation_id;
            std::string parent_id;

         protected:


         public:
            Base(std::string type=Hexagon::ChatCPTIntegration::Messages::Base::TYPE, int author_id=0, std::string conversation_id="", std::string parent_id="");
            ~Base();

            void set_author_id(int author_id);
            void set_conversation_id(std::string conversation_id);
            void set_parent_id(std::string parent_id);
            std::string get_type() const;
            int get_author_id() const;
            std::string get_conversation_id() const;
            std::string get_parent_id() const;
            bool is_type(std::string possible_type="");
         };
      }
   }
}



