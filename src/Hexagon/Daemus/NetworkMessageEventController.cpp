

#include <Hexagon/Daemus/NetworkMessageEventController.hpp>



namespace Hexagon
{
namespace Daemus
{


NetworkMessageEventController::NetworkMessageEventController()
   : daemus(nullptr)
{
}


NetworkMessageEventController::~NetworkMessageEventController()
{
}


bool NetworkMessageEventController::process_message(std::string message)
{
   bool message_captured = false;
   if (message == "TO_DAEMUS: OUTPUT_PID") { daemus->output_pid(); message_captured = true; }
   return message_captured;
}
} // namespace Daemus
} // namespace Hexagon


