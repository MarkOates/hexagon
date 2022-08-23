#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/FocusTimerBar/FocusTimerBar.hpp>
#include <Hexagon/Packet.hpp>
#include <Hexagon/Powerbar/Powerbar.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <vector>


namespace Hexagon
{
   class Hud
   {
   private:
      bool initialized;
      static AllegroFlare::FontBin dummy_font_bin;
      ALLEGRO_BITMAP* screen_sub_bitmap;
      std::vector<std::string> notifications;
      std::vector<std::string> notifications2;
      Hexagon::Powerbar::Powerbar powerbar;
      Hexagon::FocusTimerBar::FocusTimerBar focus_timer_bar;
      ALLEGRO_DISPLAY* display;
      AllegroFlare::FontBin& font_bin;
      std::string title_text;
      ALLEGRO_COLOR backfill_color;
      bool show_disabled_screen;
      bool show_powerbar;
      bool files_are_committed;
      bool commits_are_in_sync_with_remote;
      bool show_profiler;
      bool show_save_count;
      int save_count;
      bool show_packets;
      std::vector<Hexagon::Packet> packets;
      bool show_search_count;
      int search_count;
      bool show_focus_timer_bar;
      bool show_build_sequence_meter;
      bool show_notifications;
      float left_column_x;
      float surface_projection_width;
      float surface_projection_height;
      std::vector<StageInterface *>* stages;
      std::string global_font_str;
      bool current_component_is_symlinked_thus_has_different_title_color;
      bool show_caps_lock_notification_light;
      ALLEGRO_COLOR base_text_color;
      float base_text_opacity;
      std::string objective_text;
      bool show_objective;
      std::string domain_text;
      bool show_domain;

   public:
      Hud(ALLEGRO_DISPLAY* display=nullptr, AllegroFlare::FontBin& font_bin=get_dummy_font_bin(), std::string title_text="", ALLEGRO_COLOR backfill_color={0.0f, 0.0f, 0.0f, 0.0f}, bool show_disabled_screen=false, bool show_powerbar=false, bool files_are_committed=false, bool commits_are_in_sync_with_remote=false, bool show_profiler=false, bool show_save_count=false, int save_count=0, bool show_packets=false, std::vector<Hexagon::Packet> packets={}, bool show_search_count=false, int search_count=0, bool show_focus_timer_bar=false, bool show_build_sequence_meter=false, bool show_notifications=true, float left_column_x=30, ALLEGRO_COLOR base_text_color=ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0}, float base_text_opacity=0.5f, std::string objective_text="", bool show_objective=true, std::string domain_text="", bool show_domain=true);
      ~Hud();

      void set_screen_sub_bitmap(ALLEGRO_BITMAP* screen_sub_bitmap);
      void set_notifications(std::vector<std::string> notifications);
      void set_notifications2(std::vector<std::string> notifications2);
      void set_title_text(std::string title_text);
      void set_backfill_color(ALLEGRO_COLOR backfill_color);
      void set_show_disabled_screen(bool show_disabled_screen);
      void set_show_powerbar(bool show_powerbar);
      void set_files_are_committed(bool files_are_committed);
      void set_commits_are_in_sync_with_remote(bool commits_are_in_sync_with_remote);
      void set_show_profiler(bool show_profiler);
      void set_show_save_count(bool show_save_count);
      void set_save_count(int save_count);
      void set_show_packets(bool show_packets);
      void set_packets(std::vector<Hexagon::Packet> packets);
      void set_show_search_count(bool show_search_count);
      void set_search_count(int search_count);
      void set_show_focus_timer_bar(bool show_focus_timer_bar);
      void set_show_build_sequence_meter(bool show_build_sequence_meter);
      void set_show_notifications(bool show_notifications);
      void set_left_column_x(float left_column_x);
      void set_surface_projection_width(float surface_projection_width);
      void set_surface_projection_height(float surface_projection_height);
      void set_stages(std::vector<StageInterface *>* stages);
      void set_global_font_str(std::string global_font_str);
      void set_current_component_is_symlinked_thus_has_different_title_color(bool current_component_is_symlinked_thus_has_different_title_color);
      void set_show_caps_lock_notification_light(bool show_caps_lock_notification_light);
      void set_base_text_color(ALLEGRO_COLOR base_text_color);
      void set_base_text_opacity(float base_text_opacity);
      void set_objective_text(std::string objective_text);
      void set_show_objective(bool show_objective);
      void set_domain_text(std::string domain_text);
      void set_show_domain(bool show_domain);
      std::vector<std::string> get_notifications();
      std::vector<std::string> get_notifications2();
      std::string get_title_text();
      bool get_show_disabled_screen();
      bool get_show_powerbar();
      bool get_show_profiler();
      bool get_show_save_count();
      int get_save_count();
      bool get_show_packets();
      std::vector<Hexagon::Packet> get_packets();
      bool get_show_search_count();
      int get_search_count();
      bool get_show_focus_timer_bar();
      bool get_show_build_sequence_meter();
      bool get_show_notifications();
      float get_left_column_x();
      float get_surface_projection_width();
      float get_surface_projection_height();
      bool get_current_component_is_symlinked_thus_has_different_title_color();
      bool get_show_caps_lock_notification_light();
      ALLEGRO_COLOR get_base_text_color();
      float get_base_text_opacity();
      std::string get_objective_text();
      bool get_show_objective();
      std::string get_domain_text();
      bool get_show_domain();
      Hexagon::Powerbar::Powerbar &get_powerbar_ref();
      Hexagon::FocusTimerBar::FocusTimerBar &get_focus_timer_bar_ref();
      void initialize();
      void reinitialize();
      void draw_current_title_text();
      void draw_profile_timer_graph();
      void draw_objective_text();
      void draw_domain_text_and_overlay();
      void draw_powerbar();
      void draw_focus_timer_bar();
      void draw_build_sequence_meter();
      void draw_packets();
      void draw_caps_lock_notification_light(bool active=false);
      void draw();
      void set_orthographic_projection(ALLEGRO_BITMAP* bitmap=nullptr, float left=0, float top=0, float right=1920, float bottom=1080);
      static AllegroFlare::FontBin& get_dummy_font_bin();
      ALLEGRO_FONT* obtain_text_font();
      ALLEGRO_FONT* obtain_title_font();
      ALLEGRO_FONT* obtain_objective_font();
      ALLEGRO_FONT* obtain_domain_font();
      ALLEGRO_FONT* obtain_powerbar_text_font();
      ALLEGRO_FONT* obtain_score_text_font();
      ALLEGRO_FONT* obtain_global_font();
      ALLEGRO_FONT* obtain_packet_text_font();
      ALLEGRO_FONT* obtain_component_navigator_font();
   };
}



