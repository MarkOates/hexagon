
#include <gtest/gtest.h>

#include <Hexagon/CodeEditor/Stage.hpp>

std::string TEST_FIXTURE_FILE_ROOT = "/Users/markoates/Repos/hexagon/tests/fixtures/";

TEST(Hexagon_CodeEditor_StageTest, can_be_created_without_blowing_up)
{
   std::string filename = "file_that_contains_several_lines.txt";
   CodeEditor::Stage stage(filename);
}
