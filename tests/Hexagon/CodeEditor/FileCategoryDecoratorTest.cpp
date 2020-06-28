
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


TEST(Hexagon_CodeEditor_FileCategoryDecoratorTest, label__returns_the_expected_labels_for_the_known_category_types)
{
   // todo
}
