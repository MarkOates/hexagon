
#include <gtest/gtest.h>

#include <Hexagon/SymlinkToucher.hpp>

#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/FileExistenceChecker.hpp>
#include <Blast/FileLastWriteTime.hpp>

std::string get_symlink_write_time(std::string filename)
{
   Blast::ShellCommandExecutorWithCallback executor(std::string("stat ") + filename);
   std::string result = executor.execute();
   return result;
}

TEST(Hexagon_SymlinkToucherTest, can_be_created_without_blowing_up)
{
   Hexagon::SymlinkToucher symlink_toucher;
}

TEST(DISABLED_Hexagon_SymlinkToucherTest, touch_if_symlink__will_modify_the_file_timestamp)
   // DISABLED because modifies fixture files
{
   std::string filename = "/Users/markoates/repos/hexagon/tests/fixtures/symlink_of_file_that_has_symlink.txt";
   Hexagon::SymlinkToucher symlink_toucher(filename);

   std::string before_touch_write_time = get_symlink_write_time(filename);

   symlink_toucher.touch_if_symlink();

   std::string after_touch_write_time = get_symlink_write_time(filename);

   ASSERT_NE(before_touch_write_time, after_touch_write_time);
}

TEST(Hexagon_SymlinkToucherTest, touch_if_symlink__will_not_modify_the_file_timestamp_if_it_is_not_a_symlink)
{
   std::string filename = "/Users/markoates/repos/hexagon/tests/fixtures/file_that_has_symlink.txt";
   Hexagon::SymlinkToucher symlink_toucher(filename);

   std::time_t before_touch_write_time = Blast::FileLastWriteTime(filename).last_write_time();

   symlink_toucher.touch_if_symlink();

   std::time_t after_touch_write_time = Blast::FileLastWriteTime(filename).last_write_time();

   ASSERT_EQ(before_touch_write_time, after_touch_write_time);
}

TEST(Hexagon_SymlinkToucherTest, touch_if_symlink__will_not_create_a_new_file)
{
   std::string filename = "file_that_should_not_exist_before_or_after_test.txt";

   Blast::FileExistenceChecker before_file_existence_checker(filename);
   EXPECT_EQ(false, before_file_existence_checker.exists());

   Hexagon::SymlinkToucher symlink_toucher(filename);
   symlink_toucher.touch_if_symlink();

   Blast::FileExistenceChecker after_file_existence_checker(filename);
   ASSERT_EQ(false, after_file_existence_checker.exists());
}

