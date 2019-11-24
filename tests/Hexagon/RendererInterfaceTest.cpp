
#include <gtest/gtest.h>

#include <Hexagon/RendererInterface.hpp>


class DerivedTestClass : public Hexagon::RendererInterface
{
public:
   DerivedTestClass()
      : Hexagon::RendererInterface()
   {}

   virtual void render() override
   {
      // empty
   }
};


TEST(Hexagon_RendererInterfaceTest, derived_class_can_be_created_without_blowing_up)
{
   DerivedTestClass test_class;
}

