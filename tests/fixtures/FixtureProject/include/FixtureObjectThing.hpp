#pragma once


#include <string>
#include <vector>


class FixtureObjectThing
{
private:
   std::string foobar;

public:
   FixtureObjectThing(std::string foobar="boobaz");
   ~FixtureObjectThing();

   std::string get_foobar();
   std::vector<std::string> generate_two_foobars();
};



