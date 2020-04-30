

#include <Blast/Daemus/NetworkMessage.hpp>



namespace Blast
{
namespace Daemus
{


NetworkMessage::NetworkMessage()
   : daemus(nullptr)
{
}


NetworkMessage::~NetworkMessage()
{
}


bool NetworkMessage::process_message(std::string message)
{
bool message_captured = false;

if (message == "TO_DAEMUS: OUTPUT_PID") { daemus->output_pid(); message_captured = true; }

return message_captured;

}
} // namespace Daemus
} // namespace Blast


