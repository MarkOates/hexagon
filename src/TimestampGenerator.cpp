

#include <TimestampGenerator.hpp>
#include <ctime>
#include <iostream>
#include <sstream>




TimestampGenerator::TimestampGenerator()
{
}


TimestampGenerator::~TimestampGenerator()
{
}


std::string TimestampGenerator::get_current_time()
{
std::time_t time_now = std::time(nullptr);
std::stringstream result;
result << std::ctime(&time_now);
return result.str();

}


