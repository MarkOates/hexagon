


#include <Hexagon/StageInterface.hpp>



StageInterface::StageInterface(StageInterface::type_t type)
   : type(type)
   , place(0, 0, 0)
{}



StageInterface::~StageInterface()
{}



StageInterface::type_t StageInterface::get_type()
{
   return type;
}


std::string StageInterface::get_type_name()
{
   switch(type)
   {
      case NONE:
         return "none";
         break;
      case ADVANCED_CODE_EDITOR:
         return "AdvancedCodeEditor";
         break;
      case CODE_EDITOR:
         return "CodeEditor";
         break;
      case ONE_LINE_INPUT_BOX:
         return "OneLineInputBox";
         break;
      case GIT_COMMIT_MESSAGE_INPUT_BOX:
         return "GitCommitMessageInputBox";
         break;
      case FILE_NAVIGATOR:
         return "FileNavigator";
         break;
      case OLD_COMPONENT_NAVIGATOR:
         return "OldComponentNavigator";
         break;
      case COMPONENT_NAVIGATOR:
         return "ComponentNavigator";
         break;
      case KEYBOARD_INPUTS_MODAL:
         return "KeyboardInputsModal";
         break;
      case RERUN_OUTPUT_WATCHER:
         return "RerunOutputWatcher";
         break;
      case MISSING_FILE:
         return "MissingFile";
         break;
      default:
      {
         throw std::runtime_error("StageInterface::get_type_name() unrecognized type");
      }
   }
}



placement3d &StageInterface::get_place()
{
   return place;
}



void StageInterface::set_place(placement3d place)
{
   this->place = place;
}



bool StageInterface::infer_is_modal()
{
   switch (type)
   {
   case ONE_LINE_INPUT_BOX:
   case GIT_COMMIT_MESSAGE_INPUT_BOX:
   case FILE_NAVIGATOR:
   case OLD_COMPONENT_NAVIGATOR:
   case COMPONENT_NAVIGATOR:
   case KEYBOARD_INPUTS_MODAL:
      return true;
   default:
      return false;
   }
}



