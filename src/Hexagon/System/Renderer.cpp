

#include <Hexagon/System/Renderer.hpp>

#include <Hexagon/AdvancedComponentNavigator/Stage.hpp>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <Hexagon/Elements/Window.hpp>
#include <Hexagon/FileNavigator/Stage.hpp>
#include <Hexagon/StageCollectionHelper.hpp>
#include <Hexagon/shared_globals.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace System
{


Renderer::Renderer(Hexagon::System::System* system, ALLEGRO_DISPLAY* display, ALLEGRO_COLOR* backfill_color, ALLEGRO_COLOR base_text_color)
   : system(system)
   , display(display)
   , backfill_color(backfill_color)
   , base_text_color(base_text_color)
{
}


Renderer::~Renderer()
{
}


ALLEGRO_COLOR* Renderer::get_backfill_color() const
{
   return backfill_color;
}


ALLEGRO_COLOR Renderer::get_base_text_color() const
{
   return base_text_color;
}


bool Renderer::render()
{
   if (!(system))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::System::Renderer::render]: error: guard \"system\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::System::Renderer::render]: error: guard \"system\" not met");
   }
   if (!(display))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::System::Renderer::render]: error: guard \"display\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::System::Renderer::render]: error: guard \"display\" not met");
   }
   if (!(backfill_color))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::System::Renderer::render]: error: guard \"backfill_color\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::System::Renderer::render]: error: guard \"backfill_color\" not met");
   }
   //al_clear_to_color(*get_backfill_color());

   system->get_camera_ref().setup_camera_perspective(al_get_backbuffer(display));
   al_clear_depth_buffer(1000);

   global::profiler.start("all stages");

   Hexagon::StageCollectionHelper stage_collection_helper(&system->get_stages_ref());

   for (auto &stage : stage_collection_helper.get_all_stages_not_rendered_on_hud())
   {
      std::stringstream profile_timer_element_label;
      profile_timer_element_label << "Stage [" << stage->get_type_name() << "]                    " << stage;
      global::profiler.start(profile_timer_element_label.str());

      bool infer_is_focused = (system->get_frontmost_stage() == stage);

      stage->render();

      if (infer_is_focused) // for now, we're just going to do this as an experiment in
                            // assessing focused state in the UI
      {
         draw_focused_frame(stage);
      }

      global::profiler.pause(profile_timer_element_label.str());
   }
   global::profiler.pause("all stages");

   system->get_hud_ref().draw();

   return true;
}

void Renderer::draw_focused_frame(StageInterface* stage)
{
   if (!(stage))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::System::Renderer::draw_focused_frame]: error: guard \"stage\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::System::Renderer::draw_focused_frame]: error: guard \"stage\" not met");
   }
   placement3d place = stage->get_place();
   Hexagon::Elements::Window window(place.size.x, place.size.y);
   ALLEGRO_COLOR btc = get_base_text_color();
   ALLEGRO_COLOR focus_frame_color = ALLEGRO_COLOR{btc.r*0.3f, btc.g*0.3f, btc.b*0.3f, btc.a*0.3f};

   //window.set_outer_line_color(ALLEGRO_COLOR{0.0f, 1.0f, 1.0f, 1.0f});
   window.set_outer_line_color(focus_frame_color); //ALLEGRO_COLOR{0.3f, 0.3f, 0.3f, 0.3f});
   window.set_outer_line_opacity(0.5);
   window.set_outer_line_thickness(4.0);

   place.start_transform();
   window.draw();
   place.restore_transform();

   return;
}


} // namespace System
} // namespace Hexagon


