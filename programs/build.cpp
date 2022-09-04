#include <allegro5/allegro.h> // for compatibility with union/Makefile
#include <Hexagon/BuildSystem/BuildFactory.hpp>
#include <Hexagon/BuildSystem/ReportRenderer.hpp>
#include <iostream>
#include <sstream>


class ShellCommandBuilder
{
public:
   std::string project_directory;

   ShellCommandBuilder()
      : project_directory("/Users/markoates/Repos/TestProjectDeleteMe")
   {}

   std::string build_make_quintessence_shell_command()
   {
      std::stringstream build_stage_shell_command;
      build_stage_shell_command << "(cd " << project_directory << " && make quintessences)";
      return build_stage_shell_command.str();
   }
};


int main(int argc, char **argv)
{
   ShellCommandBuilder shell_command_builder;

   Hexagon::BuildSystem::BuildFactory build_factory;
   Hexagon::BuildSystem::Builds::Base* build = build_factory.create_shell_command_build(shell_command_builder.build_make_quintessence_shell_command());
   build->run();

   Hexagon::BuildSystem::ReportRenderer report_renderer(build);
   std::cout << report_renderer.build_text_report() << std::endl;

   return 0;
}


