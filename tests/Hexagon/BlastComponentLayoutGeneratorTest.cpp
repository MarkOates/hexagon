
#include <gtest/gtest.h>

#include <Hexagon/BlastProjectLayoutsGenerator.hpp>

const std::string FIXTURE_PROJECT_DIRECTORY = "/Users/markoates/Repos/hexagon/tests/fixtures/FixtureProject/";

TEST(Hexagon_BlastProjectLayoutsGeneratorTest, can_be_created_without_blowing_up)
{
   Hexagon::BlastProjectLayoutsGenerator blast_project_layouts_generator;
}

TEST(Hexagon_BlastProjectLayoutsGeneratorTest, generate__returns_the_expected_response)
{
   Hexagon::BlastProjectLayoutsGenerator blast_project_layouts_generator(FIXTURE_PROJECT_DIRECTORY);
   blast_project_layouts_generator.generate();
   SUCCEED();
}

TEST(Hexagon_BlastProjectLayoutsGeneratorTest, generate__creates_layouts_for_the_project_components)
{
   Hexagon::BlastProjectLayoutsGenerator blast_project_layouts_generator(FIXTURE_PROJECT_DIRECTORY);

   std::vector<Hexagon::Layout> expected_layouts = {
      Hexagon::Layout("AnotherFixtureObject", {
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
      }),
      Hexagon::Layout("FixtureObjectThing", {
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
      }),
   };
   std::vector<Hexagon::Layout> actual_layouts = blast_project_layouts_generator.generate();
   std::vector<std::tuple<std::string, std::string, placement3d>> expected_layout_files, actual_layout_files;

   ASSERT_EQ(expected_layouts.size(), actual_layouts.size());

   int i=0;
   for (auto &expected_layout : expected_layouts)
   {
      Hexagon::Layout &actual_layout = actual_layouts[i];

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

      i++;
   }

   SUCCEED();
}

