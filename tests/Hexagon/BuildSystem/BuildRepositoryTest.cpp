
#include <gtest/gtest.h>

#include <Hexagon/BuildSystem/BuildRepository.hpp>

TEST(Hexagon_BuildSystem_BuildRepositoryTest, can_be_created_without_blowing_up)
{
   Hexagon::BuildSystem::BuildRepository build_repository;
}

TEST(Hexagon_BuildSystem_BuildRepositoryTest, get_latest_if_exists__returns_nullptr_if_no_builds_are_present)
{
   Hexagon::BuildSystem::BuildRepository build_repository;
   EXPECT_EQ(nullptr, build_repository.get_latest_if_exists());
}
