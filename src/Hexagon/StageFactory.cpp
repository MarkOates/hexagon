

#include <Hexagon/StageFactory.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <Hexagon/RerunOutputWatcher/Stage.hpp>
#include <Hexagon/FileNavigator/Stage.hpp>
#include <Hexagon/StageInterface.hpp>
#include <Hexagon/MissingFile/Stage.hpp>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <Hexagon/AdvancedComponentNavigator/Stage.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro.h>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{


StageFactory::StageFactory(Hexagon::System::Config* config, AllegroFlare::FontBin* font_bin)
   : config(config)
   , font_bin(font_bin)
{
}


StageFactory::~StageFactory()
{
}


std::string StageFactory::obtain_default_navigator_directory()
{
if (!(config))
   {
      std::stringstream error_message;
      error_message << "StageFactory" << "::" << "obtain_default_navigator_directory" << ": error: " << "guard \"config\" not met";
      throw std::runtime_error(error_message.str());
   }
return config->get_default_navigator_directory();

}

ALLEGRO_COLOR StageFactory::obtain_base_text_color()
{
if (!(config))
   {
      std::stringstream error_message;
      error_message << "StageFactory" << "::" << "obtain_base_text_color" << ": error: " << "guard \"config\" not met";
      throw std::runtime_error(error_message.str());
   }
return config->get_base_text_color();

}

std::string StageFactory::obtain_regex_temp_filename()
{
if (!(config))
   {
      std::stringstream error_message;
      error_message << "StageFactory" << "::" << "obtain_regex_temp_filename" << ": error: " << "guard \"config\" not met";
      throw std::runtime_error(error_message.str());
   }
return config->get_regex_temp_filename();

}

ALLEGRO_COLOR StageFactory::obtain_base_backfill_color()
{
if (!(config))
   {
      std::stringstream error_message;
      error_message << "StageFactory" << "::" << "obtain_base_backfill_color" << ": error: " << "guard \"config\" not met";
      throw std::runtime_error(error_message.str());
   }
return config->get_backfill_color();

}

ALLEGRO_FONT* StageFactory::obtain_component_navigator_font()
{
if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "StageFactory" << "::" << "obtain_component_navigator_font" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
return font_bin->auto_get("Menlo-Regular.ttf -18");

}

ALLEGRO_FONT* StageFactory::obtain_file_navigator_font()
{
if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "StageFactory" << "::" << "obtain_file_navigator_font" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
return font_bin->auto_get("consolas.ttf -18");

}

ALLEGRO_FONT* StageFactory::obtain_global_font()
{
if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "StageFactory" << "::" << "obtain_global_font" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
return font_bin->auto_get("Menlo-Regular.ttf -20");

}

ALLEGRO_FONT* StageFactory::obtain_git_commit_message_box_font()
{
if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "StageFactory" << "::" << "obtain_git_commit_message_box_font" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
return font_bin->auto_get("Purista Medium.otf -22");

}

int StageFactory::obtain_display_default_width()
{
if (!(config))
   {
      std::stringstream error_message;
      error_message << "StageFactory" << "::" << "obtain_display_default_width" << ": error: " << "guard \"config\" not met";
      throw std::runtime_error(error_message.str());
   }
return config->get_initial_display_width();

}

int StageFactory::obtain_display_default_height()
{
if (!(config))
   {
      std::stringstream error_message;
      error_message << "StageFactory" << "::" << "obtain_display_default_height" << ": error: " << "guard \"config\" not met";
      throw std::runtime_error(error_message.str());
   }
return config->get_initial_display_height();

}

StageInterface* StageFactory::create()
{
return nullptr;

}

StageInterface* StageFactory::create_rerun_output_watcher()
{
float golden_ratio = 0.61803f;
float x_pos = golden_ratio * obtain_display_default_width() - obtain_display_default_width()/2;
placement3d place(x_pos, -obtain_display_default_height()/2 + 30, 0);
place.size = vec3d(0, 0, 0.0);
place.align = vec3d(0, 0, 0);
place.scale = vec3d(0.7, 0.7, 0.0);

Hexagon::RerunOutputWatcher::Stage *rerun_output_watcher = new Hexagon::RerunOutputWatcher::Stage();
rerun_output_watcher->set_place(place);
rerun_output_watcher->set_font(obtain_global_font());

return rerun_output_watcher;

}

StageInterface* StageFactory::create_file_navigator(std::string directory)
{
std::string directory_to_start = directory.empty() ? obtain_default_navigator_directory() : directory;

ALLEGRO_FONT *font = obtain_file_navigator_font();
Hexagon::FileNavigator::Stage *file_navigator
   = new Hexagon::FileNavigator::Stage(directory_to_start);
file_navigator->process_local_event("refresh_list"); // TODO: similar to another comment existing in this file
                                                     // at the time of this writing
file_navigator->set_place(build_file_navigator_initial_place());
file_navigator->set_render_on_hud(true);

// properties previously assigned at render time:
ALLEGRO_DISPLAY *display = get_current_display();
int cell_width = al_get_text_width(font, " ");
int cell_height = al_get_font_line_height(font);

file_navigator->set_display(display);
file_navigator->set_font(font);
file_navigator->set_cell_width(cell_width);
file_navigator->set_cell_height(cell_height);

return file_navigator;

}

StageInterface* StageFactory::create_missing_file(std::string filename)
{
Hexagon::MissingFile::Stage *stage = new Hexagon::MissingFile::Stage(filename);
stage->set_font(obtain_global_font());
return stage;

}

StageInterface* StageFactory::create_regex_input_box_modal()
{
// TODO: extract this one line input box from CodeEditor
Hexagon::CodeEditor::Stage *stage = new Hexagon::CodeEditor::Stage({
      obtain_regex_temp_filename(),
      "input_box",
      ::CodeEditor::CodeEditor::INSERT,
      StageInterface::ONE_LINE_INPUT_BOX
   });
stage->set_place(build_regex_input_box_initial_place());
stage->set_font(obtain_global_font());
stage->set_render_on_hud(true);
stage->get_code_editor_ref().set_initial_content(std::vector<std::string>{ "" });

// properties previously assigned at render time:
ALLEGRO_FONT *font = obtain_global_font();
ALLEGRO_DISPLAY *display = get_current_display();
int cell_width = al_get_text_width(font, " ");
int cell_height = al_get_font_line_height(font);

stage->set_display(display);
stage->set_cell_width(cell_width);
stage->set_cell_height(cell_height);

return stage;

}

StageInterface* StageFactory::create_git_commit_message_box()
{
Hexagon::CodeEditor::Stage *stage = new Hexagon::CodeEditor::Stage(
   {
      obtain_regex_temp_filename(),
      "git_commit_message_input_box",
      ::CodeEditor::CodeEditor::INSERT,
      StageInterface::GIT_COMMIT_MESSAGE_INPUT_BOX
   });

stage->set_place(build_git_commit_message_input_box_initial_place());
stage->set_font(obtain_git_commit_message_box_font());
stage->set_render_on_hud(true);
stage->get_code_editor_ref().set_initial_content(std::vector<std::string>{ "" });

// properties previously assigned at render time:
ALLEGRO_DISPLAY *display = get_current_display();
ALLEGRO_FONT *font = obtain_git_commit_message_box_font();
int cell_width = al_get_text_width(font, " ");
int cell_height = al_get_font_line_height(font);

stage->set_display(display);
stage->set_font(font);
stage->set_cell_width(cell_width);
stage->set_cell_height(cell_height);

return stage;

}

StageInterface* StageFactory::create_advanced_component_navigator()
{
Hexagon::AdvancedComponentNavigator::Stage *result =
   new Hexagon::AdvancedComponentNavigator::Stage(obtain_default_navigator_directory());

result->process_local_event("refresh_list"); // TODO: find a test technique for this,
                                             // I feel like this event should not be run real-time
                                             // it's blocking and requests from the filesystem so
                                             // this refresh should be part of an operation that
                                             // happens after the creation, or something like that
result->set_render_on_hud(true);
result->set_base_text_color(obtain_base_text_color());
result->set_base_backfill_color(obtain_base_backfill_color());
result->set_place(build_component_navigator_initial_place());

// properties previously assigned at render time:
ALLEGRO_DISPLAY *display = get_current_display();
ALLEGRO_FONT *font = obtain_component_navigator_font();
int cell_width = al_get_text_width(font, " ");
int cell_height = al_get_font_line_height(font);

result->set_display(display);
result->set_font(font);
result->set_cell_width(cell_width);
result->set_cell_height(cell_height);

return result;

}

ALLEGRO_DISPLAY* StageFactory::get_current_display()
{
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "StageFactory" << "::" << "get_current_display" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "StageFactory" << "::" << "get_current_display" << ": error: " << "guard \"al_get_current_display()\" not met";
      throw std::runtime_error(error_message.str());
   }
return al_get_current_display();

}

placement3d StageFactory::build_component_navigator_initial_place()
{
ALLEGRO_DISPLAY *display = get_current_display();
placement3d result;
result.position = vec3d(al_get_display_width(display)/2, al_get_display_height(display)/2, 0);
result.size = vec3d(800, 700, 0);
result.align = vec3d(0.5, 0.5, 0.5);
result.scale = vec3d(1.0, 1.0, 1.0);
result.rotation = vec3d(0.0, 0.0, 0.0);
return result;

}

placement3d StageFactory::build_file_navigator_initial_place()
{
ALLEGRO_DISPLAY *display = get_current_display();
placement3d result;
result.position = vec3d(al_get_display_width(display)/2, al_get_display_height(display)/2, 0);
result.size = vec3d(500, 600, 0);
result.align = vec3d(0.5, 0.5, 0);
result.scale = vec3d(0.8, 0.8, 1.0);
result.rotation = vec3d(0.0, 0.0, 0.0);
return result;

}

placement3d StageFactory::build_git_commit_message_input_box_initial_place()
{
ALLEGRO_DISPLAY *display = get_current_display();
int surface_width = al_get_display_width(display);
int surface_height = al_get_display_height(display);
placement3d place(surface_width*0.5f, surface_height*0.5f, 0.0);
place.size = vec3d(600, 25, 0.0);
place.scale = vec3d(1.5, 1.5, 1.0);
place.rotation = vec3d(0.0, 0.0, 0.0);
return place;

}

placement3d StageFactory::build_regex_input_box_initial_place()
{
ALLEGRO_DISPLAY *display = get_current_display();
int surface_width = al_get_display_width(display);
int surface_height = al_get_display_height(display);
placement3d place(surface_width*0.5f, surface_height*0.5f, 0.0);
place.size = vec3d(300, 25, 0.0);
place.scale = vec3d(1.5, 1.5, 1.0);
place.rotation = vec3d(0.0, 0.0, 0.0);
return place;

}
} // namespace Hexagon


