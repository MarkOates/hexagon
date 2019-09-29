

#include <Hexagon/PasteboardData.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <iostream>
#include <sstream>


namespace Hexagon
{


PasteboardData::PasteboardData()
{
}


PasteboardData::~PasteboardData()
{
}


bool PasteboardData::store(std::string content)
{
std::stringstream command;
command << "printf \"" << content << "\" | pbcopy" << std::endl;
Blast::ShellCommandExecutorWithCallback executor(command.str());
executor.execute();
return true;

}

std::string PasteboardData::retrieve()
{
return {};

}
} // namespace Hexagon


