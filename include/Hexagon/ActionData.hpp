#pragma once



#include <string>



class ActionData
{
private:
   enum datatype_t
   {
      UNBOUND,
      STRING,
      CHAR,
      BOOL,
      FLOAT,
      DOUBLE,
      INT,
   };

   datatype_t type;
   const std::string ATTRIBUTE_KEY = "value";
   std::string string_value;

   static std::string _get_datatype_string(datatype_t type);

public:
   ActionData();
   ActionData(std::string string_value);
   ~ActionData();

   std::string get_string();
};



