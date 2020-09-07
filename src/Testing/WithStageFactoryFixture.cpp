

#include <Testing/WithStageFactoryFixture.hpp>



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


Hexagon::StageFactory &WithStageFactoryFixture::get_stage_factory_ref()
{
   return stage_factory;
}


void WithStageFactoryFixture::SetUp()
{
al_init();
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


