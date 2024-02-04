#pragma once


#include <allegro5/allegro.h>
#include <allegro_flare/placement3d.h>
#include <allegro_flare/motion.h>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/BitmapBin.hpp>
#include <string>
#include <vector>
#include <Hexagon/Camera.hpp>
#include <Hexagon/StageInterface.hpp>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <Hexagon/AdvancedCodeEditor/Stage.hpp>
#include <Hexagon/System/Config.hpp>
#include <Hexagon/Hud.hpp>
#include <Hexagon/Packet.hpp>
#include <Hexagon/Testing/GoogleTestRunTestResult.hpp>


namespace Hexagon::System
{
class System
{
private:
   static Hexagon::System::Config dummy_hexagon_config;
   std::string last_component_navigator_selection;
   std::string current_project_directory;
   std::string last_project_navigator_selection;
   std::string last_project_folders_selection;
   std::string last_commit_message;
   std::string focused_component_name;
   std::string current_objective;
   std::string current_project_domain;
   std::string current_held_component;
   float mouse_x;
   float mouse_y;
   float baseline_camera_stepback;
   bool drawing_mouse_cursor;

   ALLEGRO_DISPLAY *display;
   Hexagon::System::Config &hexagon_config;
   Motion motion;

   std::vector<Hexagon::Testing::GoogleTestRunTestResult> test_results;

   bool option__saving_focused_filename_to_file_is_disabled;
   bool option__pushing_to_git_remote_on_commit_is_disabled;
   int save_count;
   int search_count;
   bool files_changed;
   bool files_committed;
   bool in_sync_with_remote;
   std::vector<StageInterface *> stages;
   Hexagon::Camera camera;
   std::string last_file_navigator_selection;
   std::string global_font_resource_filename;
   std::string target;
   int global_font_size;
   bool command_mode;
   std::vector<Hexagon::Packet> packets;
   AllegroFlare::BitmapBin bitmap_bin;
   AllegroFlare::FontBin font_bin;
   Hexagon::Hud hud;

   int get_display_default_width();
   int get_display_default_height();
   float get_baseline_camera_stepback();

public:

   System(ALLEGRO_DISPLAY *display=nullptr, Hexagon::System::Config &hexagon_config = System::dummy_hexagon_config);

   void initialize();
   float get_default_code_editor_stage_width();
   float get_default_code_editor_stage_height();
   std::string get_current_project_directory();
   std::string get_current_objective();
   std::string get_current_project_domain();
   std::string get_current_held_component();
   std::string get_global_font_str();
   void set_option__saving_focused_filename_to_file_is_disabled(bool option=false);
   void set_option__pushing_to_git_remote_on_commit_is_disabled(bool option=false);
   Hexagon::Camera &get_camera_ref();
   std::vector<StageInterface *> &get_stages_ref();
   Hexagon::Hud &get_hud_ref();
   Motion &get_motion_ref();

   void set_focused_component_name(std::string focused_component_name);
   void set_current_objective(std::string current_objective);
   void set_current_project_domain(std::string current_project_domain="");
   void set_current_held_component(std::string current_held_component="");
   std::string get_focused_component_name();
   void clear_focused_component_name();
   void set_last_project_navigator_selection(std::string last_project_navigator_selection);
   void set_last_project_folders_selection(std::string last_project_folders_selection);
   void set_last_component_navigator_selection(std::string last_component_navigator_selection);
   void set_current_project_directory(std::string current_project_directory);
   bool unset_focused_state_on_topmost_stage_if_not_already_unfocused(); // TODO make private
   bool set_focused_state_on_topmost_stage_if_not_already_focused(); // TODO make private

   // retrieval
   StageInterface *get_frontmost_stage();
   Hexagon::AdvancedCodeEditor::Stage *get_frontmost_advanced_code_editor_stage();
   Hexagon::CodeEditor::Stage *get_frontmost_code_editor_stage();
   std::vector<Hexagon::CodeEditor::Stage *> get_all_code_editor_stages();
   int get_number_of_code_editor_stages();

   // inference
   bool is_current_stage_in_edit_mode();
   bool is_current_stage_in_insert_mode();
   bool is_current_stage_a_modal();
   bool is_drawing_mouse_cursor();
   bool is_topmost_stage_advanced_code_editor_in_edit_mode();
   bool is_topmost_stage_an_advanced_code_editor();
   bool has_no_stages();

   // internal messages
   void acknowledge_display_resize(ALLEGRO_DISPLAY *display);
   void acknowledge_display_switch_out(ALLEGRO_DISPLAY *display);
   void acknowledge_display_switch_in(ALLEGRO_DISPLAY *display);

   // internally sent messages
   void close_topmost_multiplex_menu();

   // actions
   bool mark_as_files_changed();
   bool send_commands_from_multiplex_menu_to_editor();
   bool set_frontmost_git_commit_message_input_box_to_submitted_and_pending_destruction();
   bool set_current_project_directory_from_project_navigator_selection();
   bool open_folder_from_project_folders_selection();
   bool mark_as_files_committed();
   bool mark_as_in_sync_with_remote();
   bool mark_as_files_unchanged();
   bool mark_as_files_uncommitted();
   bool mark_as_not_in_sync_with_remote();
   bool write_focused_component_name_to_file();
   bool increment_save_count();
   bool clear_save_count();
   bool increment_search_count();
   bool increment_search_count_if_search_regex_is_nonblank();
   bool clear_search_count();
   bool set_hud_title_to_focused_component_name();
   bool set_hud_objective_to_objective();
   bool set_hud_domain_to_current_project_domain();
   bool set_hud_held_component_to_current_held_component();
   bool clear_hud_title();
   bool set_hud_save_count_to_save_count();
   bool set_hud_search_count_to_search_count();
   bool set_hud_packets_to_packets();
   bool set_hud_caps_lock_light_on();
   bool set_hud_caps_lock_light_off();
   bool toggle_command_mode_on();
   bool toggle_command_mode_off();
   bool reset_camera_to_center();
   bool rotate_stage_right_and_update_focused_state_on_changed_stages();
   bool rotate_stage_left_and_update_focused_state_on_changed_stages();
   bool pull_back_camera_to_off_axis_left();
   bool pull_back_camera_to_off_axis_right();
   bool center_camera_on_frontmost_stage();
   bool run_project_tests();
   bool save_frontmost_code_editor_stage_and_touch_if_symlink();
   bool send_message_to_daemus_to_build();
   bool increase_font_size();
   bool decrease_font_size();
   bool refresh_regex_hilights_on_frontmost_stage();
   bool refresh_regex_hilights_on_all_code_editor_stages();
   bool refresh_git_modified_line_numbers_on_all_code_editor_stages();
   bool set_regex_input_box_modal_to_insert_mode();

   // spawn modals
   bool spawn_multiplex_delete_menu();
   bool spawn_multiplex_change_menu();
   bool spawn_multiplex_goto_menu();
   bool spawn_class_brief_menu();
   bool spawn_drawing_box();
   bool spawn_regex_input_box_modal();
   bool spawn_git_commit_message_input_box_modal();
   bool spawn_component_navigator();
   bool spawn_project_navigator();
   bool spawn_project_folders_window();
   bool spawn_fancy();
   bool spawn_component_relations_navigator();
   bool spawn_red_overlay();
   bool spawn_chat_gpt_chat();

   bool parse_test_results_from_last_test_run_dump();
   bool spawn_file_navigator();
   bool add_file_is_unsaved_notification();
   bool remove_file_is_unsaved_notification();
   bool destroy_topmost_stage();
   bool jump_to_next_code_point_on_stage();
   bool jump_to_next_or_nearest_code_point_on_stage();
   bool offset_first_line_to_vertically_center_cursor_on_stage();
   bool push_component_navigator_selection();
   bool push_component_relations_navigator_selection();
   bool push_project_navigator_selection();
   bool push_project_folders_selection();
   bool push_file_navigator_selection();
   bool create_stage_from_last_file_navigator_selection();
   bool spawn_file_navigator_from_last_file_navigator_folder_selection();
   bool destroy_all_code_editor_stages();
   bool create_stages_from_layout_of_last_component_navigator_selection();
   bool create_two_or_three_split_layout_from_last_component_navigator_selection();
   bool create_layout_from_last_project_navigator_selection();
   bool set_search_regex_expression_on_all_code_editor_stages_to_regex_temp_file_contents();
   bool set_regex_temp_file_contents_to_word_under_current_advanced_code_editor_cursor();
   bool commit_all_files_with_last_git_commit_message_from_regex_temp_file_contents();
   bool append_packet_using_last_commit_message_and_clear_scores();
   bool push_to_git_remote();
   bool execute_magic_command();
   bool submit_current_modal();
   bool escape_current_modal();
   bool open_hexagon_config_file();
   bool clear_last_compiled_error_messages();
   bool enable_drawing_info_overlays_on_all_code_editor_stages();
   bool disable_drawing_info_overlays_on_all_code_editor_stages();
   bool check_git_sync_and_update_powerbar();
   bool check_git_local_status_and_update_powerbar();
   bool open_documentation_in_browser();

   // motion fx
   bool fx__play_focus_animation_on_frontmost_stage();

   // core event processing
   void process_local_event(std::string event_name);
   void process_event(ALLEGRO_EVENT *event);
};
} // Hexagon::System



class System
{
public:
   // events
   static const std::string SEND_COMMANDS_FROM_MULTIPLEX_MENU_TO_EDITOR;
   static const std::string SET_FRONTMOST_GIT_COMMIT_MESSAGE_INPUT_BOX_TO_SUBMITTED_AND_PENDING_DESTRUCTION;
   static const std::string OPEN_HEXAGON_CONFIG_FILE;
   static const std::string WRITE_FOCUSED_COMPONENT_NAME_TO_FILE;
   static const std::string ADD_FILE_IS_UNSAVED_NOTIFICATION;
   static const std::string CREATE_STAGE_FROM_LAST_FILE_NAVIGATOR_SELECTION;
   static const std::string PULL_BACK_CAMERA_TO_OFF_AXIS_LEFT;
   static const std::string PULL_BACK_CAMERA_TO_OFF_AXIS_RIGHT;
   static const std::string SPAWN_FILE_NAVIGATOR_FROM_LAST_FILE_NAVIGATOR_FOLDER_SELECTION;
   static const std::string CREATE_STAGES_FROM_LAYOUT_OF_LAST_COMPONENT_NAVIGATOR_SELECTION;
   static const std::string CREATE_LAYOUT_FROM_LAST_PROJECT_NAVIGATOR_SELECTION;
   static const std::string CREATE_TWO_OR_THREE_SPLIT_LAYOUT_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION;
   static const std::string SET_FOCUSED_COMPONENT_NAME_TO_TOPMOST_RELATIVE;
   static const std::string CLEAR_HUD_TITLE;
   static const std::string SET_HUD_CAPS_LOCK_LIGHT_ON;
   static const std::string SET_HUD_CAPS_LOCK_LIGHT_OFF;
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
   static const std::string JUMP_TO_NEXT_OR_NEAREST_CODE_POINT_ON_STAGE;
   static const std::string OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE;
   static const std::string ENABLE_DRAWING_INFO_OVERLAYS_ON_ALL_CODE_EDITOR_STAGES;
   static const std::string DISABLE_DRAWING_INFO_OVERLAYS_ON_ALL_CODE_EDITOR_STAGES;
   static const std::string PUSH_FILE_NAVIGATOR_SELECTION;
   static const std::string PUSH_PROJECT_NAVIGATOR_SELECTION;
   static const std::string PUSH_PROJECT_FOLDERS_SELECTION;
   static const std::string PUSH_COMPONENT_NAVIGATOR_SELECTION;
   static const std::string PUSH_COMPONENT_RELATIONS_NAVIGATOR_SELECTION;
   static const std::string REFRESH_REGEX_HILIGHTS_ON_FRONTMOST_STAGE;
   static const std::string REFRESH_REGEX_HILIGHTS_ON_ALL_CODE_EDITOR_STAGES;
   static const std::string REFRESH_GIT_MODIFIED_LINE_NUMBERS_ON_ALL_CODE_EDITOR_STAGES;
   static const std::string SET_SEARCH_REGEX_EXPRESSION_ON_ALL_CODE_EDITOR_STAGES_TO_REGEX_TEMP_FILE_CONTENTS;
   static const std::string SET_REGEX_TEMP_FILE_CONTENTS_TO_WORD_UNDER_CURRENT_ADVANCED_CODE_EDITOR_CURSOR;
   static const std::string INCREMENT_SEARCH_COUNT_IF_SEARCH_REGEX_IS_NONBLANK;
   static const std::string REMOVE_FILE_IS_UNSAVED_NOTIFICATION;
   static const std::string TOGGLE_COMMAND_MODE_ON;
   static const std::string TOGGLE_COMMAND_MODE_OFF;
   static const std::string RESET_CAMERA_TO_CENTER;
   static const std::string ROTATE_STAGE_LEFT;
   static const std::string ROTATE_STAGE_RIGHT;
   static const std::string RUN_PROJECT_TESTS;
   static const std::string SAVE_FRONTMOST_CODE_EDITOR_STAGE_AND_TOUCH_IF_SYMLINK;
   static const std::string SEND_MESSAGE_TO_DAEMUS_TO_BUILD;
   static const std::string SPAWN_MULTIPLEX_DELETE_MENU;
   static const std::string SPAWN_MULTIPLEX_CHANGE_MENU;
   static const std::string SPAWN_MULTIPLEX_GOTO_MENU;
   static const std::string SPAWN_FANCY;
   static const std::string SPAWN_COMPONENT_RELATIONS_NAVIGATOR;
   static const std::string SPAWN_COMPONENT_NAVIGATOR;
   static const std::string SPAWN_PROJECT_NAVIGATOR;
   static const std::string SPAWN_PROJECT_FOLDERS_WINDOW;
   static const std::string SPAWN_FILE_NAVIGATOR;
   static const std::string SPAWN_CHAT_GPT_CHAT;
   static const std::string SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL;
   static const std::string PARSE_TEST_RESULTS_FROM_LAST_TEST_RUN_DUMP;
   static const std::string SPAWN_GIT_COMMIT_MESSAGE_INPUT_BOX_MODAL;
   static const std::string SUBMIT_CURRENT_MODAL;
   static const std::string FX__PLAY_FOCUS_ANIMATION_ON_FRONTMOST_STAGE;
   static const std::string CHECK_GIT_SYNC_AND_UPDATE_POWERBAR;
   static const std::string OPEN_DOCUMENTATION_IN_BROWSER;
   static const std::string COMMIT_ALL_FILES_WITH_LAST_GIT_COMMIT_MESSAGE_FROM_REGEX_TEMP_FILE_CONTENTS;
   static const std::string APPEND_PACKET_USING_LAST_COMMIT_MESSAGE_AND_CLEAR_SCORES;
   static const std::string PUSH_TO_GIT_REMOTE;
   static const std::string SPAWN_CLASS_BRIEF_MENU;
   static const std::string SPAWN_DRAWING_BOX;

};


