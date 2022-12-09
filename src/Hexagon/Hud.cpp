

#include <Hexagon/Hud.hpp>

#include <AllegroFlare/Color.hpp>
#include <Hexagon/AdvancedComponentNavigator/Stage.hpp>
#include <Hexagon/BuildSequenceMeter/Renderer.hpp>
#include <Hexagon/Camera.hpp>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <Hexagon/Elements/ColorKit.hpp>
#include <Hexagon/Elements/Pill.hpp>
#include <Hexagon/FocusTimerBar/Renderer.hpp>
#include <Hexagon/PacketRenderer.hpp>
#include <Hexagon/Powerbar/Powerbar.hpp>
#include <Hexagon/Powerbar/Renderer.hpp>
#include <Hexagon/StageCollectionHelper.hpp>
#include <Hexagon/shared_globals.hpp>
#include <algorithm>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro_flare/placement2d.h>
#include <allegro_flare/placement3d.h>
#include <allegro_flare/useful_php.h>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{


AllegroFlare::FontBin Hud::dummy_font_bin = {};


Hud::Hud(ALLEGRO_DISPLAY* display, AllegroFlare::FontBin& font_bin, std::string title_text, ALLEGRO_COLOR backfill_color, bool show_disabled_screen, bool show_powerbar, bool files_are_committed, bool commits_are_in_sync_with_remote, bool show_profiler, bool show_save_count, int save_count, bool show_packets, std::vector<Hexagon::Packet> packets, bool show_search_count, int search_count, bool show_focus_timer_bar, bool show_build_sequence_meter, bool show_notifications, float left_column_x, ALLEGRO_COLOR base_text_color, float base_text_opacity, std::string objective_text, bool show_objective, std::string domain_text, bool show_domain)
   : initialized(false)
   , screen_sub_bitmap(nullptr)
   , notifications({})
   , notifications2({})
   , powerbar({})
   , focus_timer_bar({})
   , display(display)
   , font_bin(font_bin)
   , title_text(title_text)
   , backfill_color(backfill_color)
   , show_disabled_screen(show_disabled_screen)
   , show_powerbar(show_powerbar)
   , files_are_committed(files_are_committed)
   , commits_are_in_sync_with_remote(commits_are_in_sync_with_remote)
   , show_profiler(show_profiler)
   , show_save_count(show_save_count)
   , save_count(save_count)
   , show_packets(show_packets)
   , packets(packets)
   , show_search_count(show_search_count)
   , search_count(search_count)
   , show_focus_timer_bar(show_focus_timer_bar)
   , show_build_sequence_meter(show_build_sequence_meter)
   , show_notifications(show_notifications)
   , left_column_x(left_column_x)
   , surface_projection_width(1920)
   , surface_projection_height(1080)
   , stages(nullptr)
   , global_font_str("unset-global_font_str")
   , current_component_is_symlinked_thus_has_different_title_color(false)
   , show_caps_lock_notification_light(false)
   , base_text_color(base_text_color)
   , base_text_opacity(base_text_opacity)
   , objective_text(objective_text)
   , show_objective(show_objective)
   , domain_text(domain_text)
   , show_domain(show_domain)
{
}


Hud::~Hud()
{
}


void Hud::set_screen_sub_bitmap(ALLEGRO_BITMAP* screen_sub_bitmap)
{
   this->screen_sub_bitmap = screen_sub_bitmap;
}


void Hud::set_notifications(std::vector<std::string> notifications)
{
   this->notifications = notifications;
}


void Hud::set_notifications2(std::vector<std::string> notifications2)
{
   this->notifications2 = notifications2;
}


void Hud::set_title_text(std::string title_text)
{
   this->title_text = title_text;
}


void Hud::set_backfill_color(ALLEGRO_COLOR backfill_color)
{
   this->backfill_color = backfill_color;
}


void Hud::set_show_disabled_screen(bool show_disabled_screen)
{
   this->show_disabled_screen = show_disabled_screen;
}


void Hud::set_show_powerbar(bool show_powerbar)
{
   this->show_powerbar = show_powerbar;
}


void Hud::set_files_are_committed(bool files_are_committed)
{
   this->files_are_committed = files_are_committed;
}


void Hud::set_commits_are_in_sync_with_remote(bool commits_are_in_sync_with_remote)
{
   this->commits_are_in_sync_with_remote = commits_are_in_sync_with_remote;
}


void Hud::set_show_profiler(bool show_profiler)
{
   this->show_profiler = show_profiler;
}


void Hud::set_show_save_count(bool show_save_count)
{
   this->show_save_count = show_save_count;
}


void Hud::set_save_count(int save_count)
{
   this->save_count = save_count;
}


void Hud::set_show_packets(bool show_packets)
{
   this->show_packets = show_packets;
}


void Hud::set_packets(std::vector<Hexagon::Packet> packets)
{
   this->packets = packets;
}


void Hud::set_show_search_count(bool show_search_count)
{
   this->show_search_count = show_search_count;
}


void Hud::set_search_count(int search_count)
{
   this->search_count = search_count;
}


void Hud::set_show_focus_timer_bar(bool show_focus_timer_bar)
{
   this->show_focus_timer_bar = show_focus_timer_bar;
}


void Hud::set_show_build_sequence_meter(bool show_build_sequence_meter)
{
   this->show_build_sequence_meter = show_build_sequence_meter;
}


void Hud::set_show_notifications(bool show_notifications)
{
   this->show_notifications = show_notifications;
}


void Hud::set_left_column_x(float left_column_x)
{
   this->left_column_x = left_column_x;
}


void Hud::set_surface_projection_width(float surface_projection_width)
{
   this->surface_projection_width = surface_projection_width;
}


void Hud::set_surface_projection_height(float surface_projection_height)
{
   this->surface_projection_height = surface_projection_height;
}


void Hud::set_stages(std::vector<StageInterface *>* stages)
{
   this->stages = stages;
}


void Hud::set_global_font_str(std::string global_font_str)
{
   this->global_font_str = global_font_str;
}


void Hud::set_current_component_is_symlinked_thus_has_different_title_color(bool current_component_is_symlinked_thus_has_different_title_color)
{
   this->current_component_is_symlinked_thus_has_different_title_color = current_component_is_symlinked_thus_has_different_title_color;
}


void Hud::set_show_caps_lock_notification_light(bool show_caps_lock_notification_light)
{
   this->show_caps_lock_notification_light = show_caps_lock_notification_light;
}


void Hud::set_base_text_color(ALLEGRO_COLOR base_text_color)
{
   this->base_text_color = base_text_color;
}


void Hud::set_base_text_opacity(float base_text_opacity)
{
   this->base_text_opacity = base_text_opacity;
}


void Hud::set_objective_text(std::string objective_text)
{
   this->objective_text = objective_text;
}


void Hud::set_show_objective(bool show_objective)
{
   this->show_objective = show_objective;
}


void Hud::set_domain_text(std::string domain_text)
{
   this->domain_text = domain_text;
}


void Hud::set_show_domain(bool show_domain)
{
   this->show_domain = show_domain;
}


std::vector<std::string> Hud::get_notifications() const
{
   return notifications;
}


std::vector<std::string> Hud::get_notifications2() const
{
   return notifications2;
}


std::string Hud::get_title_text() const
{
   return title_text;
}


bool Hud::get_show_disabled_screen() const
{
   return show_disabled_screen;
}


bool Hud::get_show_powerbar() const
{
   return show_powerbar;
}


bool Hud::get_show_profiler() const
{
   return show_profiler;
}


bool Hud::get_show_save_count() const
{
   return show_save_count;
}


int Hud::get_save_count() const
{
   return save_count;
}


bool Hud::get_show_packets() const
{
   return show_packets;
}


std::vector<Hexagon::Packet> Hud::get_packets() const
{
   return packets;
}


bool Hud::get_show_search_count() const
{
   return show_search_count;
}


int Hud::get_search_count() const
{
   return search_count;
}


bool Hud::get_show_focus_timer_bar() const
{
   return show_focus_timer_bar;
}


bool Hud::get_show_build_sequence_meter() const
{
   return show_build_sequence_meter;
}


bool Hud::get_show_notifications() const
{
   return show_notifications;
}


float Hud::get_left_column_x() const
{
   return left_column_x;
}


float Hud::get_surface_projection_width() const
{
   return surface_projection_width;
}


float Hud::get_surface_projection_height() const
{
   return surface_projection_height;
}


bool Hud::get_current_component_is_symlinked_thus_has_different_title_color() const
{
   return current_component_is_symlinked_thus_has_different_title_color;
}


bool Hud::get_show_caps_lock_notification_light() const
{
   return show_caps_lock_notification_light;
}


ALLEGRO_COLOR Hud::get_base_text_color() const
{
   return base_text_color;
}


float Hud::get_base_text_opacity() const
{
   return base_text_opacity;
}


std::string Hud::get_objective_text() const
{
   return objective_text;
}


bool Hud::get_show_objective() const
{
   return show_objective;
}


std::string Hud::get_domain_text() const
{
   return domain_text;
}


bool Hud::get_show_domain() const
{
   return show_domain;
}


Hexagon::Powerbar::Powerbar &Hud::get_powerbar_ref()
{
   return powerbar;
}


Hexagon::FocusTimerBar::FocusTimerBar &Hud::get_focus_timer_bar_ref()
{
   return focus_timer_bar;
}


void Hud::initialize()
{
   if (initialized) return;
   if (!display)
   {
      throw std::runtime_error("[Hud::initialize()] Cannot initialize Hud with a nullptr screen_sub_bitmap");
   }

   ALLEGRO_BITMAP *backbuffer = al_get_backbuffer(display);
   ALLEGRO_BITMAP *hud_screen_sub_bitmap = al_create_sub_bitmap(
      backbuffer,
      0,
      0,
      al_get_bitmap_width(backbuffer),
      al_get_bitmap_height(backbuffer)
      );
   set_screen_sub_bitmap(hud_screen_sub_bitmap);

   //float hwidth = 1920/2;
   //float hheight = 1080/2;
   //set_orthographic_projection(hud_screen_sub_bitmap, -hwidth, -hheight, hwidth, hheight);
   set_orthographic_projection(
      hud_screen_sub_bitmap,
      0,
      0,
      get_surface_projection_width(),
      get_surface_projection_height()
   );

   initialized = true;
   return;
}

void Hud::reinitialize()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Hud::reinitialize]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Hud::reinitialize: error: guard \"initialized\" not met");
   }
   if (!(display))
   {
      std::stringstream error_message;
      error_message << "[Hud::reinitialize]: error: guard \"display\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Hud::reinitialize: error: guard \"display\" not met");
   }
   if (!(screen_sub_bitmap))
   {
      std::stringstream error_message;
      error_message << "[Hud::reinitialize]: error: guard \"screen_sub_bitmap\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Hud::reinitialize: error: guard \"screen_sub_bitmap\" not met");
   }
   ALLEGRO_BITMAP *backbuffer = al_get_backbuffer(display);
   al_destroy_bitmap(screen_sub_bitmap);
   ALLEGRO_BITMAP *hud_screen_sub_bitmap = al_create_sub_bitmap(backbuffer,
                                                               0,
                                                               0,
                                                               al_get_bitmap_width(backbuffer),
                                                               al_get_bitmap_height(backbuffer));
   set_screen_sub_bitmap(hud_screen_sub_bitmap);

   initialized = true;
   return;
}

void Hud::draw_current_title_text()
{
   std::string title_text_filtered_with_domain_removed = title_text;
   if (title_text.find(domain_text) == 0) title_text_filtered_with_domain_removed = title_text.substr(domain_text.size());

   std::string &text = title_text_filtered_with_domain_removed;

   if (text.empty()) return;

   ALLEGRO_COLOR epic_green_color = al_color_html("99ddc4");
   ALLEGRO_COLOR color = AllegroFlare::color::mix(epic_green_color, al_color_name("dodgerblue"), 0.5);
   if (get_current_component_is_symlinked_thus_has_different_title_color())
   {
      ALLEGRO_COLOR is_symlink_mix_color = al_color_name("orange");
      color = AllegroFlare::color::mix(color, is_symlink_mix_color, 0.5);
   }
   float display_center_x = get_surface_projection_width() / 2;
   ALLEGRO_FONT *title_font = obtain_title_font();
   float title_font_line_height = al_get_font_line_height(title_font);
   float text_width = al_get_text_width(title_font, text.c_str());
   int y_position = 52 - title_font_line_height/2;

   al_draw_filled_rectangle(display_center_x - text_width/2 - 20,
      y_position - title_font_line_height/2 - 10,
      display_center_x + text_width/2 + 20,
      y_position + title_font_line_height/2 + 10,
      AllegroFlare::color::color(backfill_color, 0.9)
      //ALLEGRO_COLOR{0, 0, 0, 0.9}
   );

   al_draw_text(title_font,
                color,
                display_center_x,
                y_position - title_font_line_height/2,
                ALLEGRO_ALIGN_CENTER,
                text.c_str());
   return;
}

void Hud::draw_profile_timer_graph()
{
   global::profiler.draw(10, 10, obtain_text_font());
   return;
}

void Hud::draw_objective_text()
{
   Hexagon::Elements::ColorKit color_kit(backfill_color, base_text_color);
   float opacity = base_text_opacity;
   ALLEGRO_FONT *objective_text_font = obtain_objective_font();
   float x = surface_projection_width / 32 * 1;
   float y = 30;
   al_draw_text(objective_text_font,
                color_kit.get_base_text_color(base_text_opacity),
                x,
                y,
                ALLEGRO_ALIGN_LEFT,
                objective_text.c_str());
   return;
}

void Hud::draw_domain_text_and_overlay()
{
   Hexagon::Elements::ColorKit color_kit(backfill_color, base_text_color);
   float opacity = base_text_opacity;
   ALLEGRO_FONT *domain_text_font = obtain_domain_font();
   float x = surface_projection_width * 0.5;
   float y = 2;
   al_draw_text(domain_text_font,
                color_kit.get_base_text_color(base_text_opacity),
                x,
                y,
                ALLEGRO_ALIGN_CENTER,
                domain_text.c_str());
   return;
}

void Hud::draw_powerbar()
{
   powerbar.set_files_are_committed(files_are_committed);
   powerbar.set_commits_are_in_sync_with_remote(commits_are_in_sync_with_remote);
   // these values are set externally in System/System via actions
   //powerbar.set_files_are_modified(files_are_modified);
   //powerbar.set_files_are_staged(files_are_staged);
   //powerbar.set_files_are_untracked(files_are_untracked);

   Hexagon::Powerbar::Renderer powerbar_renderer(display, &powerbar, obtain_powerbar_text_font(), backfill_color);
   powerbar_renderer.render();
   return;
}

void Hud::draw_focus_timer_bar()
{
   Hexagon::FocusTimerBar::Renderer focus_timer_bar_renderer(
      &font_bin,
      get_surface_projection_width(),
      get_surface_projection_height(),
      &focus_timer_bar
   );
   focus_timer_bar_renderer.render();
   return;
}

void Hud::draw_build_sequence_meter()
{
   std::string BUILD_STATUS_SIGNALING_FILENAME =
      "/Users/markoates/Repos/hexagon/bin/programs/data/tmp/build_signal.txt";
   std::string build_sequence_status = php::file_get_contents(BUILD_STATUS_SIGNALING_FILENAME);
   if (!build_sequence_status.empty()) build_sequence_status.pop_back(); // remove the newline, ugh hack sorry
   // TODO consider (do, actually, not consider) migrating this to placement3d
   placement2d place{1920 - 40, 1080 / 2, 70, 620};
   place.align = vec2d(1.0, 0.5);

   std::vector<std::tuple<std::string, std::string, std::string, std::string>> build_stages = {
     { "started", "SGNL", "not_started", "" },
     { "generating_sources_files_from_quintessence", "PRSE", "not_started", "quintessence_build.txt" },
     { "building_dependency_file_for_component", "DEPS", "not_started", "" },
     { "building_component_object_files", "BUILD", "not_started", "component_object_build.txt" },
     { "delete_focused_component_test_object_file_and_test_executable", "XTOB", "not_started", "" },
     { "build_focused_component_test_object_file", "BTOB", "not_started", "component_test_object_build.txt" },
     { "build_focused_component_test_executable", "BTEX", "not_started", "component_test_executable.txt" },
     { "run_test_for_focused_component", "TEST", "not_started", "component_test_run.txt" },
     { "make_library", "LIBB", "not_started", "" },
     { "make_all_programs", "PROG", "not_started", "" },
     { "make_documentation", "DOCS", "not_started", "" },
     { "signal_component_built_and_integrated", "SIGF", "not_started", "" },
     { "completed", "PASS", "not_started", "" },
   };
   for (auto &build_stage : build_stages)
   {
      std::string this_stage_status = std::get<0>(build_stage);
      if (this_stage_status == build_sequence_status)
      {
         if (build_sequence_status == "completed") std::get<2>(build_stage) = "finished";
         else std::get<2>(build_stage) = "running";
      }
   }
   Hexagon::BuildSequenceMeter::Renderer build_sequence_meter_renderer(
      &font_bin,
      build_sequence_status,
      build_stages,
      place.size.x,
      place.size.y,
      backfill_color,
      base_text_color
   );

   place.start_transform();
   build_sequence_meter_renderer.render();
   place.restore_transform();

   return;
}

void Hud::draw_packets()
{
   int frame_height = get_surface_projection_height();

   float x = left_column_x - 5;
   float y = frame_height - 60;
   float width = 130;
   float height = 90;
   float spacing = 20;

   float y_increment = -(height + spacing);

   placement3d place(x, y, 0.0);
   place.size.x = width;
   place.size.y = height;
   place.align.x = 0.0;
   place.align.y = 1.0;
   place.scale.x = 0.75;
   place.scale.y = 0.75;
   ALLEGRO_FONT *packet_text_font = obtain_packet_text_font();

   ALLEGRO_COLOR packet_text_color = AllegroFlare::color::color(get_base_text_color(), base_text_opacity);

   al_draw_text(packet_text_font, packet_text_color, x, y, 0, "PACKETS");

   place.position.y -= al_get_font_line_height(packet_text_font);

   Hexagon::Packet packet_in_progress(search_count, save_count);
   std::vector<Hexagon::Packet> packets_to_render = packets;
   packets_to_render.push_back(packet_in_progress);

   // 9, because golf has 9-hole halves (of a game of 18 holes)
   // also it's divisible by 2 or 3. Good number.  Also 1 extra for the in-progress
   int max_num_packets_to_render = 10;

   while (packets_to_render.size() > max_num_packets_to_render) packets_to_render.erase(packets_to_render.begin());
   std::reverse(packets_to_render.begin(), packets_to_render.end());

   for (auto &packet : packets_to_render)
   {
      place.start_transform();

      Hexagon::PacketRenderer packet_renderer(
         &font_bin, &packet, packet_text_font, place.size.x, place.size.y, packet_text_color
      );
      packet_renderer.render();

      place.restore_transform();

      place.position.y += y_increment;
   }
   return;
}

void Hud::draw_caps_lock_notification_light(bool active)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Hud::draw_caps_lock_notification_light]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Hud::draw_caps_lock_notification_light: error: guard \"initialized\" not met");
   }
   float caps_notification_lights_x = 130;
   float caps_notification_lights_y = get_surface_projection_height() - 200;

   Hexagon::Elements::Pill pill(&font_bin, caps_notification_lights_x, caps_notification_lights_y);
   pill.render();
   //ALLEGRO_FONT *font = obtain_global_font();
   //ALLEGRO_COLOR color = ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2};
   //al_draw_text(font, color, 10, 10, ALLEGRO_ALIGN_CENTER, "CAPS");
   //TODO: fill out this drawing
   //ALLEGRO_KEY_SCROLLLOCK
   //ALLEGRO_KEY_NUMLOCK
   //ALLEGRO_KEY_CAPSLOCK
   return;
}

void Hud::draw()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Hud::draw]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Hud::draw: error: guard \"initialized\" not met");
   }
   int y_cursor = 0;
   int frame_width = get_surface_projection_width();
   int frame_height = get_surface_projection_height();

   ALLEGRO_STATE previous_target_bitmap_state;
   al_store_state(&previous_target_bitmap_state, ALLEGRO_STATE_TARGET_BITMAP);
   al_set_target_bitmap(screen_sub_bitmap);

   ALLEGRO_FONT *font = obtain_global_font();
   ALLEGRO_FONT *component_navigator_font = obtain_component_navigator_font();

   std::vector<StageInterface::type_t> permitted_types = {
      StageInterface::PROJECT_NAVIGATOR,
      StageInterface::COMPONENT_NAVIGATOR,
      StageInterface::COMPONENT_RELATIONS_NAVIGATOR,
      StageInterface::ONE_LINE_INPUT_BOX,
      StageInterface::GIT_COMMIT_MESSAGE_INPUT_BOX,
      StageInterface::FILE_NAVIGATOR,
      StageInterface::LITTLE_MENU,
      StageInterface::DRAWING_BOX,
      StageInterface::FANCY,
      StageInterface::MULTIPLEX_MENU,
   };

   // alternatively using a camera
   bool using_camera = false;
   if (using_camera)
   {
      Hexagon::Camera camera;
      vec3d &camera_position = camera.get_position_ref();
      vec3d &camera_stepback = camera.get_stepback_ref();
      vec3d &camera_rotation = camera.get_rotation_ref();
      camera_position.x = frame_width / 2; //al_get_display_width(display)/2;
      camera_position.y = frame_height / 2; //al_get_display_height(display)/2;
      camera_stepback.z = 0; //(sin(al_get_time()) * 100);
      camera.setup_camera_perspective(screen_sub_bitmap);
      al_clear_depth_buffer(1000);
   }

   bool draw_stages = true;

   Hexagon::StageCollectionHelper stage_collection_helper(stages);
   //for (auto &stage : stage_collection_helper.get_all_render_on_hud_stages())

   if (draw_stages && stages)
   {
      for (auto &stage : stage_collection_helper.get_all_render_on_hud_stages())
      //for (auto &stage : (*stages))
      {
         //if (!stage->get_render_on_hud()) continue;
         if (std::find(permitted_types.begin(), permitted_types.end(), stage->get_type()) == permitted_types.end())
         {
            std::stringstream error_message;
            error_message << "Hexagon/Hud::draw: error: Cannot render a stage marked as render_on_hud "
                          << "that is of type \"" << stage->get_type() << "\"";
            throw std::runtime_error(error_message.str());
         }

         stage->render();
      }
   }

   draw_current_title_text();

   if (show_objective) draw_objective_text();

   if (show_domain) draw_domain_text_and_overlay();

   if (show_profiler) draw_profile_timer_graph();

   if (show_notifications)
   {
      ALLEGRO_COLOR color = al_color_name("red");
      float notification_bottom_padding = al_get_font_line_height(obtain_text_font());
      float font_line_height = al_get_font_line_height(obtain_text_font());
      y_cursor=0;
      for (auto &notification : notifications)
      {
         float y_position = y_cursor * notification_bottom_padding;
         al_draw_text(obtain_text_font(), color, 0, y_position, 0, notification.c_str());
         y_cursor++;
      }

      y_cursor=0;
      for (auto &notification2 : notifications2)
      {
         float y_position = (y_cursor+1) * font_line_height;
         al_draw_text(obtain_text_font(),
                      color,
                      frame_width,
                      frame_height-y_position,
                      ALLEGRO_ALIGN_RIGHT,
                      notification2.c_str());
         y_cursor++;
      }
   }

   if (show_save_count)
   {
      // bottom left of screen
      std::string save_count_text_to_draw = std::string("Saves: ") + std::to_string(save_count);
      ALLEGRO_FONT *score_text_font = obtain_score_text_font();
      al_draw_text(
         score_text_font,
         al_color_name("gray"),
         left_column_x,
         frame_height - al_get_font_line_height(score_text_font) - 60,
         ALLEGRO_ALIGN_LEFT,
         save_count_text_to_draw.c_str()
      );
   }

   if (show_search_count)
   {
      // bottom left of screen
      std::string search_count_text_to_draw = std::string("Searches: ") + std::to_string(search_count);
      ALLEGRO_FONT *score_text_font = obtain_score_text_font();
      al_draw_text(
         score_text_font,
         al_color_name("gray"),
         left_column_x,
         frame_height - al_get_font_line_height(score_text_font) - 60 - 28,
         ALLEGRO_ALIGN_LEFT,
         search_count_text_to_draw.c_str()
      );
   }

   if (show_packets) draw_packets();

   if (show_powerbar) draw_powerbar();

   if (show_focus_timer_bar) draw_focus_timer_bar();

   if (show_caps_lock_notification_light) draw_caps_lock_notification_light();

   if (show_build_sequence_meter) draw_build_sequence_meter();

   if (show_disabled_screen)
   {
      al_draw_line(0,
                   0,
                   get_surface_projection_width(),
                   get_surface_projection_height(),
                   al_color_name("red"),
                   3.0);
   }

   al_restore_state(&previous_target_bitmap_state);
   return;
}

void Hud::set_orthographic_projection(ALLEGRO_BITMAP* bitmap, float left, float top, float right, float bottom)
{
   ALLEGRO_TRANSFORM trans;
   al_identity_transform(&trans);
   float h_depth = 200;

   bool using_ortho = true;
   if (using_ortho)
   {
      al_orthographic_transform(
            &trans,
            left,
            top,
            -1.0 * h_depth,
            right,
            bottom,
            1.0 * h_depth
         );
   }
   else
   {
      // NOTE: This doesn't work
      al_perspective_transform(
            &trans,
            left - 500,
            top - 500,
            -2000, //-1.0 * h_depth + 350,
            right + 500,
            bottom + 500,
            2000 //1.0 * h_depth + 350
         );
   }

   ALLEGRO_STATE previous_target_bitmap_state;
   al_store_state(&previous_target_bitmap_state, ALLEGRO_STATE_TARGET_BITMAP);

   al_set_target_bitmap(bitmap);
   al_use_projection_transform(&trans);

   al_restore_state(&previous_target_bitmap_state);
   return;
}

AllegroFlare::FontBin& Hud::get_dummy_font_bin()
{
   return dummy_font_bin;
}

ALLEGRO_FONT* Hud::obtain_text_font()
{
   return font_bin["Eurostile.ttf -27"];
   //return font_bin["EurostileExtendedBlack-aka-ExtendedBold.ttf -32"];
}

ALLEGRO_FONT* Hud::obtain_title_font()
{
   return font_bin["Purista Medium.otf -28"];
   //return font_bin["EurostileExtendedBlack-aka-ExtendedBold.ttf -32"];
}

ALLEGRO_FONT* Hud::obtain_objective_font()
{
   return font_bin["Purista Medium.otf -22"];
   //return font_bin["EurostileExtendedBlack-aka-ExtendedBold.ttf -32"];
}

ALLEGRO_FONT* Hud::obtain_domain_font()
{
   return font_bin["Purista Medium.otf -16"];
   //return font_bin["EurostileExtendedBlack-aka-ExtendedBold.ttf -32"];
}

ALLEGRO_FONT* Hud::obtain_powerbar_text_font()
{
   return font_bin["Purista Medium.otf -18"];
   //return font_bin["EurostileExtendedBlack-aka-ExtendedBold.ttf -32"];
}

ALLEGRO_FONT* Hud::obtain_score_text_font()
{
   return font_bin["Purista Medium.otf -22"];
   //return font_bin["Eurostile.ttf -22"];
   //return font_bin["EurostileExtendedBlack-aka-ExtendedBold.ttf -32"];
}

ALLEGRO_FONT* Hud::obtain_global_font()
{
   return font_bin[global_font_str];
   //return font_bin["EurostileExtendedBlack-aka-ExtendedBold.ttf -32"];
}

ALLEGRO_FONT* Hud::obtain_packet_text_font()
{
   return font_bin["Exan-Regular.ttf -14"];
}

ALLEGRO_FONT* Hud::obtain_component_navigator_font()
{
   return font_bin["Purista Medium.otf -22"];
   //return font_bin["EurostileExtendedBlack-aka-ExtendedBold.ttf -32"];
}


} // namespace Hexagon


