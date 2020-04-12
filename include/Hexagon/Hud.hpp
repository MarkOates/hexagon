#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
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
      ALLEGRO_DISPLAY* display;
      AllegroFlare::FontBin& fonts;
      std::string title_text;
      bool show_disabled_screen;
      bool show_powerbar;
      bool files_are_modified;
      bool files_are_committed;
      bool commits_are_in_sync_with_remote;

   public:
      Hud(ALLEGRO_DISPLAY* display=nullptr, AllegroFlare::FontBin& fonts=get_dummy_font_bin(), std::string title_text="", bool show_disabled_screen=false, bool show_powerbar=true, bool files_are_modified=false, bool files_are_committed=false, bool commits_are_in_sync_with_remote=false);
      ~Hud();

      void set_screen_sub_bitmap(ALLEGRO_BITMAP* screen_sub_bitmap);
      void set_notifications(std::vector<std::string> notifications);
      void set_notifications2(std::vector<std::string> notifications2);
      void set_title_text(std::string title_text);
      void set_show_disabled_screen(bool show_disabled_screen);
      void set_show_powerbar(bool show_powerbar);
      void set_files_are_modified(bool files_are_modified);
      void set_files_are_committed(bool files_are_committed);
      void set_commits_are_in_sync_with_remote(bool commits_are_in_sync_with_remote);

      std::vector<std::string> get_notifications();
      std::vector<std::string> get_notifications2();
      std::string get_title_text();
      bool get_show_disabled_screen();
      bool get_show_powerbar();
   static AllegroFlare::FontBin& get_dummy_font_bin();
   ALLEGRO_FONT* obtain_text_font();
   void initialize();
   void reinitialize();
   void draw_current_focus_name();
   void draw();
   };
}



