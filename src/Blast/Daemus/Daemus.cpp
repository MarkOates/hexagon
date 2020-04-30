

#include <Blast/Daemus/Daemus.hpp>
#include <iostream>
#include <iostream>
#include <unistd.h>


namespace Blast
{
namespace Daemus
{


Daemus::Daemus()
{
}


Daemus::~Daemus()
{
}


void Daemus::output_pid()
{
std::cout << "pid: " << getpid() << std::endl;
return;

}
} // namespace Daemus
} // namespace Blast


