

#include <Hexagon/RailsMinitestTestResultToCodeMessagePointConverter.hpp>
#include <Hexagon/CodeMessagePoint.hpp>


namespace Hexagon
{


RailsMinitestTestResultToCodeMessagePointConverter::RailsMinitestTestResultToCodeMessagePointConverter(RailsMinitestTestResult rails_minitest_test_result)
   : rails_minitest_test_result(rails_minitest_test_result)
{
}


RailsMinitestTestResultToCodeMessagePointConverter::~RailsMinitestTestResultToCodeMessagePointConverter()
{
}


std::string RailsMinitestTestResultToCodeMessagePointConverter::run()
{
   return "Hello World!";
}

CodeMessagePoint RailsMinitestTestResultToCodeMessagePointConverter::convert()
{
   CodeMessagePoint::type_t code_message_point_type = CodeMessagePoint::NONE;
   if (rails_minitest_test_result.test_state == RailsMinitestTestResult::ERROR) code_message_point_type = CodeMessagePoint::ERROR;
   else if (rails_minitest_test_result.test_state == RailsMinitestTestResult::FAILURE) code_message_point_type = CodeMessagePoint::TEST_FAILURE;
   return CodeMessagePoint(0, rails_minitest_test_result.error_line_number, 0, 0, rails_minitest_test_result.test_result_output, code_message_point_type);
}
} // namespace Hexagon


