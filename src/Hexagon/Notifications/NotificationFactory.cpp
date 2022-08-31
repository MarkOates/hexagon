

#include <Hexagon/Notifications/NotificationFactory.hpp>




namespace Hexagon
{
namespace Notifications
{


NotificationFactory::NotificationFactory()
{
}


NotificationFactory::~NotificationFactory()
{
}


Hexagon::Notifications::Notification* NotificationFactory::create_basic_notification(std::string body_text)
{
   Hexagon::Notifications::Notification *notification =
      new Hexagon::Notifications::Notification(
         body_text
      );
   return notification;
}


} // namespace Notifications
} // namespace Hexagon


