
#include <gtest/gtest.h>

#include <Hexagon/Rails/ComponentLister.hpp>

std::string RAILS_FIXTURE_PROJECT_ROOT_DIRECTORY = "/Users/markoates/Repos/hexagon/tests/fixtures/RailsProject";

TEST(Hexagon_Rails_ComponentListerTest, can_be_created_without_blowing_up)
{
   Hexagon::Rails::ComponentLister component_lister;
}

TEST(Hexagon_Rails_ComponentListerTest, model_filenames__returns_the_expected_list_of_filenames)
{
   Hexagon::Rails::ComponentLister component_lister(RAILS_FIXTURE_PROJECT_ROOT_DIRECTORY);
   std::vector<std::string> expected_model_filenames = {
      "app/models/driver.rb",
      "app/models/truck.rb",
      "app/models/application_record.rb",
   };
   EXPECT_EQ(expected_model_filenames, component_lister.model_filenames());
}

TEST(Hexagon_Rails_ComponentListerTest, test_filenames__returns_the_expected_list_of_filenames)
{
   Hexagon::Rails::ComponentLister component_lister(RAILS_FIXTURE_PROJECT_ROOT_DIRECTORY);
   std::vector<std::string> expected_test_filenames = {
      "test/models/truck_test.rb",
      "test/models/driver_test.rb",
      "test/controllers/trucks_controller_test.rb",
   };
   EXPECT_EQ(expected_test_filenames, component_lister.test_filenames());
}

