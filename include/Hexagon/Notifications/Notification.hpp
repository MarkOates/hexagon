#pragma once


#include <string>


namespace Hexagon
{
   namespace Notifications
   {
      class Notification
      {
      private:
         std::string body_text;

      protected:


      public:
         Notification(std::string body_text="");
         ~Notification();

         std::string get_body_text() const;
      };
   }
}



