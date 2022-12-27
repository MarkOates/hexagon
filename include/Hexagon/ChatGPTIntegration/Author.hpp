#pragma once


#include <cstdint>
#include <string>


namespace Hexagon
{
   namespace ChatGPTIntegration
   {
      class Author
      {
      private:
         uint32_t id;
         std::string identifier;
         std::string name;
         std::string avatar_bitmap_identifier;

      protected:


      public:
         Author(uint32_t id=0, std::string identifier="[unset-identifier]", std::string name="[unset-name]", std::string avatar_bitmap_identifier="[unset-avatar_bitmap_identifier]");
         ~Author();

         void set_id(uint32_t id);
         void set_identifier(std::string identifier);
         void set_name(std::string name);
         void set_avatar_bitmap_identifier(std::string avatar_bitmap_identifier);
         uint32_t get_id() const;
         std::string get_identifier() const;
         std::string get_name() const;
         std::string get_avatar_bitmap_identifier() const;
      };
   }
}



