
#include <gtest/gtest.h>

#include <Hexagon/BuildSystem/ReportRenderers/Base.hpp>


class ReportRenderersBaseTestClass : public Hexagon::BuildSystem::ReportRenderers::Base
{
public:
   ReportRenderersBaseTestClass()
      : Hexagon::BuildSystem::ReportRenderers::Base("ReportRenderersBaseTestClass")
   {}
};


TEST(Hexagon_BuildSystem_ReportRenderers_BaseTest, can_be_created_without_blowing_up)
{
   Hexagon::BuildSystem::ReportRenderers::Base base;
}


TEST(Hexagon_BuildSystem_ReportRenderers_BaseTest, has_the_expected_type)
{
   Hexagon::BuildSystem::ReportRenderers::Base base;
   EXPECT_EQ("Base", base.get_type());
}


TEST(Hexagon_BuildSystem_ReportRenderers_BaseTest, derived_classes_will_have_the_expected_type)
{
   ReportRenderersBaseTestClass test_class;
   EXPECT_EQ("ReportRenderersBaseTestClass", test_class.get_type());
}


