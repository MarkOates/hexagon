
#include <gtest/gtest.h>

#include <NcursesArt/ProjectComponentBasenameExtractor.hpp>

TEST(NcursesArt_ProjectComponentBasenameExtractorTest, extracts_the_expected_filenames_from_a_project_relative_path)
{
   std::string basename = "quintessence/Library/ComponentBasename.q.yml";
   NcursesArt::ProjectComponentBasenameExtractor extractor(basename);

   std::string expected_basename = "Library/ComponentBasename";
   std::string actual_basename = extractor.identify_component_basename();

   EXPECT_EQ(expected_basename, actual_basename);
}

TEST(NcursesArt_ProjectComponentBasenameExtractorTest, is_able_to_identify_the_component_as_valid)
{
   std::string basename = "quintessence/Library/ComponentBasename.q.yml";
   NcursesArt::ProjectComponentBasenameExtractor extractor(basename);

   EXPECT_EQ(true, extractor.is_identifiable_component());
}

TEST(NcursesArt_ProjectComponentBasenameExtractorTest, does_not_extract_the_expected_basename_from_an_absolute_path)
{
   std::string basename = "/Users/markoates/ProjectName/quintessence/Library/ComponentBasename.q.yml";
   NcursesArt::ProjectComponentBasenameExtractor extractor(basename);

   std::string expected_basename = "Library/ComponentBasename";
   std::string actual_basename = extractor.identify_component_basename();

   EXPECT_NE(expected_basename, actual_basename);
}

