#pragma once


#include <AllegroFlare/Bin.hpp>
#include <Hexagon/CodeEditor/CachedLineRenderer.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <map>
#include <string>


namespace Hexagon
{
   namespace CodeEditor
   {
      class LineRenderBin : public AllegroFlare::Bin<std::string, ALLEGRO_BITMAP *>
      {
      private:
         ALLEGRO_FONT* font;
         Hexagon::CodeEditor::CachedLineRenderer render_cache;
         std::map<std::string, int> line_text_to_index_mapping;

      public:
         LineRenderBin(ALLEGRO_FONT* font=nullptr);
         ~LineRenderBin();


      ALLEGRO_BITMAP* load_data(std::string identifier="") override;
      void destroy_data(ALLEGRO_BITMAP* resource=nullptr) override;
      };
   }
}



