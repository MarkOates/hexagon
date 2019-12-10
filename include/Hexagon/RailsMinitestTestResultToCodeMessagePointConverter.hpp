#pragma once


#include <Hexagon/CodeMessagePoint.hpp>
#include <Hexagon/RailsMinitestTestResult.hpp>
#include <string>


namespace Hexagon
{
   class RailsMinitestTestResultToCodeMessagePointConverter
   {
   private:
      RailsMinitestTestResult rails_minitest_test_result;

   public:
      RailsMinitestTestResultToCodeMessagePointConverter(RailsMinitestTestResult rails_minitest_test_result={});
      ~RailsMinitestTestResultToCodeMessagePointConverter();


   std::string run();
   CodeMessagePoint convert();
   };
}



