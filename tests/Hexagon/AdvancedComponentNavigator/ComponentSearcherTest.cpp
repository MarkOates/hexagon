
#include <gtest/gtest.h>

#include <Hexagon/AdvancedComponentNavigator/ComponentSearcher.hpp>

#include <gmock/gmock.h>
using ::testing::IsSupersetOf;


TEST(Hexagon_AdvancedComponentNavigator_ComponentSearcherTest, component_names__returns_the_expected_response)
{
   std::string project_root_directory = "/Users/markoates/Repos/blast";
   Hexagon::AdvancedComponentNavigator::ComponentSearcher list(project_root_directory);

   std::vector<std::string> expected_list = {
      "Blast/DirectoryCreator",
      "Blast/ShellCommandExecutorWithCallback",
      "Blast/CamelCaseToUnderscoreConverter",
      "Blast/Project/ComponentBasenameExtractor",
      "Blast/TemplatedFile",
      "Blast/Cpp/FunctionBody",
      "Blast/Cpp/Function",
      "Blast/DirectoryExistenceChecker",
      "Blast/StringSplitter",
   };

   std::vector<std::string> actual_list = list.component_names();

   EXPECT_THAT(actual_list, IsSupersetOf(expected_list));
}


TEST(Hexagon_AdvancedComponentNavigator_ComponentSearcherTest,
   // NOTE: this test may be disabled because the list does not match across different computers
   //DISABLED__component_names__with_search_string_returns_filtered_results)
   component_names__with_search_string_returns_filtered_results)
{
   std::string project_root_directory = "/Users/markoates/Repos/blast";
   std::string search_text = "Blast/Project";
   Hexagon::AdvancedComponentNavigator::ComponentSearcher list(project_root_directory, search_text);

   std::vector<std::string> expected_list = {
      "Blast/Project/ActionCreator",
      "Blast/Project/BasenameExtractor",
      "Blast/Project/Component",
      "Blast/Project/ComponentBasenameExtractor",
      "Blast/Project/ComponentCreator",
      "Blast/Project/ComponentDependencyLister",
      "Blast/Project/ComponentFragmentTypeEnum",
      "Blast/Project/ComponentLister",
      "Blast/Project/ComponentListerNew",
      "Blast/Project/ComponentRelativeLister",
      "Blast/Project/ProgramLister",
      "Blast/Project/ProjectSymlinkFixer",
      "Blast/Project/SourceReleaseBuilder",
      "Blast/Project/SymlinkChecker",
      "Blast/ProjectComponentBasenameExtractor",
      "Blast/ProjectComponentFileTypes",
      "Blast/ProjectComponentFilenameGenerator"
   };

   std::vector<std::string> actual_list = list.component_names();

   EXPECT_EQ(expected_list, actual_list);
}


TEST(Hexagon_AdvancedComponentNavigator_ComponentSearcherTest,
   // NOTE: this test may be disabled because the list does not match across different computers
   //DISABLED__component_names__with_search_string_returns_filtered_results)
   component_names__with_search_string_that_has_spaces_separating_search_tokens__returns_filtered_results)
{
   std::string project_root_directory = "/Users/markoates/Repos/blast";
   std::string search_text = "Blast/Project Extractor";
   Hexagon::AdvancedComponentNavigator::ComponentSearcher list(project_root_directory, search_text);

   std::vector<std::string> expected_list = {
      //"Blast/Project/ActionCreator",
      "Blast/Project/BasenameExtractor",
      //"Blast/Project/Component",
      "Blast/Project/ComponentBasenameExtractor",
      //"Blast/Project/ComponentCreator",
      //"Blast/Project/ComponentDependencyLister",
      //"Blast/Project/ComponentFragmentTypeEnum",
      //"Blast/Project/ComponentLister",
      //"Blast/Project/ComponentListerNew",
      //"Blast/Project/ComponentRelativeLister",
      //"Blast/Project/ProgramLister",
      //"Blast/Project/ProjectSymlinkFixer",
      //"Blast/Project/SourceReleaseBuilder",
      //"Blast/Project/SymlinkChecker",
      "Blast/ProjectComponentBasenameExtractor",
      //"Blast/ProjectComponentFileTypes",
      //"Blast/ProjectComponentFilenameGenerator"
   };

   std::vector<std::string> actual_list = list.component_names();

   EXPECT_EQ(expected_list, actual_list);
}


TEST(Hexagon_AdvancedComponentNavigator_ComponentSearcherTest,
   components_sorted_by_most_recent__returns_results_filtered_by_search_string)
{
   std::string project_root_directory = "/Users/markoates/Repos/blast";
   Hexagon::AdvancedComponentNavigator::ComponentSearcher searcher(project_root_directory, "ProgramLister");

   std::vector<std::string> expected = { "Blast/Project/ProgramLister" };
   std::vector<std::string> actual = searcher.convert_to_names(searcher.components_sorted_by_most_recent());

   ASSERT_EQ(expected, actual);
}


TEST(Hexagon_AdvancedComponentNavigator_ComponentSearcherTest,
   components__returns_results_filtered_by_search_string)
{
}


