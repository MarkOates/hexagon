

#include <FixtureObjectThing.hpp>





FixtureObjectThing::FixtureObjectThing(std::string foobar)
   : foobar(foobar)
{
}


FixtureObjectThing::~FixtureObjectThing()
{
}


std::string FixtureObjectThing::get_foobar()
{
   return foobar;
}


std::vector<std::string> FixtureObjectThing::generate_two_foobars()
{
return { get_foobar(), get_foobar() };
}


