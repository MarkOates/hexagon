
#include <gtest/gtest.h>

#include <Hexagon/Notifications/Notification.hpp>

TEST(Hexagon_Notifications_NotificationTest, can_be_created_without_blowing_up)
{
   Hexagon::Notifications::Notification notification;
}

TEST(Hexagon_Notifications_NotificationTest, body_text__has_a_getter__and_is_initialized_with_the_expected_value)
{
   Hexagon::Notifications::Notification notification;
   std::string expected_string = "";
   EXPECT_EQ(expected_string, notification.get_body_text());
}

