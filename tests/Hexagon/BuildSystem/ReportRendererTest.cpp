
#include <gtest/gtest.h>

#include <Hexagon/BuildSystem/ReportRenderer.hpp>

#include <Hexagon/BuildSystem/BuildFactory.hpp>


TEST(Hexagon_BuildSystem_ReportRendererTest, can_be_created_without_blowing_up)
{
   Hexagon::BuildSystem::ReportRenderer report_renderer;
}


TEST(Hexagon_BuildSystem_ReportRendererTest,
   build_text_report__on_a_build_that_is_not_a_known_type__will_throw_an_error)
{
   // TODO
}


TEST(Hexagon_BuildSystem_ReportRendererTest,
   build_text_report__without_a_build__will_throw_an_error)
{
   // TODO
}


TEST(Hexagon_BuildSystem_ReportRendererTest,
   DISABLED__build_text_report__will_build_a_nicely_formatted_report_of_the_build)
   // TODO: report contains variable data (namely the duration line at the end of the report)
{
   Hexagon::BuildSystem::BuildFactory build_factory;
   Hexagon::BuildSystem::Builds::Base* build = build_factory.create_placeholder_build();

   Hexagon::BuildSystem::ReportRenderer report_renderer(build);
   std::string actual_report = report_renderer.build_text_report();

   std::string expected_report = "[========= BUILD =========]\n"
                                 "\n"
                                 "[#=------ STAGE 1 ------=#]\n"
                                 "  - Type: ShellCommand\n"
                                 "  - Status: [unset-status]\n"
                                 "  - Duration: 0 seconds\n"
                                 "  - Command: echo \"Hi friend\"\n"
                                 "\n"
                                 "[#=------ STAGE 2 ------=#]\n"
                                 "  - Type: ShellCommand\n"
                                 "  - Status: [unset-status]\n"
                                 "  - Duration: 0 seconds\n"
                                 "  - Command: echo \"Having a good day?\"\n"
                                 "\n"
                                 "[=========================]\n";

   EXPECT_EQ(expected_report, actual_report);

   delete build;
}


