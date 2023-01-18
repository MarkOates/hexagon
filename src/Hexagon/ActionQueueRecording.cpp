


#include <Hexagon/ActionQueueRecording.hpp>

#include <sstream>



ActionQueueRecording::ActionQueueRecording(std::string name)
   : name(name)
{}



ActionQueueRecording::~ActionQueueRecording()
{}



void ActionQueueRecording::clear_actions()
{
   actions.clear();
}



std::string ActionQueueRecording::get_name()
{
   return name;
}



void ActionQueueRecording::append_action(Action action)
{
   actions.push_back(action);
}



int ActionQueueRecording::infer_num_actions()
{
   return actions.size();
}



Action ActionQueueRecording::get_action_at(int index)
{
   if (index < 0 || index >= actions.size())
   {
      std::stringstream error_message;
      error_message << "\033[0;31m" << "[ActionQueueRecording]: Error attempting to access index ("
         << index << ") which is outside of range (0-" << actions.size() << ")" << "\033[0m" << std::endl;
      throw std::runtime_error(error_message.str());
   }

   return actions[index];
}



std::vector<Action> ActionQueueRecording::get_actions()
{
   return actions;
}


std::vector<Action>& ActionQueueRecording::get_actions_ref()
{
   return actions;
}



