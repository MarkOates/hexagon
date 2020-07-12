```cpp
   float display_default_width = get_display_default_width();
   float display_default_height = get_display_default_height();
   std::string component_name = last_component_navigator_selection;
   float width_scale_of_halfwidth = 1.0; //0.6180339;

   ///

   std::string project_path;
   std::vector<std::string> filenames = {};

   //project_path = "/Users/markoates/dev_repos/partners/";
   //filenames = {
   //   project_path + "app/models/external_job.rb",
   //   project_path + "spec/models/external_job_spec.rb",
   //   project_path + "spec/factories/external_job_factory.rb",
   //};
   //project_path = "/Users/markoates/Repos/hexagon/";
   //filenames = {
   //   project_path + "quintessence/System/System.cpp",
   //   project_path + "include/Hexagon/System/System.hpp",
   //   project_path + "src/Hexagon/System/System.hpp",
   //};
   project_path = "/Users/markoates/Repos/hexagon/";
   filenames = {
      project_path + "src/Hexagon/System/System.cpp",
   };
   focused_component_name = "Hexagon/System/System";
   set_hud_title_to_focused_component_name();
   write_focused_component_name_to_file();
   set_focused_component_name_relative_names_from_focused_component_name();

   filenames = __list_of_files_in_file_list();

   ///


   float width = get_default_code_editor_stage_width();
   std::string filename = "";
   bool file_present = false;
   int i=0;

   destroy_all_code_editor_stages();

   ///

   for (i=0; i<filenames.size(); i++)
   {
      filename = filenames[i];
      file_present = true;
      if (!Blast::FileExistenceChecker(filename).exists()) file_present = false;
      //if (!file_contents.empty())
      {
        placement3d place(0, 0, 0);
        place.size = vec3d(width, display_default_height, 0.0);

        place.position = vec3d(width*i, 0.0, 0.0);
        place.align = vec3d(0.5, 0.5, 0.0);
        place.scale = vec3d(1.0, 1.0, 0.0);

        StageInterface *stage = nullptr;

        if (file_present)
        {
           std::vector<std::string> file_contents = {};
           ::read_file(file_contents, filename);
           stage = new Hexagon::CodeEditor::Stage(::CodeEditor::CodeEditor{filename});
           static_cast<Hexagon::CodeEditor::Stage*>(stage)->get_code_editor_ref().set_initial_content(file_contents);
        }
        else
        {
            stage = new Hexagon::MissingFile::Stage;
        }

        stage->set_place(place);
        stages.push_back(stage);
      }
   }

   //

   bool show_rerun_output_watcher = false;
   if (show_rerun_output_watcher)
   {
      float golden_ratio = 0.61803f;
      float x_pos = golden_ratio * get_display_default_width() - get_display_default_width()/2;
      placement3d place(0, 0, 0);

      place.position = vec3d(width*i, 0.0, 0.0);
      place.size = vec3d(width, display_default_height, 0.0);
      place.align = vec3d(0.5, 0.5, 0);
      place.scale = vec3d(0.9, 0.9, 0.0);

      Hexagon::RerunOutputWatcher::Stage *rerun_output_watcher = new Hexagon::RerunOutputWatcher::Stage();
      rerun_output_watcher->set_place(place);
      stages.push_back(rerun_output_watcher);
   }

   //

   process_local_event(ROTATE_STAGE_RIGHT);
   process_local_event(CENTER_CAMERA_ON_FRONTMOST_STAGE);
 ```
