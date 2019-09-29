
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
