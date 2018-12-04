


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
   case FILE_NAVIGATOR:
   case KEYBOARD_INPUTS_MODAL:
      return true;
   default:
      return false;
   }
}



