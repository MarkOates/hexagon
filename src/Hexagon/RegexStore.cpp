

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
return "[a-zA-Z_][0-9A-Za-z_]{0,63}";
}
} // namespace Hexagon


