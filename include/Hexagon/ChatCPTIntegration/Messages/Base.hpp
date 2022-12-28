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
            int conversation_id;
            int parent_id;
            int author_id;

         protected:


         public:
            Base(std::string type=Hexagon::ChatCPTIntegration::Messages::Base::TYPE, int conversation_id=0, int parent_id=0, int author_id=0);
            ~Base();

            void set_conversation_id(int conversation_id);
            void set_parent_id(int parent_id);
            void set_author_id(int author_id);
            std::string get_type() const;
            int get_conversation_id() const;
            int get_parent_id() const;
            int get_author_id() const;
            bool is_type(std::string possible_type="");
         };
      }
   }
}



