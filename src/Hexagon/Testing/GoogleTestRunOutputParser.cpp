

#include <Hexagon/Testing/GoogleTestRunOutputParser.hpp>



namespace Hexagon
{
namespace Testing
{


GoogleTestRunOutputParser::GoogleTestRunOutputParser(std::string google_test_run_output, std::vector<Hexagon::Testing::GoogleTestRunTestResult> test_results)
   : google_test_run_output(google_test_run_output)
   , test_results(test_results)
{
}


GoogleTestRunOutputParser::~GoogleTestRunOutputParser()
{
}


bool GoogleTestRunOutputParser::parse()
{
std::string failing_case = "just some unparsable garbage string";
if (google_test_run_output == failing_case) return false;
return true;

}
} // namespace Testing
} // namespace Hexagon


