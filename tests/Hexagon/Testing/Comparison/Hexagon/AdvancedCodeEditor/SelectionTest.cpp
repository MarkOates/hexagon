
#include <gtest/gtest.h>

#include <Hexagon/Testing/Comparison/Hexagon/AdvancedCodeEditor/Selection.hpp>


TEST(Hexagon_Testing_Comparison_Hexagon_AdvancedCodeEditor_SelectionTest,
   PrintTo__with_an_AllegroFlare_Selection__will_output_as_expected)
{
   std::stringstream ss;
   Hexagon::AdvancedCodeEditor::Selection selection({
      CodeRange(4, 5, 9, 6),
      CodeRange(9, 19, 20, 19),
   });

   PrintTo(selection, &ss);

   std::string expected_output = "Selection([0]{4, 5, 9, 6, }, [1]{9, 19, 20, 19, }, )";
   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


TEST(Hexagon_Testing_Comparison_Hexagon_AdvancedCodeEditor_SelectionTest,
   equality_operator__when_true__works_with_google_test_EXPECT_statement)
{
   Hexagon::AdvancedCodeEditor::Selection selection({
      CodeRange(4, 5, 9, 6),
      CodeRange(9, 19, 20, 19),
   });
   Hexagon::AdvancedCodeEditor::Selection other_selection({
      CodeRange(4, 5, 9, 6),
      CodeRange(9, 19, 20, 19),
   });

   EXPECT_EQ(selection, other_selection);
}


TEST(Hexagon_Testing_Comparison_Hexagon_AdvancedCodeEditor_SelectionTest,
   equality_operator__when_false__works_with_google_test_EXPECT_statement)
{
   Hexagon::AdvancedCodeEditor::Selection selection({
      CodeRange(4, 5, 9, 6),
      CodeRange(9, 19, 20, 19),
   });
   Hexagon::AdvancedCodeEditor::Selection other_selection({
      CodeRange(4, 5, 9, 6),
      CodeRange(9, 20, 20, 20),
   });

   EXPECT_NE(selection, other_selection);
}


