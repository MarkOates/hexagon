#pragma once


#include <cstdint>
#include <string>


namespace Hexagon
{
   namespace ChatGPTIntegration
   {
      class Message
      {
      private:
         std::string text;
         uint32_t author_id;

      protected:


      public:
         Message(std::string text="[unset-text]", uint32_t author_id=0);
         ~Message();

         void set_text(std::string text);
         void set_author_id(uint32_t author_id);
         std::string get_text() const;
         uint32_t get_author_id() const;
      };
   }
}



