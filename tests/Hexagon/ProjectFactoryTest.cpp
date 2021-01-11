
#include <gtest/gtest.h>

#include <Hexagon/ProjectFactory.hpp>

TEST(Hexagon_ProjectFactoryTest, can_be_created_without_blowing_up)
{
   Hexagon::ProjectFactory project_factory;
}

TEST(Hexagon_ProjectFactoryText, shopify_experts_conversations_system__loads_the_shopify_experts_project)
{
   Hexagon::ProjectFactory project_factory;
   Hexagon::Project created_project = project_factory.build_shopify_experts_conversations_system();

   EXPECT_EQ("Shopify Experts Conversation System", created_project.get_project_name());
   EXPECT_EQ(2, created_project.get_layouts().size());
}

