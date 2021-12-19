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
      AllegroFlare::FontBin& fonts;
      std::string title_text;
      ALLEGRO_COLOR backfill_color;
      bool show_disabled_screen;
      bool render_powerbar;
      bool files_are_committed;
      bool commits_are_in_sync_with_remote;
      bool show_profiler;
      bool draw_save_count;
      int save_count;
      bool render_packets;
      std::vector<Hexagon::Packet> packets;
      bool draw_search_count;
      int search_count;
      bool render_focus_timer_bar;
      bool draw_notifications;
      float left_column_x;
      float surface_projection_width;
      float surface_projection_height;
      std::vector<StageInterface *>* stages;
      std::string global_font_str;

   public:
      Hud(ALLEGRO_DISPLAY* display=nullptr, AllegroFlare::FontBin& fonts=get_dummy_font_bin(), std::string title_text="", ALLEGRO_COLOR backfill_color={0.0f, 0.0f, 0.0f, 0.0f}, bool show_disabled_screen=false, bool render_powerbar=false, bool files_are_committed=false, bool commits_are_in_sync_with_remote=false, bool show_profiler=false, bool draw_save_count=false, int save_count=0, bool render_packets=false, std::vector<Hexagon::Packet> packets={}, bool draw_search_count=false, int search_count=0, bool render_focus_timer_bar=false, bool draw_notifications=true, float left_column_x=30);
      ~Hud();

      void set_screen_sub_bitmap(ALLEGRO_BITMAP* screen_sub_bitmap);
      void set_notifications(std::vector<std::string> notifications);
      void set_notifications2(std::vector<std::string> notifications2);
      void set_title_text(std::string title_text);
      void set_backfill_color(ALLEGRO_COLOR backfill_color);
      void set_show_disabled_screen(bool show_disabled_screen);
      void set_render_powerbar(bool render_powerbar);
      void set_files_are_committed(bool files_are_committed);
      void set_commits_are_in_sync_with_remote(bool commits_are_in_sync_with_remote);
      void set_show_profiler(bool show_profiler);
      void set_draw_save_count(bool draw_save_count);
      void set_save_count(int save_count);
      void set_render_packets(bool render_packets);
      void set_packets(std::vector<Hexagon::Packet> packets);
      void set_draw_search_count(bool draw_search_count);
      void set_search_count(int search_count);
      void set_render_focus_timer_bar(bool render_focus_timer_bar);
      void set_draw_notifications(bool draw_notifications);
      void set_left_column_x(float left_column_x);
      void set_surface_projection_width(float surface_projection_width);
      void set_surface_projection_height(float surface_projection_height);
      void set_stages(std::vector<StageInterface *>* stages);
      void set_global_font_str(std::string global_font_str);
      std::vector<std::string> get_notifications();
      std::vector<std::string> get_notifications2();
      std::string get_title_text();
      bool get_show_disabled_screen();
      bool get_render_powerbar();
      bool get_show_profiler();
      bool get_draw_save_count();
      int get_save_count();
      bool get_render_packets();
      std::vector<Hexagon::Packet> get_packets();
      bool get_draw_search_count();
      int get_search_count();
      bool get_render_focus_timer_bar();
      bool get_draw_notifications();
      float get_left_column_x();
      float get_surface_projection_width();
      float get_surface_projection_height();
      Hexagon::Powerbar::Powerbar &get_powerbar_ref();
      Hexagon::FocusTimerBar::FocusTimerBar &get_focus_timer_bar_ref();
      static AllegroFlare::FontBin& get_dummy_font_bin();
      ALLEGRO_FONT* obtain_text_font();
      ALLEGRO_FONT* obtain_title_font();
      ALLEGRO_FONT* obtain_powerbar_text_font();
      ALLEGRO_FONT* obtain_score_text_font();
      ALLEGRO_FONT* obtain_global_font();
      ALLEGRO_FONT* obtain_packet_text_font();
      ALLEGRO_FONT* obtain_component_navigator_font();
      void initialize();
      void reinitialize();
      void draw_current_title_text();
      void draw_profile_timer_graph();
      void draw_powerbar();
      void draw_focus_timer_bar();
      void draw_build_sequence_meter();
      void draw_packets();
      void draw();
      void set_orthographic_projection(ALLEGRO_BITMAP* bitmap=nullptr, float left=0, float top=0, float right=1920, float bottom=1080);
   };
}



