#include <Hexagon/OldFileNavigator.hpp>

#include <Hexagon/shared_globals.hpp>

#include <Hexagon/OldFileSystemNode.hpp>
#include <Hexagon/OldFileNavigatorEventController.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>


OldFileNavigator::OldFileNavigator(std::string directory)
   //: file_system_entries()
   : StageInterface(StageInterface::OLD_FILE_NAVIGATOR)
   , current_node(new OldFileSystemNode(al_create_fs_entry(directory.c_str())))
   //, visible_and_active(false)
   , cursor_y(0)
   //, place(0, 0, 0)
{
   placement3d &p = get_place();

   //current_node = current_directory_fs_entry = al_create_fs_entry(al_get_current_directory());
   current_node->create_children();
   p.scale = vec3d(0.8, 0.8, 0.8);
   p.size = vec3d(500, 600, 0);
   p.align = vec3d(0.5, 0.5, 0.0);
   p.rotation = vec3d(0, 0.02, 0);
}

OldFileNavigator::~OldFileNavigator() {}

// property accessors

void OldFileNavigator::set_cursor_y(int cursor_y) { this->cursor_y = cursor_y; }
//void set_file_system_entries(std::vector<OldFileSystemNode *> file_system_entries)   {      this->file_system_entries = file_system_entries;   }
//bool get_visible_and_active() { return visible_and_active; }

// initializers

//bool set_

// inferences

OldFileSystemNode *OldFileNavigator::infer_current_selection()
{
   if (!current_node) return nullptr;
   if (cursor_y < 0 || cursor_y >= current_node->infer_num_children()) return nullptr;
   return current_node->get_children_ref()[cursor_y];
}

std::string OldFileNavigator::infer_current_selection_name()
{
   OldFileSystemNode *node = infer_current_selection();
   if (!node) return "";
   return node->infer_full_name();
}

// actions

bool OldFileNavigator::move_cursor_y_delta(int delta)
{
   set_cursor_y(cursor_y + delta);
   if (cursor_y < 0) set_cursor_y(0);
   if (cursor_y >= current_node->infer_num_children()) set_cursor_y(current_node->infer_num_children()-1);
   return true;
}

bool OldFileNavigator::move_cursor_up()
{
   return move_cursor_y_delta(-1);
}

bool OldFileNavigator::move_cursor_down()
{
   return move_cursor_y_delta(1);
}

//bool show()
//{
   //visible_and_active = true;
   //return true;
//}

//bool hide()
//{
   //visible_and_active = false;
   //return true;
//}

//static const std::string SHOW;
//static const std::string HIDE;

void OldFileNavigator::process_local_event(std::string event_name, ActionData action_data1)
{
   OldFileNavigatorEventController file_navigator_event_controller(this);
   file_navigator_event_controller.process_local_event(event_name, action_data1);
}

void OldFileNavigator::process_event(ALLEGRO_EVENT &event)
{
   OldFileNavigatorEventController file_navigator_event_controller(this);
   file_navigator_event_controller.process_event(event);
}

bool OldFileNavigator::save_file()
{
   FILE_NAVIGATOR_SELECTION_last_content = infer_current_selection_name();
   //std::cout << "  -- current inferred selection: " << infer_current_selection_name() << std::endl;
   //std::cout << "  -- filename for saving: " << FILE_NAVIGATOR_SELECTION_FILENAME << std::endl;
   //std::vector<std::string> lines = { infer_current_selection_name() };
   //if (!::save_file(lines, FILE_NAVIGATOR_SELECTION_FILENAME)) throw std::runtime_error("OldFileNavigator::save_file(): an error occurred");
   //else std::cout << "  -- Save file appears to have saved as expected" << std::endl;
   return true;
}

// void renderers

//placement3d place;

void OldFileNavigator::render(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, int cell_width, int cell_height)
//void render(placement2d place, ALLEGRO_FONT *font) override
{
   //placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0.0);
   //place.size = vec3d(al_get_display_width(display)/3, al_get_display_height(display)/3*2, 0.0);
   //place.scale = vec3d(0.6, 0.6, 1.0);

   //if (!visible_and_active) return;


   placement3d &place = get_place();
   get_place().start_transform();

   float roundness = 6.0;
   float padding_x = cell_width*2;
   float padding_y = cell_width;
   //std::cout << " size: " << place.size.x << ", " << place.size.y << std::endl;
   al_draw_filled_rounded_rectangle(0, 0, place.size.x, place.size.y, roundness, roundness, al_color_name("black"));
   al_draw_rounded_rectangle(0, 0, place.size.x, place.size.y, roundness, roundness, al_color_name("green"), 3.0);

   int line_height = al_get_font_line_height(font);
   int line_count = 0;
   ALLEGRO_COLOR text_color;

   // draw the current node name
   //std::string current_node_label = current_node->infer_is_directory()
   al_draw_text(font, al_color_name("aliceblue"), 0, line_height * -1, ALLEGRO_ALIGN_LEFT, current_node->infer_full_name().c_str());

   // draw the children of the current node
   for (auto &file_system_entry : current_node->get_children_ref())
   {
      bool is_directory = file_system_entry->infer_is_directory();

      std::string current_node_label = is_directory ? file_system_entry->infer_basename() : file_system_entry->infer_basename();

      float y = line_height * line_count;

      if (line_count == cursor_y)
      {
         //text_color = al_color_name("black");
         al_draw_filled_rectangle(0, padding_y+y, place.size.x, padding_y+y+line_height, al_color_name("green"));
         al_draw_filled_rectangle(0, padding_y+y, cell_width, padding_y+y+line_height, al_color_name("lime"));
         //al_draw_filled_rectangle(0, padding_y+y, cell_width, padding_y+y+line_height, al_color_name("lime"));
      }
      //else
      //{
         text_color = is_directory ? al_color_name("lime") : al_color_name("aquamarine");
      //}
      al_draw_text(font, text_color, padding_x+0, padding_y+line_height * line_count, ALLEGRO_ALIGN_LEFT, current_node_label.c_str());
      line_count++;
   }

   place.restore_transform();
}
