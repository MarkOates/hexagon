
#include <gtest/gtest.h>

#include <Hexagon/StringIndenter.hpp>


TEST(Hexagon_String_UnindenterTest, can_be_created_without_blowing_up)
{
   Hexagon::StringIndenter indenter;
}


TEST(Hexagon_String_UnindenterTest, unindent__will_remove_spaces)
{
std::string source = R"END(
   Foo
   Bar
      Baz
         Boz
   Biz
)END";

   Hexagon::StringIndenter indenter(source);
   std::string actual = indenter.unindent(2);

std::string expected = R"END(
 Foo
 Bar
    Baz
       Boz
 Biz
)END";

   EXPECT_EQ(expected, actual);
}


TEST(Hexagon_String_UnindenterTest, indent__will_add_spaces_to_the_front_of_each_line)
{
std::string source = R"END(
   Foo
   Bar
      Baz
         Boz
   Biz
)END";

   Hexagon::StringIndenter indenter(source);
   std::string actual = indenter.indent(3);

std::string expected = R"END(
      Foo
      Bar
         Baz
            Boz
      Biz
)END";

   EXPECT_EQ(expected, actual);
}
