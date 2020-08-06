#pragma once


#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro_color.h>
#include <allegro_flare/placement3d.h>
#include <string>
#include <vector>


namespace Hexagon
{
   class Layout
   {
   private:
      std::string concept_name;
      std::vector<StageInterface *>* stages;
      std::vector<std::tuple<std::string, std::string, placement3d>> files;
      std::string daemus_command;
      int code_editor_height;
      int code_editor_width;
      ALLEGRO_COLOR text_color;
      ALLEGRO_COLOR backfill_color;

   public:
      Layout(std::string concept_name="- Untitled -", std::vector<StageInterface *>* stages=nullptr, std::vector<std::tuple<std::string, std::string, placement3d>> files={}, std::string daemus_command="", int code_editor_height=1350, int code_editor_width=1215, ALLEGRO_COLOR text_color=ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f}, ALLEGRO_COLOR backfill_color=ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
      ~Layout();

      void set_concept_name(std::string concept_name);
      void set_stages(std::vector<StageInterface *>* stages);
      void set_files(std::vector<std::tuple<std::string, std::string, placement3d>> files);

      std::string get_concept_name();
      std::vector<StageInterface *>* get_stages();
      std::vector<std::tuple<std::string, std::string, placement3d>> get_files();
      std::string get_daemus_command();
      int get_code_editor_height();
      int get_code_editor_width();
   bool place_and_load_code_editor(std::string filename="", std::string file_category="undefined_file_category", placement3d place={});
   void create();
   };
}



