
#include <gtest/gtest.h>

#include <Hexagon/BuildSystem/Builds/Base.hpp>


class BuildsBaseTestClass : public Hexagon::BuildSystem::Builds::Base
{
public:
   BuildsBaseTestClass()
      : Hexagon::BuildSystem::Builds::Base("BuildsBaseTestClass")
   {}
};


TEST(Hexagon_BuildSystem_Builds_BaseTest, can_be_created_without_blowing_up)
{
   Hexagon::BuildSystem::Builds::Base base;
}


TEST(Hexagon_BuildSystem_Builds_BaseTest, has_the_expected_type)
{
   Hexagon::BuildSystem::Builds::Base base;
   EXPECT_EQ("Base", base.get_type());
}


TEST(Hexagon_BuildSystem_Builds_BaseTest, derived_classes_will_have_the_expected_type)
{
   BuildsBaseTestClass test_class;
   EXPECT_EQ("BuildsBaseTestClass", test_class.get_type());
}


