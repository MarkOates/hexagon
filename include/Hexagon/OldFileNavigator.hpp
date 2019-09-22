#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>


class OldFileSystemNode;


class OldFileNavigator : public StageInterface
{
private:
   OldFileSystemNode *current_node;
   int cursor_y;

public:
   OldFileNavigator(std::string directory);
   ~OldFileNavigator();

   void set_cursor_y(int cursor_y);
   OldFileSystemNode *infer_current_selection();
   std::string infer_current_selection_name();

   // actions

   bool move_cursor_y_delta(int delta);
   bool move_cursor_up();
   bool move_cursor_down();
   void process_local_event(std::string event_name, ActionData action_data1=ActionData()) override;
   void process_event(ALLEGRO_EVENT &event) override;
   bool save_file() override;
   void render(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, int cell_width, int cell_height) override;
};


