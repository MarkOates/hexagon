

#include <Hexagon/Elements/FilePixelPreviewCreator.hpp>



namespace Hexagon
{
namespace Elements
{


FilePixelPreviewCreator::FilePixelPreviewCreator(std::string filename)
   : filename(filename)
{
}


FilePixelPreviewCreator::~FilePixelPreviewCreator()
{
}


std::string FilePixelPreviewCreator::run()
{
return "Hello World!";
}
} // namespace Elements
} // namespace Hexagon


