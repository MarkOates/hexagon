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


#include <Hexagon/RegexMatcher.hpp>




class ExpressionMatcher
{
public:
   std::string expression;
   std::string actual;

public:
   ExpressionMatcher(std::string expression=".*", std::string actual="foo")
      : expression(expression)
      , actual(actual)
   {}

   bool matches()
   {
      return !RegexMatcher(actual, expression).get_match_info().empty();
   }
};




class ValidateIconutil : public Hexagon::BuildSystem::BuildStages::Base
{
private:
   std::string get_result_of_dylibbuilder_shell_execution()
   {
      std::stringstream shell_command;
      shell_command << "iconutil";
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      return shell_command_executor.execute();
   }

public:
   static constexpr char* TYPE = "ValidateIconutil";

   ValidateIconutil()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
   {}

   virtual bool execute() override
   {
      std::string match_expression = "Usage: iconutil --convert "; //\( icns | iconset\) ";//\[\-\-output file\] file \[icon\-name\]";
      std::string actual_string = get_result_of_dylibbuilder_shell_execution();
      if (!ExpressionMatcher(match_expression, actual_string).matches()) return false;
      return true;
   }
};



class ValidateDylibBundlerVersion : public Hexagon::BuildSystem::BuildStages::Base
{
private:
   std::string get_result_of_dylibbuilder_shell_execution()
   {
      std::stringstream shell_command;
      shell_command << "dylibbundler";
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      return shell_command_executor.execute();
   }

public:
   static constexpr char* TYPE = "ValidateDylibBundlerVersion";

   ValidateDylibBundlerVersion()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
   {}

   virtual bool execute() override
   {
      std::string match_expression = "dylibbundler is a utility that helps bundle dynamic libraries inside macOS app bundles.\n";
      std::string actual_string = get_result_of_dylibbuilder_shell_execution();
      if (!ExpressionMatcher(match_expression, actual_string).matches()) return false;
      return true;
   }
};





int main(int argc, char **argv)
{
   Hexagon::BuildSystem::BuildStageFactory build_stage_factory;
   Hexagon::BuildSystem::Builds::Base *build = new Hexagon::BuildSystem::Builds::Base;
   build->set_build_stages({
      new ValidateDylibBundlerVersion(),
      new ValidateIconutil(),
   });
   build->run();
   //parallel_build->run_all_in_parallel();


   Hexagon::BuildSystem::ReportRenderer report_renderer(build);
   std::cout << report_renderer.build_text_report() << std::endl;

   return 0;
}




