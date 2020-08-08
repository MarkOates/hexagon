
#include <gtest/gtest.h>

#include <Hexagon/BlastComponentLayoutGenerator.hpp>

const std::string FIXTURE_PROJECT_DIRECTORY = "/Users/markoates/Repos/hexagon/tests/fixtures/FixtureProject/";

TEST(Hexagon_BlastComponentLayoutGeneratorTest, can_be_created_without_blowing_up)
{
   Hexagon::BlastComponentLayoutGenerator blast_project_layouts_generator;
}

TEST(Hexagon_BlastComponentLayoutGeneratorTest, generate__does_not_blow_up)
{
   Hexagon::BlastComponentLayoutGenerator blast_project_layouts_generator(FIXTURE_PROJECT_DIRECTORY);
   blast_project_layouts_generator.generate();
   SUCCEED();
}

TEST(Hexagon_BlastComponentLayoutGeneratorTest, generate__creates_layouts_for_the_project_components)
{
   Hexagon::BlastComponentLayoutGenerator blast_project_layouts_generator(
      FIXTURE_PROJECT_DIRECTORY,
      "AnotherFixtureObject"
   );

   Hexagon::Layout expected_layout = {
      "AnotherFixtureObject",
      {
         {
            "/Users/markoates/Repos/hexagon/tests/fixtures/FixtureProject/include/AnotherFixtureObject.hpp",
            "cpp_header",
            {},
         },
         {
            "/Users/markoates/Repos/hexagon/tests/fixtures/FixtureProject/src/AnotherFixtureObject.cpp",
            "cpp_source",
            {},
         },
         {
            "/Users/markoates/Repos/hexagon/tests/fixtures/FixtureProject/tests/AnotherFixtureObjectTest.cpp",
            "blast_test",
            {},
         },
      },
   };
   Hexagon::Layout actual_layout = blast_project_layouts_generator.generate();
   std::vector<std::tuple<std::string, std::string, placement3d>> expected_layout_files, actual_layout_files;

   int i=0;
   //for (auto &expected_layout : expected_layouts)
   //{
      //Hexagon::Layout &actual_layout = actual_layouts[i];

      EXPECT_EQ(expected_layout.get_concept_name(), actual_layout.get_concept_name());

      expected_layout_files = expected_layout.get_files();
      actual_layout_files = actual_layout.get_files();

      ASSERT_EQ(expected_layout_files.size(), actual_layout_files.size());

      int j=0;
      for (auto &expected_layout_file : expected_layout_files)
      {
         std::tuple<std::string, std::string, placement3d> &actual_layout_file = actual_layout_files[j];

         // has the expected filename
         EXPECT_EQ(std::get<0>(expected_layout_file), std::get<0>(actual_layout_file));

         // has the expected type
         EXPECT_EQ(std::get<1>(expected_layout_file), std::get<1>(actual_layout_file));

         j++;
      }

      //i++;
   //}

   SUCCEED();
}

