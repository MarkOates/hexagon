
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
      Hexagon::Layout("AnotherFixtureObject"),
      Hexagon::Layout("FixtureObjectThing"),
   };
   std::vector<Hexagon::Layout> actual_layouts = blast_project_layouts_generator.generate();

   ASSERT_EQ(false, actual_layouts.empty());

   int i=0;
   for (auto &expected_layout : expected_layouts)
   {
      Hexagon::Layout &actual_layout = actual_layouts[i];
      ASSERT_EQ(expected_layout.get_concept_name(), actual_layout.get_concept_name());
      i++;
   }

   SUCCEED();
}

