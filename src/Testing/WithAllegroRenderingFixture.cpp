

#include <Testing/WithAllegroRenderingFixture.hpp>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>


namespace Testing
{


WithAllegroRenderingFixture::WithAllegroRenderingFixture()
   : ::testing::Test()
   , display(nullptr)
   , font_bin({})
{
}


WithAllegroRenderingFixture::~WithAllegroRenderingFixture()
{
}


void WithAllegroRenderingFixture::SetUp()
{
ASSERT_EQ(false, al_is_system_installed());
ASSERT_EQ(true, al_init());
al_init_primitives_addon();
al_init_font_addon();
al_init_ttf_addon();

font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");

display = al_create_display(1280 * 2, 720 * 2);
al_clear_to_color(ALLEGRO_COLOR{0.05f, 0.05f, 0.05f, 0.05f});
return;

}

void WithAllegroRenderingFixture::TearDown()
{
font_bin.clear();
al_destroy_display(display);
al_shutdown_ttf_addon(); // this is required otherwise subsequent al_init_ttf_addon will not work
                         // this is a bug in Allegro
al_uninstall_system();
return;

}

ALLEGRO_FONT* WithAllegroRenderingFixture::get_any_font()
{
return font_bin.auto_get("consolas.ttf 32");

}
} // namespace Testing

