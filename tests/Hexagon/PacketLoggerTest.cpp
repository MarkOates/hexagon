
#include <gtest/gtest.h>

#include <Hexagon/PacketLogger.hpp>

#include <Blast/FileExistenceChecker.hpp>

TEST(Hexagon_PacketLoggerTest, can_be_created_without_blowing_up)
{
   Hexagon::PacketLogger packet_logger;
}

TEST(Hexagon_PacketLoggerTest, DISABLED__generate_log_file_contents__returns_the_expected_response)
{
   Hexagon::PacketLogger packet_logger("blast", 123, 42, 87);
   std::string expected_file_contents = "foo";
   std::string actual_file_contents = packet_logger.generate_log_file_contents();
   EXPECT_EQ(expected_file_contents, actual_file_contents);
}

TEST(Hexagon_PacketLoggerTest, DISABLED__generate_log_filename__creates_a_filename_based_on_the_time)
{
   // TODO
}

TEST(Hexagon_PacketLoggerTest, PACKET_LOG_FOLDER_LOCATION__has_the_expected_default)
{
   Hexagon::PacketLogger packet_logger;
   std::string expected_packet_log_folder_location = "/Users/markoates/Repos/me/programming_logs";
   std::string actual_packet_log_folder_location = packet_logger.get_PACKET_LOG_FOLDER_LOCATION();
   EXPECT_EQ(expected_packet_log_folder_location, actual_packet_log_folder_location);
}

TEST(Hexagon_PacketLoggerTest, DISABLED__write_log_file__writes_the_log_file_to_the_destination)
{
   Hexagon::PacketLogger packet_logger("test-blast", 123, 42, 87);
   std::string filename_to_create = packet_logger.generate_log_filename();
   Blast::FileExistenceChecker file_existence_checker(filename_to_create);

   ASSERT_EQ(false, file_existence_checker.exists());
   packet_logger.write_log_file();
   ASSERT_EQ(true, file_existence_checker.exists());
}

TEST(Hexagon_PacketLoggerTest, generate_log_filename__creates_a_filename_based_on_the_time)
{
   // TODO
}

