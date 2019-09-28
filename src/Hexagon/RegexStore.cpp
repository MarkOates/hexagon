

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
return "[a-z_][0-9A-Za-z_]{0,63}";
}

std::string RegexStore::class_names()
{
return "[A-Z][0-9A-Za-z_]{0,63}";
}
} // namespace Hexagon


