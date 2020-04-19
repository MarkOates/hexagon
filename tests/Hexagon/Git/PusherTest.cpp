
#include <gtest/gtest.h>

#include <Hexagon/Git/Pusher.hpp>

TEST(Hexagon_Git_PusherTest, can_be_created_without_blowing_up)
{
   Hexagon::Git::Pusher pusher;
}

TEST(DISABLED_Hexagon_Git_PusherTest, can_be_created_without_blowing_up)
{
   // test is disabled because is a destructive action

   //Hexagon::Git::Pusher pusher;
   //pusher.push();
}

