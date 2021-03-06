
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

TEST(Hexagon_Rails_ComponentListerTest, spec_filenames__returns_the_expected_list_of_filenames)
{
   Hexagon::Rails::ComponentLister component_lister(RAILS_FIXTURE_PROJECT_ROOT_DIRECTORY);
   std::vector<std::string> expected_spec_filenames = {
      "spec/models/truck_spec.rb",
      "spec/models/driver_spec.rb",
      "spec/controllers/trucks_controller_spec.rb",
   };
   EXPECT_EQ(expected_spec_filenames, component_lister.spec_filenames());
}

TEST(Hexagon_Rails_ComponentListerTest, spec_factory_filenames__returns_the_expected_list_of_filenames)
{
   Hexagon::Rails::ComponentLister component_lister(RAILS_FIXTURE_PROJECT_ROOT_DIRECTORY);
   std::vector<std::string> expected_spec_factory_filenames = {
      "spec/factories/truck_factory.rb",
      "spec/factories/driver_factory.rb",
   };
   EXPECT_EQ(expected_spec_factory_filenames, component_lister.spec_factory_filenames());
}

TEST(Hexagon_Rails_ComponentListerTest, controller_filenames__returns_the_expected_list_of_filenames)
{
   Hexagon::Rails::ComponentLister component_lister(RAILS_FIXTURE_PROJECT_ROOT_DIRECTORY);
   std::vector<std::string> expected_controller_filenames = {
      "app/controllers/trucks_controller.rb",
      "app/controllers/application_controller.rb",
   };
   EXPECT_EQ(expected_controller_filenames, component_lister.controller_filenames());
}

