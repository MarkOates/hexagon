
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

