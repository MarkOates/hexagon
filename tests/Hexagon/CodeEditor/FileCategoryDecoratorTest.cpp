
#include <gtest/gtest.h>

#include <Hexagon/CodeEditor/FileCategoryDecorator.hpp>

#include <utility>


TEST(Hexagon_CodeEditor_FileCategoryDecoratorTest, can_be_created_without_blowing_up)
{
   Hexagon::CodeEditor::FileCategoryDecorator file_category_decorator;
}


TEST(Hexagon_CodeEditor_FileCategoryDecoratorTest, label__returns_the_expected_labels_for_the_default)
{
   Hexagon::CodeEditor::FileCategoryDecorator file_category_decorator;
   std::string expected = "Undefined";
   ASSERT_EQ(expected, file_category_decorator.label());
}


TEST(Hexagon_CodeEditor_FileCategoryDecoratorTest, label__without_a_known_file_category__returns_the_expected_label)
{
   Hexagon::CodeEditor::FileCategoryDecorator file_category_decorator("file_category_that_does_not_exist");
   std::string expected = "Unknown";
   ASSERT_EQ(expected, file_category_decorator.label());
}


TEST(Hexagon_CodeEditor_FileCategoryDecoratorTest, label__returns_the_expected_labels_for_the_known_category_types)
{
   std::vector<std::pair<std::string, std::string>> expected_file_categories_and_labels = {
      { "undefined", "Undefined" },
      { "rails_model", "Model" },
      { "rails_model_test", "Model Test" },
      { "rails_controller", "Controller" },
      { "rails_controller_test", "Controller Test" },
      { "rails_routes", "Routes" },
   };

   for (auto &expected_file_category_and_label : expected_file_categories_and_labels)
   {
      std::string expected_file_category = expected_file_category_and_label.first;
      std::string expected_label = expected_file_category_and_label.second;

      Hexagon::CodeEditor::FileCategoryDecorator file_category_decorator(expected_file_category);
      std::string actual_label = file_category_decorator.label();
      EXPECT_EQ(expected_label, actual_label);
   }
}
