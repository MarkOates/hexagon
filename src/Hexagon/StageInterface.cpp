


#include <Hexagon/StageInterface.hpp>



StageInterface::StageInterface(StageInterface::type_t type)
   : type(type)
   , render_on_hud(false)
   , place(0, 0, 0)
{}



StageInterface::~StageInterface()
{
   destroy();
}



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
      case COMPONENT_NAVIGATOR:
         return "ComponentNavigator";
         break;
      case PROJECT_COMPONENT_NAVIGATOR:
         return "ProjectComponentNavigator";
         break;
      case COMPONENT_RELATIONS_NAVIGATOR:
         return "ComponentRelationsNavigator";
         break;
      case KEYBOARD_INPUTS_MODAL:
         return "KeyboardInputsModal";
         break;
      case NEW_COMPONENT_MAKER:
         return "NewComponentMaker";
         break;
      case MISSING_FILE:
         return "MissingFile";
         break;
      case LITTLE_MENU:
         return "LittleMenu";
         break;
      case DRAWING_BOX:
         return "DrawingBox";
         break;
      case NOTIFICATION:
         return "Notification";
         break;
      case FANCY:
         return "Fancy";
         break;
      case OBJECTIVES_LOG:
         return "ObjectivesLog";
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



void StageInterface::set_render_on_hud(bool render_on_hud)
{
   this->render_on_hud = render_on_hud;
}



bool StageInterface::get_render_on_hud()
{
   return render_on_hud;
}



bool StageInterface::infer_is_modal()
{
   switch (type)
   {
   case ONE_LINE_INPUT_BOX:
   case GIT_COMMIT_MESSAGE_INPUT_BOX:
   case FILE_NAVIGATOR:
   case COMPONENT_NAVIGATOR:
   case PROJECT_COMPONENT_NAVIGATOR:
   case COMPONENT_RELATIONS_NAVIGATOR:
   case KEYBOARD_INPUTS_MODAL:
   case NEW_COMPONENT_MAKER:
   case LITTLE_MENU:
   case OBJECTIVES_LOG:
   case DRAWING_BOX:
      return true;
   default:
      return false;
   }
}



void StageInterface::destroy() {}



