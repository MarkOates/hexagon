#include <string>
#include <iostream>

// build with:
// g++ -std=c++17 tests/fixtures/source_files/a_program.cpp

int main(int argc, char **argv)
{
   std::string output_string = "This is some text output by the fixture program.";
   std::cout << output_string << std::endl;
   return 0;
}
