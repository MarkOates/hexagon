#include <Hexagon/StageInterface.hpp>
#include <AllegroFlare/KeyboardCommandMapper.hpp>


namespace KeyboardInputsModal
{
   class Stage : public StageInterface
   {
   private:
      AllegroFlare::KeyboardCommandMapper *keyboard_command_mapper;

   public:
      Stage(AllegroFlare::KeyboardCommandMapper *keyboard_command_mapper);
      ~Stage();

      virtual void render() override;
      virtual void process_local_event(std::string event_name, ActionData action_data=ActionData()) override;
      virtual void process_event(ALLEGRO_EVENT &event) override;
   };
} // namespace KeyboardInputsModal


