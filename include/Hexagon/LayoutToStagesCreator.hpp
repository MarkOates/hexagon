#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/Layout.hpp>
#include <Hexagon/StageFactory.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro_color.h>
#include <allegro_flare/placement3d.h>
#include <string>
#include <vector>


namespace Hexagon
{
   class LayoutToStagesCreator
   {
   private:
      std::vector<StageInterface *>* stages;
      Hexagon::StageFactory* stage_factory;
      Hexagon::Layout* layout;
      AllegroFlare::FontBin* font_bin;
      int code_editor_height;
      int code_editor_width;
      ALLEGRO_COLOR text_color;
      ALLEGRO_COLOR backfill_color;

   public:
      LayoutToStagesCreator(std::vector<StageInterface *>* stages=nullptr, Hexagon::StageFactory* stage_factory=nullptr, Hexagon::Layout* layout={}, AllegroFlare::FontBin* font_bin=nullptr, int code_editor_height=1350, int code_editor_width=1215, ALLEGRO_COLOR text_color=ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f}, ALLEGRO_COLOR backfill_color=ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
      ~LayoutToStagesCreator();

      void set_stages(std::vector<StageInterface *>* stages);

      std::vector<StageInterface *>* get_stages();
      int get_code_editor_height();
      int get_code_editor_width();
   void create();
   bool place_and_load_code_editor(std::string filename="", std::string file_category="undefined_file_category", placement3d place={});
   };
}



