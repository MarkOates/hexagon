
#include <gtest/gtest.h>

#include <Hexagon/Layout.hpp>

TEST(Hexagon_LayoutTest, can_be_created_without_blowing_up)
{
   Hexagon::Layout layout;
}

TEST(Hexagon_LayoutTest, create__will_create_the_passed_files)
{
   std::string project_root = "/Users/markoates/Repos/hexagon/";
   std::vector<StageInterface *> stages;
   std::string daemus_command = "git diff";
   std::vector<std::tuple<std::string, std::string, float, float>> files = {
      { "/Users/markoates/Repos/hexagon/quintessence/Hexagon/Logo.q.yml", "blast_quintessence", 0, 0 },
   };

   Hexagon::Layout layout(project_root, &stages, files, daemus_command);

   layout.create();

   ASSERT_EQ(false, stages.empty());
}

