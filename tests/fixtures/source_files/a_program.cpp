#include <string>
#include <iostream>

// build with:
// g++ -std=c++17 tests/fixtures/source_files/a_program.cpp

int main(int argc, char **argv)
{
   std::string output_string = "This is some text to output.";
   std::cout << output_string << std::endl;
   return 0;
}
