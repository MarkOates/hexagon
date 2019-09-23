

#include <Hexagon/FileNavigator/Stage.hpp>



namespace Hexagon
{
namespace FileNavigator
{


Stage::Stage()
   : StageInterface({})
{
}


Stage::~Stage()
{
}


std::string Stage::run()
{
return "Hello World!";
}

void Stage::render(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font, int cell_width, int cell_height)
{
return;

}
} // namespace FileNavigator
} // namespace Hexagon


