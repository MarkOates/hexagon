
#include <gtest/gtest.h>

#include <Hexagon/CodeSelectionBoxRenderer.hpp>


const std::string sonnet = R"END(Is it thy will thy image should keep open
My heavy eyelids to the weary night?
Dost thou desire my slumbers should be broken,
While shadows like to thee do mock my sight?
Is it thy spirit that thou send'st from thee
So far from home into my deeds to pry,
To find out shames and idle hours in me,
The scope and tenor of thy jealousy?
O, no! thy love, though much, is not so great:
It is my love that keeps mine eye awake;
Mine own true love that doth my rest defeat,
To play the watchman ever for thy sake:
For thee watch I whilst thou dost wake elsewhere,
From me far off, with others all too near.

- William Shakespere)END";


TEST(Hexagon_CodeSelectionBoxRendererTest, can_be_created_without_blowing_up)
{
   std::vector<std::string> lines = {};
   CodeRange range = { 0, 0, 0, 0 };
   CodeSelectionBoxRenderer renderer(lines, range, 0, 10, 32);
}

TEST(Hexagon_CodeSelectionBoxRendererTest, the_expected_functions__without_initializing__raise_the_expected_errors)
{
   std::vector<std::string> lines = {};
   CodeRange range = { 0, 0, 0, 0 };
   CodeSelectionBoxRenderer renderer(lines, range, 0, 10, 32);
}

TEST(Hexagon_CodeSelectionBoxRendererTest, render__renders_as_expected_on_a_single_line)
{
   std::vector<std::string> lines = {};
   CodeRange range = { 0, 0, 0, 0 };
   CodeSelectionBoxRenderer renderer(lines, range, 0, 10, 32);
}

TEST(Hexagon_CodeSelectionBoxRendererTest, render__renders_the_expected_cursor_when_range_is_empty)
{
   std::vector<std::string> lines = {};
   CodeRange range = { 0, 0, 0, 0 };
   CodeSelectionBoxRenderer renderer(lines, range, 0, 10, 32);
}

TEST(Hexagon_CodeSelectionBoxRendererTest, render__renders_red__if_the_cursor_extends_over_void_range)
{
   std::vector<std::string> lines = {};
   CodeRange range = { 0, 0, 0, 0 };
   CodeSelectionBoxRenderer renderer(lines, range, 0, 10, 32);
}


