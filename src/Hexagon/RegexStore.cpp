

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
return "[a-z_][0-9a-z_]{0,31}";
}
} // namespace Hexagon


