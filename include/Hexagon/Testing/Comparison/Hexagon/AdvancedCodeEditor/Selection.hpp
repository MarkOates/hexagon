#pragma once


#include <Hexagon/AdvancedCodeEditor/Selection.hpp>
#include <ostream>


namespace Hexagon::AdvancedCodeEditor
{
   bool operator==(const Selection& object, const Selection& other_object);
   bool operator!=(const Selection& object, const Selection& other_object);
   void PrintTo(const Selection& object, ::std::ostream* os);
}


