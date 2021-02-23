
#include <gtest/gtest.h>

#include <Hexagon/Notifications/NotificationFactory.hpp>

TEST(Hexagon_Notifications_NotificationFactoryTest, can_be_created_without_blowing_up)
{
   Hexagon::Notifications::NotificationFactory notification_factory;
}

TEST(Hexagon_Notifications_NotificationFactoryTest,
   create_basic_notification__creates_a_notification_with_the_expected_values)
{
   Hexagon::Notifications::NotificationFactory notification_factory;
   std::string body_text = "Hello notification!";

   Hexagon::Notifications::Notification *created_notification =
      notification_factory.create_basic_notification(body_text);

   EXPECT_NE(nullptr, created_notification);
   EXPECT_EQ(body_text, created_notification->get_body_text());
}
