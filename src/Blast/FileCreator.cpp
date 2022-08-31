

#include <Blast/FileCreator.hpp>
#include <iostream>
#include <fstream>


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

void FileCreator::create_or_overwrite()
{
   std::ofstream outfile(filename);
   outfile << initial_content;
   outfile.close();
   return;
}
} // namespace Blast


