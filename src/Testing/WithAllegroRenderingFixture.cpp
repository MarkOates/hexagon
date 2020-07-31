

#include <Testing/WithAllegroRenderingFixture.hpp>



namespace Testing
{


WithAllegroRenderingFixture::WithAllegroRenderingFixture()
   : ::testing::Test()
{
}


WithAllegroRenderingFixture::~WithAllegroRenderingFixture()
{
}


std::string WithAllegroRenderingFixture::run()
{
return "Hello World!";
}
} // namespace Testing


