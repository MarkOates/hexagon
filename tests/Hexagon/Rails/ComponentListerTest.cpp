
#include <gtest/gtest.h>

#include <Hexagon/Rails/ComponentLister.hpp>

TEST(Hexagon_Rails_ComponentListerTest, can_be_created_without_blowing_up)
{
   Hexagon::Rails::ComponentLister component_lister;
}

TEST(Hexagon_Rails_ComponentListerTest, model_filenames__returns_the_expected_list_of_model_filenames)
{
   Hexagon::Rails::ComponentLister component_lister;
   std::vector<std::string> expected_model_filenames = {
      "app/models/disc.rb",
      "app/models/disc_type.rb",
      "app/models/application_record.rb",
   };
   EXPECT_EQ(expected_model_filenames, component_lister.model_filenames());
}
