
#include <allegro5/allegro.h> // for compatibility with union/Makefile

#include <string>

class Foo
{
public:
   static std::string MY_VALUE;
   static std::string get_my_value() 
   {
      return Foo::MY_VALUE;
   }
};

std::string Foo::MY_VALUE = "initial-value";


#define MY_VALUE Foo::get_my_value()


#include <iostream>

int main(int argc, char **argv)
{
   Foo::MY_VALUE = "modified-value";
   std::cout << "Foo::MY_VALUE: " << Foo::MY_VALUE << std::endl;
   std::cout << "Foo::get_my_value(): " << Foo::get_my_value() << std::endl;
   return 0;
}

