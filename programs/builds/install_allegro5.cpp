



// Please read this document which outlines the steps involved:
// https://docs.google.com/document/d/1nTsH72zSUxwj--fjOwiCnbI7XXGvQvUtuvOSf5f5KVs/edit#




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


#include <Blast/StringJoiner.hpp>



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


class ValidateSips : public Hexagon::BuildSystem::BuildStages::Base
{
private:
   std::string get_result_of_dylibbuilder_shell_execution()
   {
      std::stringstream shell_command;
      shell_command << "sips -v";
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      return shell_command_executor.execute();
   }

public:
   static constexpr char* TYPE = "ValidateSips";

   ValidateSips()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
   {}

   virtual bool execute() override
   {
      std::string match_expression = "sips-[0-9]+\n";
      std::string actual_string = get_result_of_dylibbuilder_shell_execution();
      if (!ExpressionMatcher(match_expression, actual_string).matches()) return false;
      return true;
   }
};



class CopySourceReleaseFilesForBuilding : public Hexagon::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      //TODO: require '/' character at end
      std::stringstream shell_command;
      shell_command << "cp -R \"" << name_of_source_folder << "\" \"" << name_of_temp_location_to_build << "\"";
      std::cout << shell_command.str() << std::endl;
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = "CopySourceReleaseFilesForBuilding";
   std::string name_of_source_folder;
   std::string name_of_temp_location_to_build;
   std::string shell_command_result;
   std::string shell_command_response_code;

   CopySourceReleaseFilesForBuilding()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
      , name_of_source_folder("/Users/markoates/Releases/TheWeepingHouse-SourceRelease-220903200818UTC/")
      , name_of_temp_location_to_build("/Users/markoates/Releases/tmp/54321-MacOS/")
      , shell_command_result()
      , shell_command_response_code()
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_response_code == "0\n") return true;
      return false;
   }
};





class BuildFromSourceInTempFolder : public Hexagon::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      //TODO: require '/' character at end
      std::stringstream shell_command;
      shell_command << "(cd " << name_of_temp_location_to_build << " && make)";
      std::cout << shell_command.str() << std::endl;
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = "BuildFromSourceInTempFolder";
   std::string name_of_temp_location_to_build;
   std::string shell_command_result;
   std::string shell_command_response_code;

   BuildFromSourceInTempFolder()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
      , name_of_temp_location_to_build("/Users/markoates/Releases/tmp/54321-MacOS/")
      , shell_command_result()
      , shell_command_response_code()
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_response_code == "0\n") return true;
      return false;
   }
};



class ValidatePresenceOfBuiltExecutable : public Hexagon::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      //TODO: require '/' character at end
      std::stringstream shell_command;
      shell_command << "(cd " << name_of_temp_location_to_build << " && ((ls \"./" << name_of_expected_executable << "\" && echo yes) || echo no))";
      std::cout << shell_command.str() << std::endl;
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = "ValidatePresenceOfBuiltExecutable";
   std::string name_of_temp_location_to_build;
   std::string name_of_expected_executable;
   std::string shell_command_result;
   std::string shell_command_response_code;

   ValidatePresenceOfBuiltExecutable()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
      , name_of_temp_location_to_build("/Users/markoates/Releases/tmp/54321-MacOS/")
      , name_of_expected_executable("TheWeepingHouse")
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_result == ("./" + name_of_expected_executable + "\nyes\n")) return true;
      return false;
   }
};



class BuildAppIcons : public Hexagon::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      //TODO: require '/' character at end
      std::stringstream shell_command;

      // from https://stackoverflow.com/a/20703594/6072362
      std::vector<std::string> lines = {
         "mkdir MyIcon.iconset",
         "sips -z 16 16     Icon1024.png --out MyIcon.iconset/icon_16x16.png",
         "sips -z 32 32     Icon1024.png --out MyIcon.iconset/icon_16x16@2x.png",
         "sips -z 32 32     Icon1024.png --out MyIcon.iconset/icon_32x32.png",
         "sips -z 64 64     Icon1024.png --out MyIcon.iconset/icon_32x32@2x.png",
         "sips -z 128 128   Icon1024.png --out MyIcon.iconset/icon_128x128.png",
         "sips -z 256 256   Icon1024.png --out MyIcon.iconset/icon_128x128@2x.png",
         "sips -z 256 256   Icon1024.png --out MyIcon.iconset/icon_256x256.png",
         "sips -z 512 512   Icon1024.png --out MyIcon.iconset/icon_256x256@2x.png",
         "sips -z 512 512   Icon1024.png --out MyIcon.iconset/icon_512x512.png",
         "cp Icon1024.png MyIcon.iconset/icon_512x512@2x.png",
         "iconutil -c icns MyIcon.iconset",
         "rm -R MyIcon.iconset",
      };

      std::string lines_joined = Blast::StringJoiner(lines, "\n").join();

      shell_command << "(cd " << name_of_temp_folder_for_icons << " && (" << lines_joined << "))";
      std::cout << shell_command.str() << std::endl;
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = "BuildAppIcons";
   std::string name_of_temp_folder_for_icons;
   std::string shell_command_result;
   std::string shell_command_response_code;

   BuildAppIcons()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
      , name_of_temp_folder_for_icons("/Users/markoates/Releases/tmp/54321-IcnsFile/")
      , shell_command_result()
      , shell_command_response_code()
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_response_code == ("0\n")) return true;
      return false;
   }
};



class ValidatePresenceOfIcnsFile : public Hexagon::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      //TODO: require '/' character at end
      std::stringstream shell_command;
      shell_command << "(cd " << name_of_temp_location_to_build << " && ((ls \"./" << name_of_expected_executable << "\" && echo yes) || echo no))";
      std::cout << shell_command.str() << std::endl;
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = "ValidatePresenceOfIcnsFile";
   std::string name_of_temp_location_to_build;
   std::string name_of_expected_executable;
   std::string shell_command_result;
   std::string shell_command_response_code;

   ValidatePresenceOfIcnsFile()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
      , name_of_temp_location_to_build("/Users/markoates/Releases/tmp/54321-IcnsFile/")
      , name_of_expected_executable("MyIcon.icns")
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_result == ("./" + name_of_expected_executable + "\nyes\n")) return true;
      return false;
   }
};


class CreateFoldersForReleaseAndAppPackage : public Hexagon::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      std::vector<std::string> mkdir_commands;
      for (auto &folder_to_create : folders_to_create)
      {
         mkdir_commands.push_back("mkdir " + folder_to_create);
      }
      std::string mkdir_commands_chained = Blast::StringJoiner(mkdir_commands, " && ").join();

      std::stringstream shell_command;
      shell_command << "(cd " << system_releases_folder << " && (" << mkdir_commands_chained << "))";

      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = "CreateFoldersForReleaseAndAppPackage";
   std::string system_releases_folder;
   std::vector<std::string> folders_to_create;
   std::string shell_command_result;
   std::string shell_command_response_code;

   CreateFoldersForReleaseAndAppPackage()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
      , system_releases_folder("/Users/markoates/Releases/")
      , folders_to_create({
         "TheWeepingHouse-MacOS-chip_unknown",
         "TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app",
         "TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Content",
         "TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Content/MacOS",
         "TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Content/Resources",
         })
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_response_code == "0\n") return true;
      return false;
   }
};




int main(int argc, char **argv)
{
   Hexagon::BuildSystem::BuildStageFactory build_stage_factory;
   Hexagon::BuildSystem::Builds::Base *build = new Hexagon::BuildSystem::Builds::Base;
   build->set_build_stages({
      // validate these are present
      new ValidateDylibBundlerVersion(),
      new ValidateIconutil(),
      new ValidateSips(),

      // get copy of source release
      new CopySourceReleaseFilesForBuilding(),

      // make a build from the source
      new BuildFromSourceInTempFolder(),
      new ValidatePresenceOfBuiltExecutable(),
      new BuildAppIcons(),
      new ValidatePresenceOfIcnsFile(),
      new CreateFoldersForReleaseAndAppPackage(),
   });
   build->run();
   //parallel_build->run_all_in_parallel();


   Hexagon::BuildSystem::ReportRenderer report_renderer(build);
   std::cout << report_renderer.build_text_report() << std::endl;

   return 0;
}




