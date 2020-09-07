

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


void WithStageFactoryFixture::SetUp()
{
return;

}

void WithStageFactoryFixture::TearDown()
{
return;

}
} // namespace Testing


