
#include <gtest/gtest.h>

#include <Hexagon/System/Action/CreateRailsResourceLayout.hpp>

#include <Hexagon/CodeEditor/CodeEditor.hpp>



TEST(Hexagon_System_Action_CreateRailsResourceLayoutTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Action::CreateRailsResourceLayout create_rails_resource_layout;
}



TEST(Hexagon_System_Action_CreateRailsResourceLayoutTest, execute__returns_successful)
{
   Hexagon::System::Action::CreateRailsResourceLayout create_rails_resource_layout;

   EXPECT_TRUE(create_rails_resource_layout.execute());
}



TEST(Hexagon_System_Action_CreateRailsResourceLayoutTest, execute___expected_number_of_stages_are_created)
{
   std::vector<StageInterface *> stages;
   Hexagon::System::Action::CreateRailsResourceLayout create_rails_resource_layout(stages);

   EXPECT_EQ(0, stages.size());

   EXPECT_TRUE(create_rails_resource_layout.execute());

   EXPECT_EQ(6, stages.size());
}



TEST(Hexagon_System_Action_CreateRailsResourceLayoutTest, execute___created_stages_have_the_expected_placement)
{
   std::vector<StageInterface *> stages;
   Hexagon::System::Action::CreateRailsResourceLayout create_rails_resource_layout(stages);

   EXPECT_TRUE(create_rails_resource_layout.execute());

   placement3d expected_place(0, 0, 0);
   expected_place.size = vec3d(1215, 1350, 0);
   expected_place.align = vec3d(0.5, 0.5, 0.0);
   expected_place.rotation = vec3d(0.0, 0.0, 0.0);

   placement3d actual_place = stages[0]->get_place();

   EXPECT_EQ(expected_place.size, actual_place.size);
   EXPECT_EQ(expected_place.position, actual_place.position);
   EXPECT_EQ(expected_place.align, actual_place.align);
   EXPECT_EQ(expected_place.rotation, actual_place.rotation);
   EXPECT_EQ(expected_place.scale, actual_place.scale);
}



TEST(Hexagon_System_Action_CreateRailsResourceLayoutTest, execute___created_stages_have_the_expected_filenames)
{
   std::vector<StageInterface *> stages;
   std::vector<std::string> expected_filenames = {
      "app/models/truck.rb",
      "test/models/truck_test.rb",
      "config/routes.rb",
      "app/controllers/trucks_controller.rb",
      "test/controllers/trucks_controller_test.rb",
      "app/views/trucks/index.html.erb",
   };
   Hexagon::System::Action::CreateRailsResourceLayout create_rails_resource_layout(stages);

   EXPECT_TRUE(create_rails_resource_layout.execute());

   std::vector<std::string> actual_filenames;

   for (auto &stage : stages)
   {
      CodeEditor::CodeEditor *code_editor = static_cast<CodeEditor::CodeEditor *>(stage);
      actual_filenames.push_back(code_editor->get_filename());
   }

   EXPECT_EQ(expected_filenames, actual_filenames);
}


