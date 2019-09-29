
#include <gtest/gtest.h>

#include <Hexagon/PasteboardData.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>

TEST(Hexagon_PasteboardDataTest, store__and__retrieve__are_able_to_store_data_from_the_system_clipboard)
{
   // clear the clipboard initially
   Blast::ShellCommandExecutorWithCallback clear_clipboard_setup_executor("printf \"\" | pbcopy");

   std::string initial_content = "Some random content for the clipboard";
   Hexagon::PasteboardData::store(initial_content);
   std::string pulled_value = Hexagon::PasteboardData::retrieve();

   EXPECT_EQ(initial_content, pulled_value);
}

TEST(Hexagon_PasteboardDataTest, store__and__retrieve__will_work_as_expected_when_containing_double_quotes)
{
   // clear the clipboard initially
   Blast::ShellCommandExecutorWithCallback clear_clipboard_setup_executor("printf \"\" | pbcopy");

   std::string initial_content = "Some \"random\" content 'for the clipboard', that \"has\" some quotes in it.";
   Hexagon::PasteboardData::store(initial_content);
   std::string pulled_value = Hexagon::PasteboardData::retrieve();

   EXPECT_EQ(initial_content, pulled_value);
}

TEST(Hexagon_PasteboardDataTest, store__and_retrieve__will_work_as_expected_when_containing_dollar_sign_symbols)
{
   // dollar sign symbols can represent shell variables and need to be escaped

   // clear the clipboard initially
   Blast::ShellCommandExecutorWithCallback clear_clipboard_setup_executor("printf \"\" | pbcopy");

   std::string initial_content = "Some $$ dolla $$ dolla bills";
   Hexagon::PasteboardData::store(initial_content);
   std::string pulled_value = Hexagon::PasteboardData::retrieve();

   EXPECT_EQ(initial_content, pulled_value);
}

TEST(Hexagon_PasteboardDataTest, store__and_retrieve__will_work_as_expected_when_containing_backslashes)
{
   // clear the clipboard initially
   Blast::ShellCommandExecutorWithCallback clear_clipboard_setup_executor("printf \"\" | pbcopy");

   std::stringstream initial_content;
   initial_content << "Some \\ backslashy \\ content here!";
   Hexagon::PasteboardData::store(initial_content.str());
   std::string pulled_value = Hexagon::PasteboardData::retrieve();

   EXPECT_EQ(initial_content.str(), pulled_value);
}
