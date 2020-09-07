```cpp
bool System::create_rails_resource_layout()
{
   //Hexagon::RailsResourceFilenameGenerator generator;
   std::string application_module_name = "Disclife";
   std::string resource_name = "Disc";

   std::string base_directory = "/Users/markoates/Repos/disclife/";
   int display_default_height = 1350;
   int code_editor_width = 1215;
   std::string model_filename = base_directory + "app/models/disc.rb";
   std::string model_test_filename = base_directory + "test/models/disc_test.rb";
   std::string routes_filename = base_directory + "config/routes.rb";
   std::string controller_filename = base_directory + "app/controllers/discs_controller.rb";
   std::string controller_test_filename = base_directory + "test/controllers/discs_controller_test.rb";
   std::string view_filename = base_directory + "app/views/discs/index.html.erb";

   { // wrong layer of abstraction
      std::string hud_title = application_module_name + ": " + resource_name;
      hud.set_title_text(hud_title);
   }

   Hexagon::System::Action::CreateRailsResourceLayout rails_resource_layout(
      stages,
      display_default_height,
      code_editor_width,
      model_filename,
      model_test_filename,
      routes_filename,
      controller_filename,
      controller_test_filename,
      view_filename
   );
   return rails_resource_layout.execute();
}






         keyboard_command_mapper.set_mapping(ALLEGRO_KEY_R, false, true, false, false, {
            ::System::DESTROY_ALL_CODE_EDITOR_STAGES,
            ::System::CREATE_RAILS_RESOURCE_LAYOUT,
            ::System::ROTATE_STAGE_RIGHT,
            ::System::CENTER_CAMERA_ON_FRONTMOST_STAGE,
            ::System::FX__PLAY_FOCUS_ANIMATION_ON_FRONTMOST_STAGE });
```
