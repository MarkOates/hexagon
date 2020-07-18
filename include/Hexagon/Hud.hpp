#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/FocusTimerBar/FocusTimerBar.hpp>
#include <Hexagon/Packet.hpp>
#include <Hexagon/Powerbar/Powerbar.hpp>
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
      bool draw_powerbar;
      bool files_are_modified;
      bool files_are_committed;
      bool commits_are_in_sync_with_remote;
      bool show_profiler;
      bool draw_save_count;
      int save_count;
      bool draw_packets;
      std::vector<Hexagon::Packet> packets;
      bool draw_search_count;
      int search_count;
      bool draw_focus_timer_bar;
      bool draw_notifications;

   public:
      Hud(ALLEGRO_DISPLAY* display=nullptr, AllegroFlare::FontBin& fonts=get_dummy_font_bin(), std::string title_text="", ALLEGRO_COLOR backfill_color={0.0f, 0.0f, 0.0f, 0.0f}, bool show_disabled_screen=false, bool draw_powerbar=false, bool files_are_modified=false, bool files_are_committed=false, bool commits_are_in_sync_with_remote=false, bool show_profiler=false, bool draw_save_count=true, int save_count=0, bool draw_packets=true, std::vector<Hexagon::Packet> packets={}, bool draw_search_count=true, int search_count=0, bool draw_focus_timer_bar=true, bool draw_notifications=true);
      ~Hud();

      void set_screen_sub_bitmap(ALLEGRO_BITMAP* screen_sub_bitmap);
      void set_notifications(std::vector<std::string> notifications);
      void set_notifications2(std::vector<std::string> notifications2);
      void set_title_text(std::string title_text);
      void set_backfill_color(ALLEGRO_COLOR backfill_color);
      void set_show_disabled_screen(bool show_disabled_screen);
      void set_draw_powerbar(bool draw_powerbar);
      void set_files_are_modified(bool files_are_modified);
      void set_files_are_committed(bool files_are_committed);
      void set_commits_are_in_sync_with_remote(bool commits_are_in_sync_with_remote);
      void set_show_profiler(bool show_profiler);
      void set_draw_save_count(bool draw_save_count);
      void set_save_count(int save_count);
      void set_draw_packets(bool draw_packets);
      void set_packets(std::vector<Hexagon::Packet> packets);
      void set_draw_search_count(bool draw_search_count);
      void set_search_count(int search_count);
      void set_draw_focus_timer_bar(bool draw_focus_timer_bar);
      void set_draw_notifications(bool draw_notifications);

      std::vector<std::string> get_notifications();
      std::vector<std::string> get_notifications2();
      std::string get_title_text();
      bool get_show_disabled_screen();
      bool get_draw_powerbar();
      bool get_show_profiler();
      bool get_draw_save_count();
      int get_save_count();
      bool get_draw_packets();
      std::vector<Hexagon::Packet> get_packets();
      bool get_draw_search_count();
      int get_search_count();
      bool get_draw_focus_timer_bar();
      bool get_draw_notifications();
      Hexagon::Powerbar::Powerbar &get_powerbar_ref();
      Hexagon::FocusTimerBar::FocusTimerBar &get_focus_timer_bar_ref();
   static AllegroFlare::FontBin& get_dummy_font_bin();
   ALLEGRO_FONT* obtain_text_font();
   ALLEGRO_FONT* obtain_powerbar_text_font();
   ALLEGRO_FONT* obtain_score_text_font();
   ALLEGRO_FONT* obtain_packet_text_font();
   void initialize();
   void reinitialize();
   void draw_current_focus_name();
   void draw_profile_timer_graph();
   void draw();
   };
}



