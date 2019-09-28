

#include <Hexagon/RegexStore.hpp>



namespace Hexagon
{


RegexStore::RegexStore()
{
}


RegexStore::~RegexStore()
{
}


std::string RegexStore::identifiers()
{
return "\\b[A-Za-z_][0-9A-Za-z_]+\\b";
}
} // namespace Hexagon


