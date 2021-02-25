

#include <Blast/FileCreator.hpp>
#include <iostream>


namespace Blast
{


FileCreator::FileCreator(std::string filename, std::string initial_content)
   : filename(filename)
   , initial_content(initial_content)
{
}


FileCreator::~FileCreator()
{
}


void FileCreator::create_if_not_exists()
{
   std::cout << "ERROR: Blast::FileCreator::create_if_not_exists(): not implemented" << std::endl;
   return;
}
} // namespace Blast


