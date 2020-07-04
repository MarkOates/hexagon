

#include <Hexagon/Testing/GoogleTestRunTestResult.hpp>



namespace Hexagon
{
namespace Testing
{


GoogleTestRunTestResult::GoogleTestRunTestResult(std::string test_class_name, std::string test_description, std::string result, int duration_msec, std::string failure_message)
   : test_class_name(test_class_name)
   , test_description(test_description)
   , result(result)
   , duration_msec(duration_msec)
   , failure_message(failure_message)
{
}


GoogleTestRunTestResult::~GoogleTestRunTestResult()
{
}


} // namespace Testing
} // namespace Hexagon


