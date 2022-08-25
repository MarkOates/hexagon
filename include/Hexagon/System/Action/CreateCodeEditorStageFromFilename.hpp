#pragma once


#include <Hexagon/Action.hpp>
#include <Hexagon/StageFactory.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro_color.h>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace System
   {
      namespace Action
      {
         class CreateCodeEditorStageFromFilename : public ::Action
         {
         private:
            std::string filename;
            int display_default_width;
            int display_default_height;
            int stage_width;
            int stage_height;
            ALLEGRO_COLOR text_color;
            ALLEGRO_COLOR backfill_color;
            std::vector<StageInterface *>* stages;
            Hexagon::StageFactory* stage_factory;

         public:
            CreateCodeEditorStageFromFilename(std::string filename="file.txt", int display_default_width=1, int display_default_height=1, int stage_width=1, int stage_height=1, ALLEGRO_COLOR text_color=ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f}, ALLEGRO_COLOR backfill_color=ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f}, std::vector<StageInterface *>* stages=nullptr, Hexagon::StageFactory* stage_factory=nullptr);
            ~CreateCodeEditorStageFromFilename();

            int get_display_default_width() const;
            int get_display_default_height() const;
            int get_stage_width() const;
            int get_stage_height() const;
            bool execute();
         };
      }
   }
}



