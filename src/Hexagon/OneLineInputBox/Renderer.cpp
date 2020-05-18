

#include <Hexagon/OneLineInputBox/Renderer.hpp>



namespace Hexagon
{
namespace OneLineInputBox
{


Renderer::Renderer()
   : font(nullptr)
   , outline_and_text_color({0.0f,0.0f,0.0f,0.0f})
   , width(1.0f)
   , height(1.0f)
   , cell_width(1)
   , cell_height(1)
{
}


Renderer::~Renderer()
{
}


void Renderer::render_raw(int cursor_x, int cursor_y)
{
return;

}
} // namespace OneLineInputBox
} // namespace Hexagon


