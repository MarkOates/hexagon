#pragma once


#include <Hexagon/AdvancedCodeEditor/Cursor.hpp>
#include <Hexagon/AdvancedCodeEditor/Selection.hpp>
#include <Hexagon/CodeMessagePoint.hpp>
#include <Hexagon/CodeRange.hpp>
#include <Hexagon/Elements/TextMesh.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace AdvancedCodeEditor
   {
      class Renderer
      {
      private:
         Hexagon::Elements::TextMesh* text_mesh;
         ALLEGRO_BITMAP* surface_render;
         Hexagon::AdvancedCodeEditor::Cursor* cursor;
         std::vector<Hexagon::AdvancedCodeEditor::Selection>* selections;
         Hexagon::AdvancedCodeEditor::Selection* search_regex_selections;
         std::vector<CodeRange>* visual_selections;
         std::vector<CodeRange>* full_line_visual_selections;
         std::vector<CodeMessagePoint>* code_message_points;
         std::vector<std::string>* lines;
         float width;
         float height;
         bool cursor_is_bar;
         float text_mesh_y_offset;
         int first_row_offset;
         bool show_line_numbers;
         ALLEGRO_FONT* font;
         bool content_is_modified;
         bool represents_symlink;
         bool cursor_is_in_valid_range;
         ALLEGRO_COLOR line_numbers_color;
         bool show_backfill;
         ALLEGRO_COLOR null_space_color;
         ALLEGRO_COLOR backfill_color;

      protected:


      public:
         Renderer(Hexagon::Elements::TextMesh* text_mesh=nullptr, ALLEGRO_BITMAP* surface_render=nullptr, Hexagon::AdvancedCodeEditor::Cursor* cursor=nullptr, std::vector<Hexagon::AdvancedCodeEditor::Selection>* selections=nullptr, Hexagon::AdvancedCodeEditor::Selection* search_regex_selections=nullptr, std::vector<CodeRange>* visual_selections=nullptr, std::vector<CodeRange>* full_line_visual_selections=nullptr, std::vector<CodeMessagePoint>* code_message_points=nullptr, std::vector<std::string>* lines=nullptr, float width=1, float height=1, bool cursor_is_bar=false, float text_mesh_y_offset=0.0f, int first_row_offset=0, bool show_line_numbers=false, ALLEGRO_FONT* font=nullptr, bool content_is_modified=false, bool represents_symlink=false, bool cursor_is_in_valid_range=true, bool show_backfill=true);
         ~Renderer();

         void set_show_line_numbers(bool show_line_numbers);
         void set_font(ALLEGRO_FONT* font);
         void set_content_is_modified(bool content_is_modified);
         void set_represents_symlink(bool represents_symlink);
         void set_cursor_is_in_valid_range(bool cursor_is_in_valid_range);
         void set_line_numbers_color(ALLEGRO_COLOR line_numbers_color);
         void set_show_backfill(bool show_backfill);
         void set_null_space_color(ALLEGRO_COLOR null_space_color);
         void set_backfill_color(ALLEGRO_COLOR backfill_color);
         ALLEGRO_COLOR get_line_numbers_color() const;
         ALLEGRO_COLOR get_null_space_color() const;
         ALLEGRO_COLOR get_backfill_color() const;
         void render();
         void render_backfill();
         void draw_represents_symlink_frames();
         bool draw_null_space_above_and_below();
         bool render_line_numbers();
         void render_word_highlight_under_cursor();
         void render_cursor();
         void draw_selections();
         void draw_visual_selections();
         void draw_full_line_visual_selections();
         void draw_search_regex_selections();
         void draw_code_message_points();
      };
   }
}



