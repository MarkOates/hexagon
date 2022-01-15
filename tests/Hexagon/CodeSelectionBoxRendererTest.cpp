
#include <gtest/gtest.h>

#include <Hexagon/CodeSelectionBoxRenderer.hpp>

#include <Testing/WithAllegroRenderingFixture.hpp>

class Hexagon_CodeSelectionBoxRendererTest : public ::testing::Test {};
class Hexagon_CodeSelectionBoxRendererTestWithAllegroRenderingFixture : public Testing::WithAllegroRenderingFixture {};


#include <Blast/StringSplitter.hpp>

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


TEST_F(Hexagon_CodeSelectionBoxRendererTest, can_be_created_without_blowing_up)
{
   Hexagon::CodeSelectionBoxRenderer renderer;
}

TEST_F(Hexagon_CodeSelectionBoxRendererTest, render__without_lines__throws_an_error)
{
   // TODO
}

TEST_F(Hexagon_CodeSelectionBoxRendererTest, render__without_code_range__throws_an_error)
{
   // TODO
}

TEST_F(Hexagon_CodeSelectionBoxRendererTestWithAllegroRenderingFixture, render__renders_as_expected_on_a_single_line)
{
   std::vector<std::string> lines = Blast::StringSplitter(sonnet).split();
   CodeRange code_range = { 0, 1, 10, 1 };
   Hexagon::CodeSelectionBoxRenderer renderer(&lines, &code_range, 0, 30, 50);
   renderer.render();
   al_flip_display();
   sleep(1);
}

TEST_F(Hexagon_CodeSelectionBoxRendererTestWithAllegroRenderingFixture,
   render_full_line_selection__renders_as_expected_on_a_single_line)
{
   std::vector<std::string> lines = Blast::StringSplitter(sonnet).split();
   CodeRange code_range = { 0, 2, 10, 5 };
   Hexagon::CodeSelectionBoxRenderer renderer(&lines, &code_range, 0, 30, 50);
   renderer.render_full_line_selection();
   al_flip_display();
   sleep(1);
}

TEST_F(Hexagon_CodeSelectionBoxRendererTestWithAllegroRenderingFixture,
   render__renders_as_expected_on_a_single_line_while_respecting_the_first_line_number)
{
   // TODO
}

TEST_F(Hexagon_CodeSelectionBoxRendererTest, render__renders_as_expected_over_multiple_lines)
{
   // TODO
}


