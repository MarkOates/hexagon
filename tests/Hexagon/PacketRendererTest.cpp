
#include <gtest/gtest.h>

#include <Hexagon/PacketRenderer.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

TEST(Hexagon_PacketRendererTest, can_be_created_without_blowing_up)
{
   Hexagon::PacketRenderer packet_renderer;
}

TEST(Hexagon_PacketRendererTest, render__will_render_the_packet)
{
   al_init();
   al_init_primitives_addon();
   ALLEGRO_BITMAP *render_surface = al_create_bitmap(800, 400);
   al_set_target_bitmap(render_surface);

   Hexagon::Packet packet;

   Hexagon::PacketRenderer packet_renderer(&packet);
   packet_renderer.render();

   al_uninstall_system();

   SUCCEED();
}

