#pragma once


#include <string>


class ApplicationController
{
private:
   std::string regex_temp_filename;

public:
   ApplicationController(std::string regex_temp_filename="");
   ~ApplicationController();


void run_program();
};



