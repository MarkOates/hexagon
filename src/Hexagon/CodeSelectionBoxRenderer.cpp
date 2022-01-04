

#include <Hexagon/CodeSelectionBoxRenderer.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{


CodeSelectionBoxRenderer::CodeSelectionBoxRenderer(std::vector<std::string>* lines, CodeRange* code_range, int first_line_number, int cell_width, int cell_height)
   : lines(lines)
   , code_range(code_range)
   , first_line_number(first_line_number)
   , cell_width(cell_width)
   , cell_height(cell_height)
{
}


CodeSelectionBoxRenderer::~CodeSelectionBoxRenderer()
{
}


bool CodeSelectionBoxRenderer::verify_line_in_range(int line_num)
{
   if (line_num >= lines->size()) return false;
   if (line_num < 0) return false;
   return true;
}

int CodeSelectionBoxRenderer::get_line_length(int line_num)
{
   if (!(lines))
      {
         std::stringstream error_message;
         error_message << "CodeSelectionBoxRenderer" << "::" << "get_line_length" << ": error: " << "guard \"lines\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!verify_line_in_range(line_num)) return 0;
   return (*lines)[line_num].length();
   return 0;
}

void CodeSelectionBoxRenderer::render()
{
   return;
}
} // namespace Hexagon


