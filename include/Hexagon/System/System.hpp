#pragma once


#include <lib/camera.h>
#include <allegro5/allegro.h>
#include <allegro_flare/placement3d.h>
#include <allegro_flare/motion.h>
#include <AllegroFlare/FontBin.hpp>
#include <string>
#include <vector>
#include <Hexagon/StageInterface.hpp>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <Hexagon/System/Config.hpp>
#include <Hexagon/Hud.hpp>


class System
{
private:
   static Motion dummy_motion;
   static Hexagon::System::Config dummy_config;

public:
   ALLEGRO_DISPLAY *display;
   Hexagon::System::Config &config;
   Motion &motion;

   bool files_changed;
   bool files_committed;
   bool in_sync_with_remote;
   std::vector<StageInterface *> stages;
   Camera camera;
   std::string last_file_navigator_selection;
   std::string last_component_navigator_selection;
   std::string global_font_resource_filename;
   int global_font_size;
   bool command_mode;
   std::string focused_component_name;
   std::vector<std::string> focused_component_name_relative_names;
   AllegroFlare::FontBin font_bin;
   Hexagon::Hud hud;
   float default_camera_stepback;

   //RerunOutputWatcher *rerun_output_watcher;

   System(ALLEGRO_DISPLAY *display=nullptr,
          Hexagon::System::Config &config = System::dummy_config,
          Motion &motion = System::dummy_motion);

   bool initialize();
   int get_display_default_width();
   int get_display_default_height();
   float get_default_camera_stepback();
   float get_default_code_editor_stage_width();
   std::string get_default_navigator_directory();
   std::string get_global_font_str();

   // util
   static std::vector<std::string> get_directory_listing_recursive(std::string directory);
   placement3d build_file_navigator_initial_place();
   placement3d build_component_navigator_initial_place();

   // retrieval
   StageInterface *get_frontmost_stage();
   CodeEditor::Stage *get_frontmost_code_editor_stage();
   std::vector<CodeEditor::Stage *> get_all_code_editor_stages();
   int get_number_of_code_editor_stages();

   // inference
   bool is_current_stage_in_edit_mode();
   bool is_current_stage_a_modal();
   bool is_current_stage_a_regex_input_box();

   // internal messages
   void acknowledge_display_resize(ALLEGRO_DISPLAY *display);
   void acknowledge_display_switch_out(ALLEGRO_DISPLAY *display);
   void acknowledge_display_switch_in(ALLEGRO_DISPLAY *display);

   // actions
   bool mark_as_files_changed();
   bool mark_as_files_committed();
   bool mark_as_in_sync_with_remote();
   bool mark_as_files_unchanged();
   bool mark_as_files_uncommitted();
   bool mark_as_not_in_sync_with_remote();
   bool write_focused_component_name_to_file();
   bool set_hud_title_to_focused_component_name();
   bool set_focused_component_name_relative_names_from_focused_component_name();
   bool set_focused_component_name_to_topmost_relative();
   bool toggle_command_mode_on();
   bool toggle_command_mode_off();
   bool rotate_stage_right();
   bool rotate_stage_left();
   bool rotate_relative_up();
   bool rotate_relative_down();
   bool center_camera_on_frontmost_stage();
   bool run_project_tests();
   bool save_current_stage();
   bool increase_font_size();
   bool decrease_font_size();
   bool refresh_regex_hilights_on_stage();
   bool set_regex_input_box_modal_to_insert_mode();
   bool spawn_regex_input_box_modal();
   bool spawn_component_navigator();
   bool spawn_red_overlay();
   bool spawn_file_navigator();
   bool spawn_rerun_output_watcher();
   void add_file_is_unsaved_notification();
   void remove_file_is_unsaved_notification();
   void clear_rerun_output_watchers();
   bool refresh_rerun_output_watchers();
   bool destroy_topmost_stage();
   bool jump_to_next_code_point_on_stage();
   bool run_make();
   bool offset_first_line_to_vertically_center_cursor_on_stage();
   bool push_component_navigator_selection();
   bool push_file_navigator_selection();
   bool attempt_to_create_stage_from_last_file_navigator_selection();
   bool spawn_file_navigator_from_last_file_navigator_folder_selection();
   bool destroy_all_code_editor_stages();
   bool create_two_or_three_split_layout_from_last_component_navigator_selection();
   bool create_three_split_from_last_component_navigator_selection();
   bool attempt_to_create_stage_from_last_component_navigator_selection();
   bool execute_magic_command();
   bool submit_current_modal();
   bool escape_current_modal();
   bool open_hexagon_config_file();
   //bool spawn_keyboard_inputs_modal();
   bool clear_last_compiled_error_messages();
   bool enable_drawing_info_overlays_on_all_code_editor_stages();
   bool disable_drawing_info_overlays_on_all_code_editor_stages();

   // motion fx
   bool fx__play_focus_animation_on_frontmost_stage();

   // events
   static const std::string OPEN_HEXAGON_CONFIG_FILE;
   static const std::string WRITE_FOCUSED_COMPONENT_NAME_TO_FILE;
   static const std::string ADD_FILE_IS_UNSAVED_NOTIFICATION;
   static const std::string ATTEMPT_TO_CREATE_STAGE_FROM_LAST_FILE_NAVIGATOR_SELECTION;
   static const std::string ATTEMPT_TO_CREATE_STAGE_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION;
   static const std::string SPAWN_FILE_NAVIGATOR_FROM_LAST_FILE_NAVIGATOR_FOLDER_SELECTION;
   static const std::string CREATE_THREE_SPLIT_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION;
   static const std::string CREATE_TWO_OR_THREE_SPLIT_LAYOUT_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION;
   static const std::string CLEAR_RERUN_OUTPUT_WATCHERS;
   static const std::string SET_FOCUSED_COMPONENT_NAME_TO_TOPMOST_RELATIVE;
   static const std::string CENTER_CAMERA_ON_FRONTMOST_STAGE;
   static const std::string CLEAR_LAST_COMPILED_ERROR_MESSAGES;
   static const std::string DESTROY_FILE_NAVIGATOR;
   static const std::string DESTROY_TOPMOST_STAGE;
   static const std::string EXECUTE_MAGIC_COMMAND;
   static const std::string DESTROY_ALL_CODE_EDITOR_STAGES;
   static const std::string ESCAPE_CURRENT_MODAL;
   static const std::string HIDE_FILE_NAVIGATOR;
   static const std::string INCREASE_FONT_SIZE;
   static const std::string DECREASE_FONT_SIZE;
   static const std::string JUMP_TO_NEXT_CODE_POINT_ON_STAGE;
   static const std::string OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE;

   static const std::string ENABLE_DRAWING_INFO_OVERLAYS_ON_ALL_CODE_EDITOR_STAGES;
   static const std::string DISABLE_DRAWING_INFO_OVERLAYS_ON_ALL_CODE_EDITOR_STAGES;
   static const std::string PUSH_FILE_NAVIGATOR_SELECTION;
   static const std::string PUSH_COMPONENT_NAVIGATOR_SELECTION;
   static const std::string REFRESH_REGEX_HILIGHTS_ON_STAGE;
   static const std::string REFRESH_RERUN_OUTPUT_WATCHERS;
   static const std::string REMOVE_FILE_IS_UNSAVED_NOTIFICATION;
   static const std::string TOGGLE_COMMAND_MODE_ON;
   static const std::string TOGGLE_COMMAND_MODE_OFF;
   static const std::string ROTATE_STAGE_LEFT;
   static const std::string ROTATE_STAGE_RIGHT;
   static const std::string ROTATE_RELATIVE_UP;
   static const std::string ROTATE_RELATIVE_DOWN;
   static const std::string RUN_MAKE;
   static const std::string RUN_PROJECT_TESTS;
   static const std::string SAVE_CURRENT_STAGE;
   static const std::string SET_REGEX_ONE_LINE_INPUT_BOX_MODAL_TO_INSERT_MODE;
   static const std::string SPAWN_COMPONENT_NAVIGATOR;
   static const std::string SPAWN_FILE_NAVIGATOR;
   //static const std::string SPAWN_KEYBOARD_INPUTS_MODAL;
   static const std::string SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL;
   static const std::string SPAWN_RERUN_OUTPUT_WATCHER;
   static const std::string SUBMIT_CURRENT_MODAL;
   static const std::string FX__PLAY_FOCUS_ANIMATION_ON_FRONTMOST_STAGE;

   void process_local_event(std::string event_name); // this function is 1:1 execute the action.  It does no calling of other actions before or after
   void process_event(ALLEGRO_EVENT &event);
   std::string get_action_description(std::string action_identifier);
};
