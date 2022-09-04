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

      std::string build_list_quintessences_shell_command()
      {
         std::stringstream output_filename;
         output_filename << "ListQuintessences_" << BUILD_NUMBER << ".txt";
         std::stringstream shell_command;
         shell_command << "(cd " << project_directory << " && make list_quintessence_sources > " << output_filename.str() << ")";
         return shell_command.str();
      }

      virtual void execute() override
      {
         if (executed) return;
         Blast::ShellCommandExecutorWithCallback shell_command_executor(build_list_quintessences_shell_command());
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
      std::string shell_command_result;
      bool executed;

   public:
      BuildQuintessences(std::string project_directory, std::string build_number)
         : Hexagon::BuildSystem::BuildStages::Base(BuildQuintessences::TYPE)
         , project_directory(project_directory)
         , build_number(build_number)
         , shell_command_result()
         , executed(false)
      {}
      virtual ~BuildQuintessences() {}

      std::string build_make_quintessences_shell_command()
      {
         std::stringstream output_filename;
         output_filename << "BuildQuintessences_" << BUILD_NUMBER << ".txt";
         std::stringstream shell_command;
         shell_command << "(cd " << project_directory << " && make quintessences > " << output_filename.str() << ")";
         return shell_command.str();
      }

      virtual void execute() override
      {
         std::string filename_with_quintessences_list = project_directory + "/quintessences_" + build_number + ".txt";
         std::string contents = php::file_get_contents(filename_with_quintessences_list);
         std::vector<std::string> contents_lines = Blast::StringSplitter(contents, '\n').split();

         Blast::ShellCommandExecutorWithCallback shell_command_executor(build_make_quintessences_shell_command());
         shell_command_result = shell_command_executor.execute();
         executed = true;
      }
};


class ListObjects : public Hexagon::BuildSystem::BuildStages::Base
{
   public:
      static constexpr char* TYPE = "ListObjects";

   private:
      std::string project_directory;
      std::string build_number;
      std::string shell_command_result;
      bool executed;

   public:
      ListObjects(std::string project_directory, std::string build_number)
         : Hexagon::BuildSystem::BuildStages::Base(ListObjects::TYPE)
         , project_directory(project_directory)
         , build_number(build_number)
         , shell_command_result()
         , executed(false)
      {}
      virtual ~ListObjects() {}

      std::string build_list_quintessences_shell_command()
      {
         std::stringstream output_filename;
         output_filename << "ListObjects_" << BUILD_NUMBER << ".txt";
         std::stringstream shell_command;
         shell_command << "(cd " << project_directory << " && make list_objects > " << output_filename.str() << ")";
         return shell_command.str();
      }

      virtual void execute() override
      {
         if (executed) return;
         Blast::ShellCommandExecutorWithCallback shell_command_executor(build_list_quintessences_shell_command());
         shell_command_result = shell_command_executor.execute();
         executed = true;
      }
};


class BuildObjects : public Hexagon::BuildSystem::BuildStages::Base
{
   public:
      static constexpr char* TYPE = "BuildObjects";

   private:
      std::string project_directory;
      std::string build_number;
      std::string shell_command_result;
      bool executed;

   public:
      BuildObjects(std::string project_directory, std::string build_number)
         : Hexagon::BuildSystem::BuildStages::Base(BuildObjects::TYPE)
         , project_directory(project_directory)
         , build_number(build_number)
         , shell_command_result()
         , executed(false)
      {}
      virtual ~BuildObjects() {}

      std::string build_make_quintessences_shell_command()
      {
         std::stringstream output_filename;
         output_filename << "BuildObjects_" << BUILD_NUMBER << ".txt";
         std::stringstream shell_command;
         shell_command << "(cd " << project_directory << " && make objects > " << output_filename.str() << ")";
         return shell_command.str();
      }

      virtual void execute() override
      {
         //std::string filename_with_quintessences_list = project_directory + "/quintessences_" + build_number + ".txt";
         //std::string contents = php::file_get_contents(filename_with_quintessences_list);
         //std::vector<std::string> contents_lines = Blast::StringSplitter(contents, '\n').split();

         Blast::ShellCommandExecutorWithCallback shell_command_executor(build_make_quintessences_shell_command());
         shell_command_result = shell_command_executor.execute();
         executed = true;
      }
};


class ListTestObjects : public Hexagon::BuildSystem::BuildStages::Base
{
   public:
      static constexpr char* TYPE = "ListTestObjects";

   private:
      std::string project_directory;
      std::string build_number;
      std::string shell_command_result;
      bool executed;

   public:
      ListTestObjects(std::string project_directory, std::string build_number)
         : Hexagon::BuildSystem::BuildStages::Base(ListTestObjects::TYPE)
         , project_directory(project_directory)
         , build_number(build_number)
         , shell_command_result()
         , executed(false)
      {}
      virtual ~ListTestObjects() {}

      std::string build_list_quintessences_shell_command()
      {
         std::stringstream output_filename;
         output_filename << "ListTestObjects_" << BUILD_NUMBER << ".txt";
         std::stringstream shell_command;
         shell_command << "(cd " << project_directory << " && make list_test_objects > " << output_filename.str() << ")";
         return shell_command.str();
      }

      virtual void execute() override
      {
         if (executed) return;
         Blast::ShellCommandExecutorWithCallback shell_command_executor(build_list_quintessences_shell_command());
         shell_command_result = shell_command_executor.execute();
         executed = true;
      }
};


class BuildOneTestObject : public Hexagon::BuildSystem::BuildStages::Base
{
   public:
      static constexpr char* TYPE = "BuildOneTestObject";

   private:
      std::string project_directory;
      std::string build_number;
      std::string object_to_make;
      std::string shell_command_result;
      bool executed;

   public:
      BuildOneTestObject(std::string project_directory, std::string build_number, std::string object_to_make)
         : Hexagon::BuildSystem::BuildStages::Base(BuildOneTestObject::TYPE)
         , project_directory(project_directory)
         , build_number(build_number)
         , object_to_make(object_to_make)
         , shell_command_result()
         , executed(false)
      {}
      virtual ~BuildOneTestObject() {}

      std::string build_list_quintessences_shell_command()
      {
         //std::string object_to_make = "obj/tests/TestProjectDeleteMe/HelloTest.o";
         std::stringstream output_filename;
         output_filename << "BuildOneTestObject_" << BUILD_NUMBER << ".txt";
         std::stringstream shell_command;
         shell_command << "(cd " << project_directory << " && make " << object_to_make << " > " << output_filename.str() << ")";
         return shell_command.str();
      }

      virtual void execute() override
      {
         if (executed) return;
         Blast::ShellCommandExecutorWithCallback shell_command_executor(build_list_quintessences_shell_command());
         shell_command_result = shell_command_executor.execute();
         executed = true;
      }
};



int main(int argc, char **argv)
{
   Hexagon::BuildSystem::BuildStageFactory build_stage_factory;
   Hexagon::BuildSystem::Builds::Base *build = new Hexagon::BuildSystem::Builds::Base;
   build->set_build_stages({
      new ListQuintessences(PROJECT_DIRECTORY, BUILD_NUMBER),
      new BuildQuintessences(PROJECT_DIRECTORY, BUILD_NUMBER),
      new ListObjects(PROJECT_DIRECTORY, BUILD_NUMBER),
      new BuildObjects(PROJECT_DIRECTORY, BUILD_NUMBER),
      new ListTestObjects(PROJECT_DIRECTORY, BUILD_NUMBER),
      //new BuildOneTestObject(PROJECT_DIRECTORY, BUILD_NUMBER),
   });
   build->run();


   Hexagon::BuildSystem::ReportRenderer report_renderer(build);
   std::cout << report_renderer.build_text_report() << std::endl;


   Hexagon::BuildSystem::Builds::Base *parallel_build = new Hexagon::BuildSystem::Builds::Base;
   parallel_build->set_build_stages({
      new BuildOneTestObject(PROJECT_DIRECTORY, BUILD_NUMBER, "obj/tests/TestProjectDeleteMe/HelloTest.o"),
      new BuildOneTestObject(PROJECT_DIRECTORY, BUILD_NUMBER, "obj/tests/TestProjectDeleteMe/ProgramRunnerTest.o"),
      new BuildOneTestObject(PROJECT_DIRECTORY, BUILD_NUMBER, "obj/tests/TestProjectDeleteMe/ThirdThingTest.o"),
   });
   // NOTE that run_all_in_parallel is currenntly hard-coded to 3 build stages in BuildSystem/Builds/Base
   parallel_build->run_all_in_parallel();


   Hexagon::BuildSystem::ReportRenderer report_renderer2(parallel_build);
   std::cout << report_renderer2.build_text_report() << std::endl;

   return 0;
}



