#pragma once


#include <Hexagon/CodeRange.hpp>
#include <ostream>


//namespace Hexagon (should be but CodeRange is currently at global scope until it is fixed)
//{
   //bool operator==(const CodeRange& object, const CodeRange& other_object);
   void PrintTo(const CodeRange& object, ::std::ostream* os);
//}


