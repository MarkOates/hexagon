
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

TEST(Hexagon_BlastComponentLayoutGeneratorTest,
   generate__creates_a_two_split_layout_for_components_that_have_a_quintessence)
{
   Hexagon::BlastComponentLayoutGenerator blast_project_layouts_generator(
      FIXTURE_PROJECT_DIRECTORY,
      "FixtureObjectThing"
   );

   Hexagon::Layout expected_layout = {
      "FixtureObjectThing",
      {
         {
            "/Users/markoates/Repos/hexagon/tests/fixtures/FixtureProject/quintessence/FixtureObjectThing.q.yml",
            "blast_quintessence",
            {},
         },
         {
            "/Users/markoates/Repos/hexagon/tests/fixtures/FixtureProject/tests/FixtureObjectThingTest.cpp",
            "blast_test",
            {},
         },
      },
   };
   Hexagon::Layout actual_layout = blast_project_layouts_generator.generate();
   std::vector<std::tuple<std::string, std::string, placement3d>> expected_layout_files, actual_layout_files;

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

   SUCCEED();
}

TEST(Hexagon_BlastComponentLayoutGeneratorTest,
   generate__creates_a_three_split_layout_for_components_that_only_have_a_header_and_source)
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

   SUCCEED();
}

