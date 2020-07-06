

#include <AnotherFixtureObject.hpp>





AnotherFixtureObject::AnotherFixtureObject(std::string foobar)
   : foobar(foobar)
{
}


AnotherFixtureObject::~AnotherFixtureObject()
{
}


std::string AnotherFixtureObject::get_foobar()
{
   return foobar;
}


std::vector<std::string> AnotherFixtureObject::generate_two_foobars()
{
return { get_foobar(), get_foobar() };
}



