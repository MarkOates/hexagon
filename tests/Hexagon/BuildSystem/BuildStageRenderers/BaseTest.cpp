
#include <gtest/gtest.h>

#include <Hexagon/BuildSystem/BuildStageRenderers/Base.hpp>


class BuildStageRenderersBaseTestClass : public Hexagon::BuildSystem::BuildStageRenderers::Base
{
public:
   BuildStageRenderersBaseTestClass()
      : Hexagon::BuildSystem::BuildStageRenderers::Base("BuildStageRenderersBaseTestClass")
   {}
};


TEST(Hexagon_BuildSystem_BuildStageRenderers_BaseTest, can_be_created_without_blowing_up)
{
   Hexagon::BuildSystem::BuildStageRenderers::Base base;
}


TEST(Hexagon_BuildSystem_BuildStageRenderers_BaseTest, has_the_expected_type)
{
   Hexagon::BuildSystem::BuildStageRenderers::Base base;
   EXPECT_EQ("Base", base.get_type());
}


TEST(Hexagon_BuildSystem_BuildStageRenderers_BaseTest, derived_classes_will_have_the_expected_type)
{
   BuildStageRenderersBaseTestClass test_class;
   EXPECT_EQ("BuildStageRenderersBaseTestClass", test_class.get_type());
}


