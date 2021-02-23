

#include <Hexagon/Notifications/Notification.hpp>



namespace Hexagon
{
namespace Notifications
{


Notification::Notification(std::string body_text)
   : body_text(body_text)
{
}


Notification::~Notification()
{
}


std::string Notification::get_body_text()
{
   return body_text;
}


} // namespace Notifications
} // namespace Hexagon


