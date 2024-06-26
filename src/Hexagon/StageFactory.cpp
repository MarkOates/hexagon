

#include <Hexagon/StageFactory.hpp>

#include <AllegroFlare/Color.hpp>
#include <Blast/Project/SymlinkChecker.hpp>
#include <Blast/StringSplitter.hpp>
#include <Hexagon/AdvancedCodeEditor/Stage.hpp>
#include <Hexagon/AdvancedComponentNavigator/Stage.hpp>
#include <Hexagon/ChatGPTIntegration/Chat/Stage.hpp>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <Hexagon/ComponentRelationsNavigator/ComponentRelations.hpp>
#include <Hexagon/ComponentRelationsNavigator/Stage.hpp>
#include <Hexagon/Fancy/Stage.hpp>
#include <Hexagon/FileNavigator/Stage.hpp>
#include <Hexagon/GitCommitMessageInputBox/Stage.hpp>
#include <Hexagon/MissingFile/Stage.hpp>
#include <Hexagon/MultiplexMenu/MultiplexMenuPage.hpp>
#include <Hexagon/MultiplexMenu/Stage.hpp>
#include <Hexagon/Notifications/Stage.hpp>
#include <Hexagon/OneLineInputBox/Stage.hpp>
#include <Hexagon/ProjectFoldersView.hpp>
#include <Hexagon/ProjectNavigator.hpp>
#include <Hexagon/StageInterface.hpp>
#include <Hexagon/UI/DrawingBox.hpp>
#include <Hexagon/UI/LittleMenu.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro_flare/useful_php.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>


namespace Hexagon
{


StageFactory::StageFactory(Hexagon::System::Config* config, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin)
   : config(config)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , hud_render_surface_projection_width(1920)
   , hud_render_surface_projection_height(1080)
{
}


StageFactory::~StageFactory()
{
}


float StageFactory::get_hud_render_surface_projection_width() const
{
   return hud_render_surface_projection_width;
}


float StageFactory::get_hud_render_surface_projection_height() const
{
   return hud_render_surface_projection_height;
}


ALLEGRO_COLOR StageFactory::obtain_base_text_color()
{
   if (!(config))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::StageFactory::obtain_base_text_color]: error: guard \"config\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::StageFactory::obtain_base_text_color]: error: guard \"config\" not met");
   }
   return config->get_base_text_color();
}

std::string StageFactory::obtain_regex_temp_filename()
{
   if (!(config))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::StageFactory::obtain_regex_temp_filename]: error: guard \"config\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::StageFactory::obtain_regex_temp_filename]: error: guard \"config\" not met");
   }
   return config->get_regex_temp_filename();
}

ALLEGRO_COLOR StageFactory::obtain_base_backfill_color()
{
   if (!(config))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::StageFactory::obtain_base_backfill_color]: error: guard \"config\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::StageFactory::obtain_base_backfill_color]: error: guard \"config\" not met");
   }
   return config->get_backfill_color();
}

ALLEGRO_FONT* StageFactory::obtain_component_navigator_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::StageFactory::obtain_component_navigator_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::StageFactory::obtain_component_navigator_font]: error: guard \"font_bin\" not met");
   }
   //return font_bin->auto_get("Menlo-Regular.ttf -18");
   return font_bin->auto_get("Purista Medium.otf -18");
}

ALLEGRO_FONT* StageFactory::obtain_file_navigator_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::StageFactory::obtain_file_navigator_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::StageFactory::obtain_file_navigator_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("consolas.ttf -18");
}

ALLEGRO_FONT* StageFactory::obtain_global_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::StageFactory::obtain_global_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::StageFactory::obtain_global_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Menlo-Regular.ttf -20");
}

ALLEGRO_FONT* StageFactory::obtain_git_commit_message_box_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::StageFactory::obtain_git_commit_message_box_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::StageFactory::obtain_git_commit_message_box_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Purista Medium.otf -22");
}

int StageFactory::obtain_display_default_width()
{
   if (!(config))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::StageFactory::obtain_display_default_width]: error: guard \"config\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::StageFactory::obtain_display_default_width]: error: guard \"config\" not met");
   }
   return config->get_initial_display_width();
}

int StageFactory::obtain_display_default_height()
{
   if (!(config))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::StageFactory::obtain_display_default_height]: error: guard \"config\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::StageFactory::obtain_display_default_height]: error: guard \"config\" not met");
   }
   return config->get_initial_display_height();
}

bool StageFactory::obtain_dark_mode()
{
   if (!(config))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::StageFactory::obtain_dark_mode]: error: guard \"config\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::StageFactory::obtain_dark_mode]: error: guard \"config\" not met");
   }
   return config->is_dark_mode();
}

StageInterface* StageFactory::create_notification(std::string body_text)
{
   Hexagon::Notifications::Stage *stage = new Hexagon::Notifications::Stage(body_text);
   stage->set_render_on_hud(true);
   return stage;
}

StageInterface* StageFactory::create_file_navigator(std::string project_directory)
{
   std::string directory_to_start = project_directory;

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

StageInterface* StageFactory::create_class_brief_menu(std::string title, std::vector<std::tuple<std::string, std::string>> items)
{
   Hexagon::UI::LittleMenu *little_menu = new Hexagon::UI::LittleMenu(font_bin, title, items);
   little_menu->initialize();
   little_menu->set_render_on_hud(true);
   little_menu->set_place(build_centered_on_hud_initial_place(0, 300));
   return little_menu;
}

StageInterface* StageFactory::create_chat_gpt_chat()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::StageFactory::create_chat_gpt_chat]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::StageFactory::create_chat_gpt_chat]: error: guard \"bitmap_bin\" not met");
   }
   Hexagon::ChatGPTIntegration::Chat::Stage *result = new Hexagon::ChatGPTIntegration::Chat::Stage();
   result->set_bitmap_bin(bitmap_bin);
   result->set_font_bin(font_bin);
   result->initialize();
   return result;
}

StageInterface* StageFactory::create_component_relations_navigator(std::string focused_component_name, std::string current_project_directory, bool simplify_relatives_names)
{
   Blast::Project::Component self_component(focused_component_name, current_project_directory);

   Hexagon::ComponentRelationsNavigator::ComponentRelations component_relations(self_component);

   std::vector<std::tuple<std::string, std::string>> dependents_menu_items = {};
   std::vector<std::tuple<std::string, std::string>> relatives_menu_items = {};
   std::vector<std::tuple<std::string, std::string>> dependencies_menu_items = {};

   for (auto &relatives_menu_item : component_relations.build_relatives_list())
   {
      std::string relatives_menu_item_label = relatives_menu_item;
      if (simplify_relatives_names)
      {
         std::vector<std::string> relatives_menu_item_label_fragments =
            Blast::StringSplitter(relatives_menu_item, '/').split();
         if (relatives_menu_item_label_fragments.size() >= 2)
         {
            relatives_menu_item_label =
               relatives_menu_item_label_fragments[relatives_menu_item_label_fragments.size()-2]
               + "/" + relatives_menu_item_label_fragments.back();
         }
         else if (relatives_menu_item_label_fragments.size() == 1)
         {
            relatives_menu_item_label = relatives_menu_item_label_fragments.back();
         }
      }

      relatives_menu_items.push_back({relatives_menu_item_label, relatives_menu_item});
   }

   for (auto &dependents_menu_item : component_relations.build_dependents_list())
   {
      dependents_menu_items.push_back({dependents_menu_item, dependents_menu_item});
   }

   for (auto &dependencies_menu_item : component_relations.build_dependencies_list())
   {
      dependencies_menu_items.push_back({dependencies_menu_item, dependencies_menu_item});
   }

   Hexagon::ComponentRelationsNavigator::Stage *component_relations_navigator =
      new Hexagon::ComponentRelationsNavigator::Stage(
         font_bin,
         dependents_menu_items,
         relatives_menu_items,
         dependencies_menu_items
   );

   component_relations_navigator->initialize();
   component_relations_navigator->set_render_on_hud(true);
   placement3d place = build_centered_on_hud_initial_place(0, 0);
   place.position.y -= 100;
   place.scale.x = place.scale.y = 0.75;
   component_relations_navigator->set_place(place);

   return component_relations_navigator;
}

StageInterface* StageFactory::create_fancy()
{
   ALLEGRO_DISPLAY *display = get_current_display();
   int width = get_hud_render_surface_projection_width();
   int height = get_hud_render_surface_projection_height();

   Hexagon::Fancy::Stage *fancy_stage = new Hexagon::Fancy::Stage(font_bin);
   //fancy_stage->initialize();

   fancy_stage->set_render_on_hud(true);

   return fancy_stage;
}

StageInterface* StageFactory::create_drawing_box()
{
   ALLEGRO_DISPLAY *display = get_current_display();

   //int width = al_get_display_width(display);
   int width = get_hud_render_surface_projection_width();
   //int height = al_get_display_height(display);
   int height = get_hud_render_surface_projection_height();

   Hexagon::UI::DrawingBox *drawing_box = new Hexagon::UI::DrawingBox(font_bin, width, height);
   drawing_box->initialize();

   drawing_box->set_render_on_hud(true);
   //drawing_box->set_place(build_centered_on_hud_initial_place(width, height));
   //drawing_box->set_place(build_centered_on_hud_initial_place(width, height));

   return drawing_box;
}

StageInterface* StageFactory::create_missing_file(std::string filename)
{
   Hexagon::MissingFile::Stage *missing_file_stage = new Hexagon::MissingFile::Stage(font_bin, filename);

   ALLEGRO_FONT *font = obtain_global_font();
   ALLEGRO_DISPLAY *display = get_current_display();
   int cell_width = al_get_text_width(font, " ");
   int cell_height = al_get_font_line_height(font);

   missing_file_stage->set_display(display);
   missing_file_stage->set_font(font);
   missing_file_stage->set_cell_width(cell_width);
   missing_file_stage->set_cell_height(cell_height);

   return missing_file_stage;
}

StageInterface* StageFactory::create_advanced_code_editor(std::string filename, int num_columns, int num_rows)
{
   Hexagon::AdvancedCodeEditor::Stage *advanced_code_editor_stage =
      new Hexagon::AdvancedCodeEditor::Stage(font_bin, num_columns, num_rows);
   advanced_code_editor_stage->set_on_color(obtain_base_text_color()); // TODO: these should be able to be set
                                                                       // after initialization
   if (!obtain_dark_mode())
   {
      //ALLEGRO_COLOR syntax_highlight_color = ALLEGRO_COLOR{0.75f, 0.96f, 1.0f, 1.0f};
      //ALLEGRO_COLOR on_color = ALLEGRO_COLOR{1.0f, 1.0f, 0.0f, 1.0f};
      //ALLEGRO_COLOR comment_color = ALLEGRO_COLOR{0.5f, 0.5f, 0.5f, 0.5f};
      //ALLEGRO_COLOR clear_color = ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f};

      ALLEGRO_COLOR on_color = ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 1.0f};
      ALLEGRO_COLOR syntax_highlight_color =
         AllegroFlare::color::mix(on_color, ALLEGRO_COLOR{0.5f, 0.75f, 1.0f, 1.0f}, 0.56);
      ALLEGRO_COLOR comment_color = ALLEGRO_COLOR{0.2, 0.21, 0.28, 0.5f}; //AllegroFlare::color::color(on_color, 0.5);
      ALLEGRO_COLOR clear_color = ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f};

      advanced_code_editor_stage->set_syntax_highlight_color(syntax_highlight_color);
      advanced_code_editor_stage->set_on_color(on_color);
      advanced_code_editor_stage->set_comment_color(comment_color);
      advanced_code_editor_stage->set_clear_color(clear_color);

      ALLEGRO_COLOR base_backfill_color = obtain_base_backfill_color();
      ALLEGRO_COLOR &bbc = base_backfill_color;
      ALLEGRO_COLOR inv_base_backfill_color = ALLEGRO_COLOR{1.0f - bbc.r, 1.0f - bbc.g, 1.0f - bbc.b, 1.0f};

      ALLEGRO_COLOR null_space_color = AllegroFlare::color::color(inv_base_backfill_color, 0.05);
      ALLEGRO_COLOR backfill_color = AllegroFlare::color::color(inv_base_backfill_color, 0.025);
      advanced_code_editor_stage->set_null_space_color(null_space_color);
      advanced_code_editor_stage->set_backfill_color(backfill_color);
   }

   advanced_code_editor_stage->initialize();

   std::string file_contents = php::file_get_contents(filename);
   bool is_symlink = Blast::Project::SymlinkChecker(filename).is_symlink();
   advanced_code_editor_stage->set_represents_symlink(is_symlink);
   advanced_code_editor_stage->set_filename(filename);
   advanced_code_editor_stage->set_content(file_contents);
   advanced_code_editor_stage->set_show_line_too_long(true);

   return advanced_code_editor_stage;
}

StageInterface* StageFactory::create_code_editor(std::string filename, std::string file_category)
{
   Hexagon::CodeEditor::Stage *code_editor_stage = new Hexagon::CodeEditor::Stage(
      ::CodeEditor::CodeEditor{filename, file_category}
   );

   // properties previously assigned at render time:
   ALLEGRO_FONT *font = obtain_global_font();
   ALLEGRO_DISPLAY *display = get_current_display();
   int cell_width = al_get_text_width(font, " ");
   int cell_height = al_get_font_line_height(font);

   bool is_symlink = Blast::Project::SymlinkChecker(filename).is_symlink();

   code_editor_stage->set_represents_a_symlink(is_symlink);
   code_editor_stage->set_display(display);
   code_editor_stage->set_font(font);
   code_editor_stage->set_font_bin(font_bin);
   code_editor_stage->set_cell_width(cell_width);
   code_editor_stage->set_cell_height(cell_height);

   return code_editor_stage;
}

StageInterface* StageFactory::create_delete_multiplex_menu(Hexagon::AdvancedCodeEditor::Stage* advanced_code_editor_stage, Hexagon::System::System* system)
{
   Hexagon::MultiplexMenu::MultiplexMenu delete_multiplex_menu = build_full_multiplex_menu();

   Hexagon::MultiplexMenu::Stage *stage = new Hexagon::MultiplexMenu::Stage(
      font_bin,
      advanced_code_editor_stage,
      system,
      delete_multiplex_menu
   );

   stage->open_page("start");
   stage->open_page("page_delete");

   stage->set_place(build_multiplex_menu_initial_place());
   stage->set_render_on_hud(true);
   return stage;
}

StageInterface* StageFactory::create_change_multiplex_menu(Hexagon::AdvancedCodeEditor::Stage* advanced_code_editor_stage, Hexagon::System::System* system)
{
   Hexagon::MultiplexMenu::MultiplexMenu delete_multiplex_menu = build_full_multiplex_menu();

   Hexagon::MultiplexMenu::Stage *stage = new Hexagon::MultiplexMenu::Stage(
      font_bin,
      advanced_code_editor_stage,
      system,
      delete_multiplex_menu
   );

   stage->open_page("start");
   stage->open_page("page_change");

   stage->set_place(build_multiplex_menu_initial_place());
   stage->set_render_on_hud(true);
   return stage;
}

StageInterface* StageFactory::create_goto_multiplex_menu(Hexagon::AdvancedCodeEditor::Stage* advanced_code_editor_stage, Hexagon::System::System* system)
{
   Hexagon::MultiplexMenu::MultiplexMenu delete_multiplex_menu = build_full_multiplex_menu();

   Hexagon::MultiplexMenu::Stage *stage = new Hexagon::MultiplexMenu::Stage(
      font_bin,
      advanced_code_editor_stage,
      system,
      delete_multiplex_menu
   );

   stage->open_page("start");
   stage->open_page("page_goto");

   stage->set_place(build_multiplex_menu_initial_place());
   stage->set_render_on_hud(true);
   return stage;
}

StageInterface* StageFactory::create_regex_input_box_modal()
{
   // TODO: extract this one line input box from CodeEditor
   //Hexagon::CodeEditor::Stage *stage = new Hexagon::CodeEditor::Stage({
   //      obtain_regex_temp_filename(),
   //      "input_box",
   //      ::CodeEditor::CodeEditor::INSERT,
   //      StageInterface::ONE_LINE_INPUT_BOX
   //   });
   Hexagon::OneLineInputBox::Stage *stage = new Hexagon::OneLineInputBox::Stage({
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
   Hexagon::GitCommitMessageInputBox::Stage *stage = new Hexagon::GitCommitMessageInputBox::Stage(
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

StageInterface* StageFactory::create_advanced_component_navigator(std::string project_directory, std::string initial_search_text)
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::StageFactory::create_advanced_component_navigator]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::StageFactory::create_advanced_component_navigator]: error: guard \"font_bin\" not met");
   }
   Hexagon::AdvancedComponentNavigator::Stage *result =
      new Hexagon::AdvancedComponentNavigator::Stage(project_directory);

   result->process_local_event("refresh_list"); // TODO: find a test technique for this,
                                                // I feel like this event should not be run real-time
                                                // it's blocking and requests from the filesystem so
                                                // this refresh should be part of an operation that
                                                // happens after the creation, or something like that
   result->set_font_bin(font_bin);
   result->set_render_on_hud(false);
   result->set_base_text_color(obtain_base_text_color());
   result->set_base_backfill_color(obtain_base_backfill_color());

   bool stage_is_on_hud = true;
   if (stage_is_on_hud)
   {
      result->set_render_on_hud(true);
      result->set_place(build_centered_on_hud_initial_place(600, 700));
   }
   else
   {
      result->set_render_on_hud(false);
      result->set_place(build_centered_in_world_initial_place(600, 700));
   }


   // properties previously assigned at render time:
   ALLEGRO_DISPLAY *display = get_current_display();
   ALLEGRO_FONT *font = obtain_component_navigator_font();
   int cell_width = al_get_text_width(font, " ");
   int cell_height = al_get_font_line_height(font);

   result->set_display(display);
   result->set_font(font);
   result->set_cell_width(cell_width);
   result->set_cell_height(cell_height);

   if (!initial_search_text.empty())
   {
      result->get_component_ref().set_search_text(initial_search_text);
      result->get_component_ref().refresh_list();
   }

   return result;
}

StageInterface* StageFactory::create_project_navigator(std::vector<std::tuple<std::string, std::string>> project_menu_items)
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::StageFactory::create_project_navigator]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::StageFactory::create_project_navigator]: error: guard \"font_bin\" not met");
   }
   Hexagon::ProjectNavigator *result = new Hexagon::ProjectNavigator(font_bin);

   //result->set_font_bin(font_bin);
   result->set_render_on_hud(true);
   //result->set_base_text_color(obtain_base_text_color());
   //result->set_base_backfill_color(obtain_base_backfill_color());
   result->set_place(build_centered_on_hud_initial_place(600, 700));

   if (project_menu_items.empty())
   {
      std::vector<std::tuple<std::string, std::string>> default_project_menu_items =
         Hexagon::ProjectNavigator::build_placeholder_menu_items();
      project_menu_items = default_project_menu_items;
   }

   result->set_menu_items(project_menu_items);
   result->initialize();

   //ALLEGRO_DISPLAY *display = get_current_display();
   //ALLEGRO_FONT *font = obtain_component_navigator_font();
   //int cell_width = al_get_text_width(font, " ");
   //int cell_height = al_get_font_line_height(font);

   //result->set_display(display);
   //result->set_font(font);
   //result->set_cell_width(cell_width);
   //result->set_cell_height(cell_height);

   return result;
}

StageInterface* StageFactory::create_project_folders_view(std::string project_directory)
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::StageFactory::create_project_folders_view]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::StageFactory::create_project_folders_view]: error: guard \"font_bin\" not met");
   }
   Hexagon::ProjectFoldersView *result = new Hexagon::ProjectFoldersView(font_bin, project_directory);

   //result->set_font_bin(font_bin);
   result->set_render_on_hud(true);
   //result->set_base_text_color(obtain_base_text_color());
   //result->set_base_backfill_color(obtain_base_backfill_color());
   result->set_place(build_centered_on_hud_initial_place(600, 700));

   //if (project_menu_items.empty())
   //{
      //std::vector<std::tuple<std::string, std::string>> default_project_menu_items =
         //Hexagon::ProjectFoldersView::build_placeholder_menu_items();
      //project_menu_items = default_project_menu_items;
   //}

   //result->set_menu_items(project_menu_items);
   //result->set_project_directory(project_directory);
   result->initialize();

   //ALLEGRO_DISPLAY *display = get_current_display();
   //ALLEGRO_FONT *font = obtain_component_navigator_font();
   //int cell_width = al_get_text_width(font, " ");
   //int cell_height = al_get_font_line_height(font);

   //result->set_display(display);
   //result->set_font(font);
   //result->set_cell_width(cell_width);
   //result->set_cell_height(cell_height);

   return result;
}

ALLEGRO_DISPLAY* StageFactory::get_current_display()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::StageFactory::get_current_display]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::StageFactory::get_current_display]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::StageFactory::get_current_display]: error: guard \"al_get_current_display()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::StageFactory::get_current_display]: error: guard \"al_get_current_display()\" not met");
   }
   return al_get_current_display();
}

placement3d StageFactory::build_centered_on_hud_initial_place(float width, float height)
{
   ALLEGRO_DISPLAY *display = get_current_display();
   float surface_width = get_hud_render_surface_projection_width();
   float surface_height = get_hud_render_surface_projection_height();
   placement3d result;
   //result.position = vec3d(get_display_width(display)/2, al_get_display_height(display)/2, 0);
   result.position = vec3d(surface_width/2, surface_height/2, 0);
   result.size = vec3d(width, height, 0);
   result.align = vec3d(0.5, 0.5, 0.5);
   result.scale = vec3d(1.0, 1.0, 1.0);
   result.rotation = vec3d(0.0, 0.0, 0.0);
   return result;
}

placement3d StageFactory::build_centered_in_world_initial_place(float width, float height)
{
   ALLEGRO_DISPLAY *display = get_current_display();
   float surface_width = 0; //get_hud_render_surface_projection_width();
   float surface_height = 0; //get_hud_render_surface_projection_height();
   placement3d result;
   //result.position = vec3d(get_display_width(display)/2, al_get_display_height(display)/2, 0);
   result.position = vec3d(surface_width/2, surface_height/2, 0);
   result.size = vec3d(width, height, 0);
   result.align = vec3d(0.5, 0.5, 0.5);
   result.scale = vec3d(1.0, 1.0, 1.0);
   result.rotation = vec3d(0.0, 0.0, 0.0);
   return result;
}

placement3d StageFactory::build_file_navigator_initial_place()
{
   float surface_width = get_hud_render_surface_projection_width();
   float surface_height = get_hud_render_surface_projection_height();
   placement3d result;
   //result.position = vec3d(get_display_width(display)/2, al_get_display_height(display)/2, 0);
   result.position = vec3d(surface_width/2, surface_height/2, 0);
   ALLEGRO_DISPLAY *display = get_current_display();
   result.size = vec3d(500, 600, 0);
   result.align = vec3d(0.5, 0.5, 0);
   result.scale = vec3d(0.8, 0.8, 1.0);
   result.rotation = vec3d(0.0, 0.0, 0.0);
   return result;
}

placement3d StageFactory::build_multiplex_menu_initial_place()
{
   float surface_width = get_hud_render_surface_projection_width();
   float surface_height = get_hud_render_surface_projection_height();
   float height = al_get_font_line_height(obtain_git_commit_message_box_font());

   //ALLEGRO_DISPLAY *display = get_current_display();
   //int surface_width = al_get_display_width(display);
   //int surface_height = al_get_display_height(display);
   placement3d place(surface_width*0.5f, surface_height*0.5f + 20, 0.0);
   place.size = vec3d(680, height, 0.0);
   place.scale = vec3d(0.5, 0.5, 1.0);
   place.rotation = vec3d(0.0, 0.0, 0.0);
   return place;
}

placement3d StageFactory::build_git_commit_message_input_box_initial_place()
{
   float surface_width = get_hud_render_surface_projection_width();
   float surface_height = get_hud_render_surface_projection_height();
   float height = al_get_font_line_height(obtain_git_commit_message_box_font());

   //ALLEGRO_DISPLAY *display = get_current_display();
   //int surface_width = al_get_display_width(display);
   //int surface_height = al_get_display_height(display);
   placement3d place(surface_width*0.5f, surface_height*0.5f + 20, 0.0);
   place.size = vec3d(680, height, 0.0);
   place.scale = vec3d(1.2, 1.2, 1.0);
   place.rotation = vec3d(0.0, 0.0, 0.0);
   return place;
}

placement3d StageFactory::build_regex_input_box_initial_place()
{
   float surface_width = get_hud_render_surface_projection_width();
   float surface_height = get_hud_render_surface_projection_height();
   //ALLEGRO_DISPLAY *display = get_current_display();
   //int surface_width = al_get_display_width(display);
   //int surface_height = al_get_display_height(display);
   placement3d place(surface_width*0.5f, surface_height*0.5f, 0.0);
   place.size = vec3d(400, 25, 0.0);
   place.scale = vec3d(1.5, 1.5, 1.0);
   place.rotation = vec3d(0.0, 0.0, 0.0);
   return place;
}

Hexagon::MultiplexMenu::MultiplexMenu StageFactory::build_full_multiplex_menu()
{
   Hexagon::MultiplexMenu::MultiplexMenuPage start_page(
   {
      Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_D}, "Delete >", { "open_page:page_delete" } ),
      Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_C}, "Change >", { "open_page:page_change" } ),
      Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_G}, "Go to >", { "open_page:page_goto" } ),
   });

   Hexagon::MultiplexMenu::MultiplexMenuPage page_change(
   {
      Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_A}, "Around >", { "open_page:page_change_around" } ),
      Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_I}, "Inside >", { "open_page:page_change_inside" } ),
      Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_W}, "To next word", {
            "delete_to_next_word_or_end_of_line",
            "set_to_insert_mode",
         }),
   });

   Hexagon::MultiplexMenu::MultiplexMenuPage page_delete(
   {
      Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_A}, "Around >", { "open_page:page_delete_around" } ),
      Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_I}, "Inside >", { "open_page:page_delete_inside" } ),
      Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_W}, "To next word", { "delete_to_next_word_or_end_of_line" } ),
      Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_D}, "Line", { "delete_line" } ),
      Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_4, true}, "To end of line", { "delete_to_end_of_line" } ),
   });

   Hexagon::MultiplexMenu::MultiplexMenuPage page_delete_around(
   {
      Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_W}, "Word", { "delete_word_under_cursor" } ),
   });

   Hexagon::MultiplexMenu::MultiplexMenuPage page_delete_inside(
   {
      Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_W}, "Word", { "delete_word_under_cursor" } ),
   });

   Hexagon::MultiplexMenu::MultiplexMenuPage page_change_around(
   {
      Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_W}, "Word", {
            "delete_word_under_cursor",
            "set_to_insert_mode",
         }),
   });

   Hexagon::MultiplexMenu::MultiplexMenuPage page_change_inside(
   {
      Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_W}, "Word", {
            "delete_word_under_cursor",
            "set_to_insert_mode",
         }),
   });

   Hexagon::MultiplexMenu::MultiplexMenuPage page_goto(
   {
      Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_G}, "Top of file", {
            "cursor_move_to_start_of_file",
            "first_row_offset_adjust_so_cursor_is_vertically_centered",
         }),
   });

   std::map<std::string, Hexagon::MultiplexMenu::MultiplexMenuPage> dictionary =
   {
      { "start", start_page },

      { "page_delete", page_delete },
      { "page_delete_around", page_delete_around },
      { "page_delete_inside", page_delete_inside },

      { "page_change", page_change },
      { "page_change_around", page_change_around },
      { "page_change_inside", page_change_inside },

      { "page_goto", page_goto },
   };

   // TODO: validate menu commands are valid commands for the advanced_code_editor_stage

   Hexagon::MultiplexMenu::MultiplexMenu full_multiplex_menu(dictionary);
   return full_multiplex_menu;
}


} // namespace Hexagon


