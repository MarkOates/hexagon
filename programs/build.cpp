#include <allegro5/allegro.h> // for compatibility with union/Makefile
#include <Hexagon/BuildSystem/BuildFactory.hpp>
#include <Hexagon/BuildSystem/ReportRenderer.hpp>
#include <iostream>
#include <sstream>



#define BUILD_NUMBER "54321"


#include <Hexagon/BuildSystem/BuildStages/Base.hpp>
#include <string>
#include <allegro_flare/useful_php.h>


class BuildQuintessences : public Hexagon::BuildSystem::BuildStages::Base
{
   public:
      static constexpr char* TYPE = "BuildQuintessences";

   private:
      std::string project_directory;
      std::string build_number;

   public:
      BuildQuintessences(std::string project_directory, std::string build_number="000000")
         : Hexagon::BuildSystem::BuildStages::Base(BuildQuintessences::TYPE)
         , project_directory(project_directory)
         , build_number(build_number)
      {}
      virtual ~BuildQuintessences() {}

      virtual void execute() override
      {
         std::string filename_with_quintessences_list = project_directory + "/quintessences_" + build_number + ".txt";
         std::string contents = php::file_get_contents(filename_with_quintessences_list);
         std::cout << "==================" << std::endl;
         std::cout << contents << std::endl;
         std::cout << "===END============" << std::endl;
          // open file @ $(project_directory)/quintessences_BUILD_NUMBER.txt
      }
};



class ShellCommandBuilder
{
public:
   std::string project_directory;

   ShellCommandBuilder()
      : project_directory("/Users/markoates/Repos/TestProjectDeleteMe")
   {}

   std::string build_make_quintessence_shell_command()
   {
      std::stringstream output_filename;
      output_filename << "quintessences_" << BUILD_NUMBER << ".txt";
      std::stringstream build_stage_shell_command;
      build_stage_shell_command << "(cd " << project_directory << " && make list_quintessences > " << output_filename.str() << ")";
      return build_stage_shell_command.str();
   }
};


int main(int argc, char **argv)
{
   ShellCommandBuilder shell_command_builder;

   Hexagon::BuildSystem::BuildStageFactory build_stage_factory;
   //Hexagon::BuildSystem::Builds::Base* build = build_factory.create_shell_command_build(shell_command_builder.build_make_quintessence_shell_command());
   //build->run();

   Hexagon::BuildSystem::Builds::Base *build = new Hexagon::BuildSystem::Builds::Base;
   build->set_build_stages({
      build_stage_factory.create_shell_command_build_stage(shell_command_builder.build_make_quintessence_shell_command()),
   });
   build->run();

   Hexagon::BuildSystem::ReportRenderer report_renderer(build);
   std::cout << report_renderer.build_text_report() << std::endl;

   return 0;
}


