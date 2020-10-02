

#include <Hexagon/Hud.hpp>
#include <stdexcept>
#include <sstream>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <AllegroFlare/Color.hpp>
#include <Hexagon/shared_globals.hpp>
#include <algorithm>
#include <allegro_flare/placement3d.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <Hexagon/Powerbar/Powerbar.hpp>
#include <Hexagon/Powerbar/Renderer.hpp>
#include <Hexagon/FocusTimerBar/Renderer.hpp>
#include <Hexagon/PacketRenderer.hpp>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <Hexagon/AdvancedComponentNavigator/Stage.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{


AllegroFlare::FontBin Hud::dummy_font_bin = {};


Hud::Hud(ALLEGRO_DISPLAY* display, AllegroFlare::FontBin& fonts, std::string title_text, ALLEGRO_COLOR backfill_color, bool show_disabled_screen, bool render_powerbar, bool files_are_committed, bool commits_are_in_sync_with_remote, bool show_profiler, bool draw_save_count, int save_count, bool render_packets, std::vector<Hexagon::Packet> packets, bool draw_search_count, int search_count, bool render_focus_timer_bar, bool draw_notifications, float left_column_x)
   : initialized(false)
   , screen_sub_bitmap(nullptr)
   , notifications({})
   , notifications2({})
   , powerbar({})
   , focus_timer_bar({})
   , display(display)
   , fonts(fonts)
   , title_text(title_text)
   , backfill_color(backfill_color)
   , show_disabled_screen(show_disabled_screen)
   , render_powerbar(render_powerbar)
   , files_are_committed(files_are_committed)
   , commits_are_in_sync_with_remote(commits_are_in_sync_with_remote)
   , show_profiler(show_profiler)
   , draw_save_count(draw_save_count)
   , save_count(save_count)
   , render_packets(render_packets)
   , packets(packets)
   , draw_search_count(draw_search_count)
   , search_count(search_count)
   , render_focus_timer_bar(render_focus_timer_bar)
   , draw_notifications(draw_notifications)
   , left_column_x(left_column_x)
   , stages(nullptr)
   , global_font_str("unset-global_font_str")
{
}


Hud::~Hud()
{
}


void Hud::set_screen_sub_bitmap(ALLEGRO_BITMAP* screen_sub_bitmap)
{
   this->screen_sub_bitmap = screen_sub_bitmap;
}


void Hud::set_notifications(std::vector<std::string> notifications)
{
   this->notifications = notifications;
}


void Hud::set_notifications2(std::vector<std::string> notifications2)
{
   this->notifications2 = notifications2;
}


void Hud::set_title_text(std::string title_text)
{
   this->title_text = title_text;
}


void Hud::set_backfill_color(ALLEGRO_COLOR backfill_color)
{
   this->backfill_color = backfill_color;
}


void Hud::set_show_disabled_screen(bool show_disabled_screen)
{
   this->show_disabled_screen = show_disabled_screen;
}


void Hud::set_render_powerbar(bool render_powerbar)
{
   this->render_powerbar = render_powerbar;
}


void Hud::set_files_are_committed(bool files_are_committed)
{
   this->files_are_committed = files_are_committed;
}


void Hud::set_commits_are_in_sync_with_remote(bool commits_are_in_sync_with_remote)
{
   this->commits_are_in_sync_with_remote = commits_are_in_sync_with_remote;
}


void Hud::set_show_profiler(bool show_profiler)
{
   this->show_profiler = show_profiler;
}


void Hud::set_draw_save_count(bool draw_save_count)
{
   this->draw_save_count = draw_save_count;
}


void Hud::set_save_count(int save_count)
{
   this->save_count = save_count;
}


void Hud::set_render_packets(bool render_packets)
{
   this->render_packets = render_packets;
}


void Hud::set_packets(std::vector<Hexagon::Packet> packets)
{
   this->packets = packets;
}


void Hud::set_draw_search_count(bool draw_search_count)
{
   this->draw_search_count = draw_search_count;
}


void Hud::set_search_count(int search_count)
{
   this->search_count = search_count;
}


void Hud::set_render_focus_timer_bar(bool render_focus_timer_bar)
{
   this->render_focus_timer_bar = render_focus_timer_bar;
}


void Hud::set_draw_notifications(bool draw_notifications)
{
   this->draw_notifications = draw_notifications;
}


void Hud::set_left_column_x(float left_column_x)
{
   this->left_column_x = left_column_x;
}


void Hud::set_stages(std::vector<StageInterface *>* stages)
{
   this->stages = stages;
}


void Hud::set_global_font_str(std::string global_font_str)
{
   this->global_font_str = global_font_str;
}


std::vector<std::string> Hud::get_notifications()
{
   return notifications;
}


std::vector<std::string> Hud::get_notifications2()
{
   return notifications2;
}


std::string Hud::get_title_text()
{
   return title_text;
}


bool Hud::get_show_disabled_screen()
{
   return show_disabled_screen;
}


bool Hud::get_render_powerbar()
{
   return render_powerbar;
}


bool Hud::get_show_profiler()
{
   return show_profiler;
}


bool Hud::get_draw_save_count()
{
   return draw_save_count;
}


int Hud::get_save_count()
{
   return save_count;
}


bool Hud::get_render_packets()
{
   return render_packets;
}


std::vector<Hexagon::Packet> Hud::get_packets()
{
   return packets;
}


bool Hud::get_draw_search_count()
{
   return draw_search_count;
}


int Hud::get_search_count()
{
   return search_count;
}


bool Hud::get_render_focus_timer_bar()
{
   return render_focus_timer_bar;
}


bool Hud::get_draw_notifications()
{
   return draw_notifications;
}


float Hud::get_left_column_x()
{
   return left_column_x;
}


Hexagon::Powerbar::Powerbar &Hud::get_powerbar_ref()
{
   return powerbar;
}


Hexagon::FocusTimerBar::FocusTimerBar &Hud::get_focus_timer_bar_ref()
{
   return focus_timer_bar;
}


AllegroFlare::FontBin& Hud::get_dummy_font_bin()
{
return dummy_font_bin;

}

ALLEGRO_FONT* Hud::obtain_text_font()
{
return fonts["Eurostile.ttf -27"];
//return fonts["EurostileExtendedBlack-aka-ExtendedBold.ttf -32"];

}

ALLEGRO_FONT* Hud::obtain_title_font()
{
return fonts["Purista Medium.otf -32"];
//return fonts["EurostileExtendedBlack-aka-ExtendedBold.ttf -32"];

}

ALLEGRO_FONT* Hud::obtain_powerbar_text_font()
{
return fonts["Purista Medium.otf -18"];
//return fonts["EurostileExtendedBlack-aka-ExtendedBold.ttf -32"];

}

ALLEGRO_FONT* Hud::obtain_score_text_font()
{
return fonts["Purista Medium.otf -22"];
//return fonts["Eurostile.ttf -22"];
//return fonts["EurostileExtendedBlack-aka-ExtendedBold.ttf -32"];

}

ALLEGRO_FONT* Hud::obtain_global_font()
{
return fonts[global_font_str];
//return fonts["EurostileExtendedBlack-aka-ExtendedBold.ttf -32"];

}

ALLEGRO_FONT* Hud::obtain_packet_text_font()
{
return fonts["Exan-Regular.ttf -14"];

}

ALLEGRO_FONT* Hud::obtain_component_navigator_font()
{
return fonts["Purista Medium.otf -22"];
//return fonts["EurostileExtendedBlack-aka-ExtendedBold.ttf -32"];

}

void Hud::initialize()
{
if (initialized) return;
if (!display)
{
   throw std::runtime_error("[Hud::initialize()] Cannot initialize Hud with a nullptr screen_sub_bitmap");
}

ALLEGRO_BITMAP *backbuffer = al_get_backbuffer(display);
ALLEGRO_BITMAP *hud_screen_sub_bitmap = al_create_sub_bitmap(
   backbuffer,
   0,
   0,
   al_get_bitmap_width(backbuffer),
   al_get_bitmap_height(backbuffer)
   );
set_screen_sub_bitmap(hud_screen_sub_bitmap);

initialized = true;
return;

}

void Hud::reinitialize()
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Hud" << "::" << "reinitialize" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(display))
   {
      std::stringstream error_message;
      error_message << "Hud" << "::" << "reinitialize" << ": error: " << "guard \"display\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(screen_sub_bitmap))
   {
      std::stringstream error_message;
      error_message << "Hud" << "::" << "reinitialize" << ": error: " << "guard \"screen_sub_bitmap\" not met";
      throw std::runtime_error(error_message.str());
   }
ALLEGRO_BITMAP *backbuffer = al_get_backbuffer(display);
al_destroy_bitmap(screen_sub_bitmap);
ALLEGRO_BITMAP *hud_screen_sub_bitmap = al_create_sub_bitmap(backbuffer,
                                                            0,
                                                            0,
                                                            al_get_bitmap_width(backbuffer),
                                                            al_get_bitmap_height(backbuffer));
set_screen_sub_bitmap(hud_screen_sub_bitmap);

initialized = true;
return;

}

void Hud::draw_current_title_text()
{
ALLEGRO_COLOR epic_green_color = al_color_html("99ddc4");
ALLEGRO_COLOR color = AllegroFlare::color::mix(epic_green_color, al_color_name("dodgerblue"), 0.5);
float display_center_x = al_get_display_width(display) / 2;
int y_position = 20;

al_draw_text(obtain_title_font(),
             color,
             display_center_x,
             y_position + 18,
             ALLEGRO_ALIGN_CENTER,
             title_text.c_str());
return;

}

void Hud::draw_profile_timer_graph()
{
global::profiler.draw(10, 10, obtain_text_font());
return;

}

void Hud::draw_powerbar()
{
powerbar.set_files_are_committed(files_are_committed);
powerbar.set_commits_are_in_sync_with_remote(commits_are_in_sync_with_remote);
// these values are set externally in System/System via actions
//powerbar.set_files_are_modified(files_are_modified);
//powerbar.set_files_are_staged(files_are_staged);
//powerbar.set_files_are_untracked(files_are_untracked);

Hexagon::Powerbar::Renderer powerbar_renderer(display, &powerbar, obtain_powerbar_text_font(), backfill_color);
powerbar_renderer.render();
return;

}

void Hud::draw_focus_timer_bar()
{
Hexagon::FocusTimerBar::Renderer focus_timer_bar_renderer(display, &focus_timer_bar);
focus_timer_bar_renderer.render();
return;

}

void Hud::draw_packets()
{
int frame_height = al_get_bitmap_height(screen_sub_bitmap);

float x = left_column_x - 5;
float y = frame_height - 60;
float width = 130;
float height = 90;
float spacing = 20;

float y_increment = -(height + spacing);

placement3d place(x, y, 0.0);
place.size.x = width;
place.size.y = height;
place.align.x = 0.0;
place.align.y = 1.0;
ALLEGRO_FONT *packet_text_font = obtain_packet_text_font();

al_draw_text(packet_text_font, ALLEGRO_COLOR{0.5, 0.5, 0.5, 0.5}, x, y, 0, "PACKETS");

place.position.y -= al_get_font_line_height(packet_text_font);

Hexagon::Packet packet_in_progress(search_count, save_count);
std::vector<Hexagon::Packet> packets_to_render = packets;
packets_to_render.push_back(packet_in_progress);

// 9, because golf has 9-hole halves, also divisible by 2 or 3. Good number.  Also 1 extra for the in-progress
int max_packets_to_render = 9;
int num_packets_to_render = std::min(max_packets_to_render, (int)(packets_to_render.size() - 1));

for (int i=num_packets_to_render; i>=0; i--)
{
   auto &packet = packets_to_render[i];
   place.start_transform();

   Hexagon::PacketRenderer packet_renderer(&packet, packet_text_font, place.size.x, place.size.y);
   packet_renderer.render();

   place.restore_transform();

   place.position.y += y_increment;
}
return;

}

void Hud::draw()
{
if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Hud" << "::" << "draw" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
int y_cursor = 0;
int frame_width = al_get_bitmap_width(screen_sub_bitmap);
int frame_height = al_get_bitmap_height(screen_sub_bitmap);

ALLEGRO_STATE previous_target_bitmap_state;
al_store_state(&previous_target_bitmap_state, ALLEGRO_STATE_TARGET_BITMAP);
al_set_target_bitmap(screen_sub_bitmap);

ALLEGRO_FONT *font = obtain_global_font();
ALLEGRO_FONT *component_navigator_font = obtain_component_navigator_font();

std::vector<StageInterface::type_t> permitted_types = {
   StageInterface::COMPONENT_NAVIGATOR,
   StageInterface::ONE_LINE_INPUT_BOX,
   StageInterface::GIT_COMMIT_MESSAGE_INPUT_BOX,
   StageInterface::FILE_NAVIGATOR,
};

bool draw_stages = true;
if (draw_stages && stages)
{
   for (auto &stage : (*stages))
   {
      if (!stage->get_render_on_hud()) continue;
      if (std::find(permitted_types.begin(), permitted_types.end(), stage->get_type()) == permitted_types.end())
      {
         std::stringstream error_message;
         error_message << "Hexagon/Hud::draw: error: Cannot render a stage marked as render_on_hud "
                       << "that is of type \"" << stage->get_type() << "\"";
         throw std::runtime_error(error_message.str());
      }

      stage->render();
   }
}

draw_current_title_text();

if (show_profiler) draw_profile_timer_graph();

if (draw_notifications)
{
   ALLEGRO_COLOR color = al_color_name("red");
   float notification_bottom_padding = al_get_font_line_height(obtain_text_font());
   float font_line_height = al_get_font_line_height(obtain_text_font());
   y_cursor=0;
   for (auto &notification : notifications)
   {
      float y_position = y_cursor * notification_bottom_padding;
      al_draw_text(obtain_text_font(), color, 0, y_position, 0, notification.c_str());
      y_cursor++;
   }

   y_cursor=0;
   for (auto &notification2 : notifications2)
   {
      float y_position = (y_cursor+1) * font_line_height;
      al_draw_text(obtain_text_font(),
                   color,
                   frame_width,
                   frame_height-y_position,
                   ALLEGRO_ALIGN_RIGHT,
                   notification2.c_str());
      y_cursor++;
   }
}

if (draw_save_count)
{
   // bottom left of screen
   std::string save_count_text_to_draw = std::string("Saves: ") + std::to_string(save_count);
   ALLEGRO_FONT *score_text_font = obtain_score_text_font();
   al_draw_text(
      score_text_font,
      al_color_name("gray"),
      left_column_x,
      frame_height - al_get_font_line_height(score_text_font) - 60,
      ALLEGRO_ALIGN_LEFT,
      save_count_text_to_draw.c_str()
   );
}

if (draw_search_count)
{
   // bottom left of screen
   std::string search_count_text_to_draw = std::string("Searches: ") + std::to_string(search_count);
   ALLEGRO_FONT *score_text_font = obtain_score_text_font();
   al_draw_text(
      score_text_font,
      al_color_name("gray"),
      left_column_x,
      frame_height - al_get_font_line_height(score_text_font) - 60 - 28,
      ALLEGRO_ALIGN_LEFT,
      search_count_text_to_draw.c_str()
   );
}

if (render_packets) draw_packets();

if (render_powerbar) draw_powerbar();

if (render_focus_timer_bar) draw_focus_timer_bar();

if (show_disabled_screen)
{
   al_draw_line(0,
                0,
                al_get_display_width(display),
                al_get_display_height(display),
                al_color_name("red"),
                3.0);
}

al_restore_state(&previous_target_bitmap_state);
return;

}
} // namespace Hexagon


