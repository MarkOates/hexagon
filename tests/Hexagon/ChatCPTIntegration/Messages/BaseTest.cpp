
#include <gtest/gtest.h>

#include <Hexagon/ChatCPTIntegration/Messages/Base.hpp>


class MessagesBaseTestClass : public Hexagon::ChatCPTIntegration::Messages::Base
{
public:
   MessagesBaseTestClass()
      : Hexagon::ChatCPTIntegration::Messages::Base("MessagesBaseTestClass")
   {}
};


TEST(Hexagon_ChatCPTIntegration_Messages_BaseTest, can_be_created_without_blowing_up)
{
   Hexagon::ChatCPTIntegration::Messages::Base base;
}


TEST(Hexagon_ChatCPTIntegration_Messages_BaseTest, TYPE__has_the_expected_value)
{
   Hexagon::ChatCPTIntegration::Messages::Base base;
   EXPECT_EQ("Messages/Base", base.get_type());
}


TEST(Hexagon_ChatCPTIntegration_Messages_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   Hexagon::ChatCPTIntegration::Messages::Base base;
   EXPECT_EQ(Hexagon::ChatCPTIntegration::Messages::Base::TYPE, base.get_type());
}


TEST(Hexagon_ChatCPTIntegration_Messages_BaseTest, derived_classes_will_have_the_expected_type)
{
   MessagesBaseTestClass test_class;
   EXPECT_EQ("MessagesBaseTestClass", test_class.get_type());
}


