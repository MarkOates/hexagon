
#include <gtest/gtest.h>

#include <NcursesArt/ProjectFilenameGenerator.hpp>

TEST(NcursesArt_ProjectFilenameGeneratorTest, extracts_the_expected_filenames)
{
   std::string basename = "Library/ComponentBasename";
   NcursesArt::ProjectFilenameGenerator generator(basename);

   std::string expected_quintessence_filename = "quintessence/Library/ComponentBasename.q.yml";
   std::string actual_basename = generator.generate_quintessence_filename();

   EXPECT_EQ(expected_quintessence_filename, actual_basename);
}

