#pragma once


#include <Hexagon/Notifications/Notification.hpp>
#include <string>


namespace Hexagon
{
   namespace Notifications
   {
      class NotificationFactory
      {
      private:

      protected:


      public:
         NotificationFactory();
         ~NotificationFactory();

         Hexagon::Notifications::Notification* create_basic_notification(std::string body_text="");
      };
   }
}



