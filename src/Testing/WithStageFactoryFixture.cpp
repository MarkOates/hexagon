

#include <Testing/WithStageFactoryFixture.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


namespace Testing
{


WithStageFactoryFixture::WithStageFactoryFixture()
   : ::testing::Test()
   , config("/Users/markoates/Repos/hexagon/tests/fixtures/hexagon.test.cfg")
   , font_bin({})
   , stage_factory(&config, &font_bin)
{
}


WithStageFactoryFixture::~WithStageFactoryFixture()
{
}


AllegroFlare::FontBin &WithStageFactoryFixture::get_font_bin_ref()
{
   return font_bin;
}


Hexagon::StageFactory &WithStageFactoryFixture::get_stage_factory_ref()
{
   return stage_factory;
}


void WithStageFactoryFixture::SetUp()
{
   al_init();
   al_init_font_addon();
   al_init_ttf_addon();

   config.initialize();
   font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");
   return;
}

void WithStageFactoryFixture::TearDown()
{
   font_bin.clear();
   al_shutdown_ttf_addon();
   al_uninstall_system();
   return;
}


} // namespace Testing


