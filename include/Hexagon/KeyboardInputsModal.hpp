#include <Hexagon/StageInterface.hpp>
#include <Blast/KeyboardCommandMapper.hpp>


class KeyboardInputsModal : public StageInterface
{
private:
   KeyboardCommandMapper *keyboard_command_mapper;

public:
   KeyboardInputsModal(KeyboardCommandMapper *keyboard_command_mapper);
   ~KeyboardInputsModal();

   virtual void render(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, int cell_width, int cell_height) override;

   virtual void process_local_event(std::string event_name, ActionData action_data=ActionData()) override;
   virtual void process_event(ALLEGRO_EVENT &event) override;
   virtual bool save_file() override;
};

