
#include <gtest/gtest.h>

#include <Hexagon/BuildSystem/BuildStages/Base.hpp>


class BuildStagesBaseTestClass : public Hexagon::BuildSystem::BuildStages::Base
{
public:
   BuildStagesBaseTestClass()
      : Hexagon::BuildSystem::BuildStages::Base("BuildStagesBaseTestClass")
   {}
};


TEST(Hexagon_BuildSystem_BuildStages_BaseTest, can_be_created_without_blowing_up)
{
   Hexagon::BuildSystem::BuildStages::Base base;
}


TEST(Hexagon_BuildSystem_BuildStages_BaseTest, has_the_expected_type)
{
   Hexagon::BuildSystem::BuildStages::Base base;
   EXPECT_EQ("Base", base.get_type());
}


TEST(Hexagon_BuildSystem_BuildStages_BaseTest, derived_classes_will_have_the_expected_type)
{
   BuildStagesBaseTestClass test_class;
   EXPECT_EQ("BuildStagesBaseTestClass", test_class.get_type());
}


