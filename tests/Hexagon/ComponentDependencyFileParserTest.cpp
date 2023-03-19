
#include <gtest/gtest.h>

#include <Hexagon/ComponentDependencyFileParser.hpp>


#define TEST_FIXTURE_DEPFILE_1 "/Users/markoates/Repos/hexagon/tests/fixtures/depfile.d"
#define TEST_FIXTURE_DEPFILE_2 "/Users/markoates/Repos/hexagon/tests/fixtures/depfile2.d"



TEST(Hexagon_ComponentDependencyFileParserTest, can_be_created_without_blowing_up)
{
   Hexagon::ComponentDependencyFileParser component_dependency_file_parser;
}


TEST(Hexagon_ComponentDependencyFileParserTest,
   DISABLED__generate_dependency_filename__when_a_file_does_not_exist__raises_an_error)
{
   // TODO: not implemented
}


TEST(Hexagon_ComponentDependencyFileParserTest, generate_dependency_filename__returns_the_expected_filename__case1)
{
   std::string dependency_filename = TEST_FIXTURE_DEPFILE_1;
   Hexagon::ComponentDependencyFileParser component_dependency_file_parser(dependency_filename);
   std::set<std::string> expected_dependencies = {
      //"ActionQueueRecording.o:", // NOTE: this element is removed/ignored from the depfile
      //"src/Hexagon/ActionQueueRecording.cpp", // NOTE: this element is removed/ignored from the depfile
      "include/Hexagon/Action.hpp",
      "include/Hexagon/ActionData.hpp",
      "include/Hexagon/ActionQueueRecording.hpp",
   };
   EXPECT_EQ(expected_dependencies, component_dependency_file_parser.generate_dependencies());
}


TEST(Hexagon_ComponentDependencyFileParserTest, generate_dependency_filename__returns_the_expected_filename__case2)
{
   std::string dependency_filename = TEST_FIXTURE_DEPFILE_2;
   Hexagon::ComponentDependencyFileParser component_dependency_file_parser(dependency_filename);
   std::set<std::string> expected_dependencies = {
      "include/NcursesArt/ProjectComponentBasenameExtractor.hpp",
   };
   EXPECT_EQ(expected_dependencies, component_dependency_file_parser.generate_dependencies());
}


