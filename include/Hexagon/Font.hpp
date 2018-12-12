#pragma once



#include <allegro5/allegro_font.h>
#include <string>



class Font
{
private:
   int font_size;
   std::string font_filename;
   ALLEGRO_FONT *font;

   static void __destroy(Font *font);
   static void __create(Font *font);

public:
   Font(int font_size, std::string font_filename);
   ~Font();

   void set_font_size(int font_size);
   int get_font_size();
   void set_font_filename(std::string font_filename);
   std::string get_font_filename();
};



