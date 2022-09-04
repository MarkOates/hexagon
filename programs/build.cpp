#include <allegro5/allegro.h> // for compatibility with union/Makefile
#include <Hexagon/BuildSystem/BuildFactory.hpp>
#include <Hexagon/BuildSystem/ReportRenderer.hpp>
#include <iostream>
#include <sstream>



#define PROJECT_DIRECTORY "/Users/markoates/Repos/TestProjectDeleteMe"
#define BUILD_NUMBER "54321"


#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/StringSplitter.hpp>
#include <Hexagon/BuildSystem/BuildStages/Base.hpp>
#include <allegro_flare/useful_php.h>
#include <string>


class ListQuintessences : public Hexagon::BuildSystem::BuildStages::Base
{
   public:
      static constexpr char* TYPE = "ListQuintessences";

   private:
      std::string project_directory;
      std::string build_number;
      std::string shell_command_result;
      bool executed;

   public:
      ListQuintessences(std::string project_directory, std::string build_number)
         : Hexagon::BuildSystem::BuildStages::Base(ListQuintessences::TYPE)
         , project_directory(project_directory)
         , build_number(build_number)
         , shell_command_result()
         , executed(false)
      {}
      virtual ~ListQuintessences() {}

      std::string build_list_quintessence_shell_command()
      {
         std::stringstream output_filename;
         output_filename << "quintessences_" << BUILD_NUMBER << ".txt";
         std::stringstream shell_command;
         shell_command << "(cd " << project_directory << " && make list_quintessences > " << output_filename.str() << ")";
         return shell_command.str();
      }

      virtual void execute() override
      {
         if (executed) return;
         Blast::ShellCommandExecutorWithCallback shell_command_executor(build_list_quintessence_shell_command());
         shell_command_result = shell_command_executor.execute();
         executed = true;
      }
};


class BuildQuintessences : public Hexagon::BuildSystem::BuildStages::Base
{
   public:
      static constexpr char* TYPE = "BuildQuintessences";

   private:
      std::string project_directory;
      std::string build_number;

   public:
      BuildQuintessences(std::string project_directory, std::string build_number)
         : Hexagon::BuildSystem::BuildStages::Base(BuildQuintessences::TYPE)
         , project_directory(project_directory)
         , build_number(build_number)
      {}
      virtual ~BuildQuintessences() {}

      virtual void execute() override
      {
         std::string filename_with_quintessences_list = project_directory + "/quintessences_" + build_number + ".txt";
         std::string contents = php::file_get_contents(filename_with_quintessences_list);
         std::vector<std::string> contents_lines = Blast::StringSplitter(contents, '\n').split();
      }
};



class ShellCommandBuilder
{
public:
   std::string project_directory;

   ShellCommandBuilder()
      : project_directory(PROJECT_DIRECTORY)
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
   Hexagon::BuildSystem::Builds::Base *build = new Hexagon::BuildSystem::Builds::Base;
   build->set_build_stages({
      new ListQuintessences(PROJECT_DIRECTORY, BUILD_NUMBER),
      new BuildQuintessences(PROJECT_DIRECTORY, BUILD_NUMBER),
   });
   build->run();

   Hexagon::BuildSystem::ReportRenderer report_renderer(build);
   std::cout << report_renderer.build_text_report() << std::endl;

   return 0;
}



