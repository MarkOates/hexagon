
#include <gtest/gtest.h>

#include <Hexagon/MissingFile/Stage.hpp>

TEST(Hexagon_MissingFile_StageTest, can_be_created_without_blowing_up)
{
   Hexagon::MissingFile::Stage stage;
}

TEST(Hexagon_MissingFile_StageTest, run__returns_the_expected_response)
{
   Hexagon::MissingFile::Stage stage;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, stage.run());
}
