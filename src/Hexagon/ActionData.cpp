


#include <Hexagon/ActionData.hpp>

#include <sstream>



std::string ActionData::_get_datatype_string(datatype_t type)
{
   switch(type)
   {
      case UNBOUND:
         return "unbound";
         break;
      case STRING:
         return "string";
         break;
      case CHAR:
         return "char";
         break;
      case BOOL:
         return "bool";
         break;
      case FLOAT:
         return "float";
         break;
      case DOUBLE:
         return "double";
         break;
      case INT:
         return "int";
         break;
      default:
         throw std::runtime_error("[ActionData]: Unidentified attribute type - boom!");
         break;
   };
}



ActionData::ActionData()
   : type(ActionData::UNBOUND)
{}



ActionData::ActionData(std::string string_value)
   : type(ActionData::STRING)
   , string_value(string_value)
{}



ActionData::~ActionData()
{}



std::string ActionData::get_string()
{
   if (type != STRING)
   {
      std::stringstream error_message;
      error_message << "Attempting to get a string attribute when it is defined as another type \"" << _get_datatype_string(type) << "\"." << std::endl;
      throw std::runtime_error(error_message.str());
   }
   return string_value;
}



