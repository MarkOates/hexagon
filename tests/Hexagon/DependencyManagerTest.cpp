
#include <gtest/gtest.h>

#include <Hexagon/DependencyManager.hpp>


#define TEST_FIXTURE_PROJECT_FOLDER "/Users/markoates/Repos/hexagon/tests/fixtures/"
#define TEST_FIXTURE_REPLACEMENT_DEP_FILE "/Users/markoates/Repos/hexagon/tests/fixtures/replacement_dep.d"


TEST(Hexagon_DependencyManagerTest, can_be_created_without_blowing_up)
{
   Hexagon::DependencyManager dependency_manager;
}


TEST(Hexagon_DependencyManagerTest, load_from_source_tree__will_load_the_dependencies)
{
   Hexagon::DependencyManager dependency_manager(TEST_FIXTURE_PROJECT_FOLDER);
   dependency_manager.load_from_source_tree();

   std::map<std::string, std::set<std::string>> expected_dependencies = {
      { "Blast/ShellCommandExecutor", {
         // empty
      }},
      { "Hexagon/CppCompiler/CompileRunner", {
         "Blast/ShellCommandExecutor",
      }},
      { "NcursesArt/GithubRepoStatusFetcher", {
         "Blast/ShellCommandExecutorWithCallback",
         "Blast/String/Trimmer",
         "Blast/StringSplitter",
      }},
      { "NcursesArt/ProjectComponentBasenameExtractor", {
         // empty
      }},
      { "NcursesArt/ProjectFilenameGenerator", {
         // empty
      }},
   };

   EXPECT_EQ(expected_dependencies, dependency_manager.get_dependencies());
}


/*
TEST(Hexagon_DependencyManagerTest, load_from_source_tree__will_load_the_dependents)
{
   Hexagon::DependencyManager dependency_manager(TEST_FIXTURE_PROJECT_FOLDER);
   dependency_manager.load_from_source_tree();

   std::map<std::string, std::set<std::string>> expected_dependents = {
      { "Blast/ShellCommandExecutor", {
         "Hexagon/CppCompiler/CompileRunner"
      }},
      { "Blast/ShellCommandExecutorWithCallback", {
         "NcursesArt/GithubRepoStatusFetcher"
      }},
      { "Blast/String/Trimmer", {
         "NcursesArt/GithubRepoStatusFetcher"
      }},
      { "Blast/StringSplitter", {
         "NcursesArt/GithubRepoStatusFetcher"
      }},
   };

   EXPECT_EQ(expected_dependents, dependency_manager.get_dependents());
}


TEST(Hexagon_DependencyManagerTest, reload_dependency_file__will_load_the_dependents)
{
   Hexagon::DependencyManager dependency_manager(TEST_FIXTURE_PROJECT_FOLDER);
   dependency_manager.load_from_source_tree();
   dependency_manager.reload_dependency_file("NcursesArt/GithubRepoStatusFetcher", TEST_FIXTURE_REPLACEMENT_DEP_FILE);

   std::map<std::string, std::set<std::string>> expected_dependents_after_reload = {
      { "Blast/ShellCommandExecutor", {
         "Hexagon/CppCompiler/CompileRunner"
      }},
      { "Blast/ShellCommandExecutorWithCallback", {
         //"NcursesArt/GithubRepoStatusFetcher"
      }},
      { "Blast/String/Trimmer", {
         "NcursesArt/GithubRepoStatusFetcher"
      }},
      { "Blast/StringSplitter", {
         //"NcursesArt/GithubRepoStatusFetcher"
      }},
   };

   // HERE
   EXPECT_EQ(expected_dependents_after_reload, dependency_manager.get_dependents());

   std::map<std::string, std::set<std::string>> expected_dependencies = {
      { "Blast/ShellCommandExecutor", {
         // empty
      }},
      { "Hexagon/CppCompiler/CompileRunner", {
         "Blast/ShellCommandExecutor",
      }},
      { "NcursesArt/GithubRepoStatusFetcher", {
         //"Blast/ShellCommandExecutorWithCallback",
         "Blast/String/Trimmer",
         //"Blast/StringSplitter",
      }},
      { "NcursesArt/ProjectComponentBasenameExtractor", {
         // empty
      }},
      { "NcursesArt/ProjectFilenameGenerator", {
         // empty
      }},
   };

   EXPECT_EQ(expected_dependencies, dependency_manager.get_dependencies());
}
*/

