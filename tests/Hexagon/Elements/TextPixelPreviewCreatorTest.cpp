
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/Elements/TextPixelPreviewCreator.hpp>

#include <allegro5/allegro_image.h>

static std::string VIM_DOCUMENTATION_EXCERPT = R"PASSAGE(
for illustration, here is a list of delete commands, grouped from small to big
objects.  Note that for a single character and a whole line the existing vi
movement commands are used.

      "dl"      delete character (alias: "x")       |dl|

      "diw"     delete inner word                   *diw*

      "daw"     delete a word                       *daw*

      "diW"     delete inner WORD (see |WORD|)      *diW*

      "daW"     delete a WORD (see |WORD|)          *daW*
      "dd"      delete one line                     |dd|

      "dis"     delete inner sentence               *dis*

      "das"     delete a sentence                   *das*

      "dib"     delete inner '(' ')' block          *dib*

      "dab"     delete a '(' ')' block              *dab*

      "dip"     delete inner paragraph              *dip*

      "dap"     delete a paragraph                  *dap*

      "diB"     delete inner '{' '}' block          *diB*

      "daB"     delete a '{' '}' block              *daB*

Note the difference between using a movement command and an object.  The
movement command operates from here (cursor position) to where the movement
takes us.  When using an object the whole object is operated upon, no matter
where on the object the cursor is.  For example, compare "dw" and "daw": "dw"
deletes from the cursor position to the start of the next word, "daw" deletes
the word under the cursor and the space after or before it.)PASSAGE";

#include <Blast/StringSplitter.hpp>

class Hexagon_Elements_TextPixelPreviewCreatorTestWithEmptyFixture : public ::testing::Test
{};

#include <Testing/WithAllegroRenderingFixture.hpp>

class Hexagon_Elements_TextPixelPreviewCreatorTestWithAllegroRenderingFixture
   : public Testing::WithAllegroRenderingFixture
{};

TEST_F(Hexagon_Elements_TextPixelPreviewCreatorTestWithEmptyFixture, can_be_created_without_blowing_up)
{
   Hexagon::Elements::TextPixelPreviewCreator text_pixel_preview_creator;
}

TEST_F(Hexagon_Elements_TextPixelPreviewCreatorTestWithEmptyFixture,
   create__without_allegro_initialized__raises_an_error)
{
   Hexagon::Elements::TextPixelPreviewCreator text_pixel_preview_creator;
   std::string expected_error_message =
      "TextPixelPreviewCreator::create: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(text_pixel_preview_creator.create(), std::runtime_error, expected_error_message);
}

TEST_F(Hexagon_Elements_TextPixelPreviewCreatorTestWithAllegroRenderingFixture,
   create__will_create_a_bitmap_matching_the_width_and_height_for_the_text)
{
   std::vector<std::string> lines = Blast::StringSplitter(VIM_DOCUMENTATION_EXCERPT, '\n').split();
   Hexagon::Elements::TextPixelPreviewCreator text_pixel_preview_creator(lines);
   ALLEGRO_BITMAP *text_pixel_preview = text_pixel_preview_creator.create();

   ASSERT_EQ(120, al_get_bitmap_width(text_pixel_preview));
   //ASSERT_EQ(38, al_get_bitmap_height(text_pixel_preview));

   int bitmap_width = al_get_bitmap_width(text_pixel_preview);
   int bitmap_height = al_get_bitmap_height(text_pixel_preview);

   placement3d place = build_centered_placement(bitmap_width, bitmap_height);
   place.scale = vec3d(9, 9, 9);
   place.start_transform();
   al_draw_bitmap(text_pixel_preview, 0, 0, 0);
   place.restore_transform();
   al_flip_display();
   //sleep(2);

   al_destroy_bitmap(text_pixel_preview);
}

