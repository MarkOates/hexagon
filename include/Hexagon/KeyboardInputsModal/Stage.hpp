#include <Hexagon/StageInterface.hpp>
#include <Blast/KeyboardCommandMapper.hpp>


namespace KeyboardInputsModal
{
   class Stage : public StageInterface
   {
   private:
      KeyboardCommandMapper *keyboard_command_mapper;

   public:
      Stage(KeyboardCommandMapper *keyboard_command_mapper);
      ~Stage();

      virtual void render(bool is_focused, ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, int cell_width, int cell_height) override;

      virtual void process_local_event(std::string event_name, ActionData action_data=ActionData()) override;
      virtual void process_event(ALLEGRO_EVENT &event) override;
   };
} // namespace KeyboardInputsModal


