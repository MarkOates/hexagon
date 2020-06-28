
#include <gtest/gtest.h>

#include <Hexagon/CodeEditor/FileCategoryDecorator.hpp>


TEST(Hexagon_CodeEditor_FileCategoryDecoratorTest, can_be_created_without_blowing_up)
{
   Hexagon::CodeEditor::FileCategoryDecorator file_category_decorator;
}


TEST(Hexagon_CodeEditor_FileCategoryDecoratorTest, label__returns_the_expected_labels_for_the_default)
{
   Hexagon::CodeEditor::FileCategoryDecorator file_category_decorator;
   std::string expected = "Undefined";
   EXPECT_EQ(expected, file_category_decorator.label());
}


TEST(Hexagon_CodeEditor_FileCategoryDecoratorTest, label__without_a_known_file_category__returns_the_expected_label)
{
   Hexagon::CodeEditor::FileCategoryDecorator file_category_decorator("file_category_that_does_not_exist");
   std::string expected = "Unknown";
   EXPECT_EQ(expected, file_category_decorator.label());
}


TEST(Hexagon_CodeEditor_FileCategoryDecoratorTest, label__returns_the_expected_labels_for_the_known_category_types)
{
   // todo
}
