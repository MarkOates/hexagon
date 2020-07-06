#pragma once


#include <string>
#include <vector>


class AnotherFixtureObject
{
private:
   std::string foobar;

public:
   AnotherFixtureObject(std::string foobar="boobaz");
   ~AnotherFixtureObject();


   std::string get_foobar();
std::vector<std::string> generate_two_foobars();
};



