

#include <Hexagon/CodeSelectionBoxRenderer.hpp>



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
   return true;
}

int CodeSelectionBoxRenderer::get_line_length(int line_num)
{
   return 0;
}

void CodeSelectionBoxRenderer::render()
{
   return;
}
} // namespace Hexagon


