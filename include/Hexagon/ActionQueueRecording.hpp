#pragma once



#include <Hexagon/Action.hpp>
#include <string>
#include <vector>



class ActionQueueRecording
{
private:
   std::string name;
   std::vector<Action> actions;

public:
   ActionQueueRecording(std::string name);
   ~ActionQueueRecording();

   void clear_actions();
   std::string get_name();
   void append_action(Action action);
   int infer_num_actions();
   Action get_action_at(int index);
};



