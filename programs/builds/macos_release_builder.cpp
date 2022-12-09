



// !!!!!!
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




std::string TEMP_DIRECTORY_FOR_BUILD = "";
std::string TEMP_DIRECTORY_FOR_ICON = "";



class NameGenerator
{
public:
   static std::string SYSTEM_RELEASES_FOLDER; // "/Users/markoates/Releases/"
   static std::string SOURCE_RELEASE_FOLDER_NAME; // "TheWeepingHouse-SourceRelease-220903200818UTC"
   static std::string NAME_OF_EXECUTABLE; // "TheWeepingHouse"
   static std::string COPYRIGHT_FULL_TEXT; // "Copyright 2022 - Mark Oates - www.CLUBCATT.com"
   static std::string FULL_VERSION_NUMBER_WITH_BUILD; // "1.0.0.3"
   static std::string VERSION_NUMBER; // "1.0.0"
   static std::string FULL_PATH_TO_SOURCE_ICON_PNG; // "/Users/markoates/Releases/TheWeepingHouse-SourceRelease-220903200818UTC/data/system/allegro-flare-generic-icon-1024.png"


   static std::string TEMP_DIRECTORY_FOR_BUILD; // is generated
   static std::string TEMP_DIRECTORY_FOR_ICON;  // is generated


   static std::string source_release_folder_name() { return NameGenerator::SOURCE_RELEASE_FOLDER_NAME; }
   static std::string name_of_executable() { return NameGenerator::NAME_OF_EXECUTABLE; }
   static std::string readme_filename() { return "README.md"; }
   static std::string source_icon_filename() { return "Icon1024.png"; }
   static std::string built_icns_filename() { return "MyIcon.icns"; }
   static std::string full_path_of_temp_location_for_build() { return NameGenerator::TEMP_DIRECTORY_FOR_BUILD + "/"; }
   static std::string full_path_to_built_icns_file() { return NameGenerator::TEMP_DIRECTORY_FOR_ICON + "/" + built_icns_filename(); };
   static std::string name_of_built_executable() { return NameGenerator::NAME_OF_EXECUTABLE; }
   static std::string app_package_executable_name() { return NameGenerator::NAME_OF_EXECUTABLE; }
   static std::string app_package_folder_name() { return NameGenerator::NAME_OF_EXECUTABLE + ".app"; }
   static std::string full_path_to_copied_source_icns_file() { return NameGenerator::TEMP_DIRECTORY_FOR_ICON + "/" + source_icon_filename(); }
   static std::string release_folder_relative_to_system_releases_folder() { return "TheWeepingHouse-MacOS-chip_unknown"; }
   static std::string release_zip_filename() { return "TheWeepingHouse-MacOS-chip_unknown.zip"; }
   static std::string full_path_of_source_release_folder() { return "/Users/markoates/Releases/" + NameGenerator::SOURCE_RELEASE_FOLDER_NAME; }
};


std::string NameGenerator::SYSTEM_RELEASES_FOLDER; // "/Users/markoates/Releases/"
std::string NameGenerator::SOURCE_RELEASE_FOLDER_NAME; // "TheWeepingHouse-SourceRelease-220903200818UTC"
std::string NameGenerator::NAME_OF_EXECUTABLE; // "TheWeepingHouse"
std::string NameGenerator::COPYRIGHT_FULL_TEXT; // "Copyright 2022 - Mark Oates - www.CLUBCATT.com"
std::string NameGenerator::FULL_VERSION_NUMBER_WITH_BUILD; // "1.0.0.3"
std::string NameGenerator::VERSION_NUMBER; // "1.0.0"
std::string NameGenerator::FULL_PATH_TO_SOURCE_ICON_PNG; // "/Users/markoates/Releases/TheWeepingHouse-SourceRelease-220903200818UTC/data/system/allegro-flare-generic-icon-1024.png"
std::string NameGenerator::TEMP_DIRECTORY_FOR_BUILD; // auto-generated, different each run
std::string NameGenerator::TEMP_DIRECTORY_FOR_ICON; // auto-generated, different each run




//#define SOURCE_RELEASE_FOLDER_NAME NameGenerator::SOURCE_RELEASE_FOLDER_NAME
//#define NAME_OF_EXECUTABLE NameGenerator::name_of_executable()
//#define COPYRIGHT_FULL_TEXT NameGenerator::COPYRIGHT_FULL_TEXT
//#define FULL_VERSION_NUMBER_WITH_BUILD NameGenerator::FULL_VERSION_NUMBER_WITH_BUILD
//#define VERSION_NUMBER NameGenerator::VERSION_NUMBER
//#define FULL_PATH_TO_SOURCE_ICON_PNG NameGenerator::FULL_PATH_TO_SOURCE_ICON_PNG
//#define SYSTEM_RELEASES_FOLDER NameGenerator::SYSTEM_RELEASES_FOLDER
//#define README_FILENAME NameGenerator::readme_filename()
//#define SOURCE_ICON_FILENAME NameGenerator::source_icon_filename()
//#define BUILT_ICNS_FILENAME NameGenerator::built_icns_filename()
//#define NAME_OF_GENERATED_ICNS_FILE NameGenerator::built_icns_filename()
#define FULL_PATH_OF_TEMP_LOCATION_FOR_BUILD NameGenerator::full_path_of_temp_location_for_build()
//#define FULL_PATH_TO_BUILT_ICNS_FILE NameGenerator::full_path_to_built_icns_file()
//#define NAME_OF_BUILT_EXECUTABLE NameGenerator::name_of_built_executable()
//#define APP_PACKAGE_EXECUTABLE_NAME NameGenerator::app_package_executable_name()
//#define APP_PACKAGE_FOLDER_NAME NameGenerator::app_package_folder_name()



#define FULL_PATH_TO_DESTINATION_ICNS_FILE "/Users/markoates/Releases/TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Contents/Resources/Icon.icns"
#define FULL_PATH_TO_SOURCE_README (TEMP_DIRECTORY_FOR_BUILD + "/" + NameGenerator::readme_filename())
#define FULL_PATH_OF_SOURCE_DATA_FOLDER (TEMP_DIRECTORY_FOR_BUILD + "/data/")
#define FULL_PATH_TO_DESTINATION_README "/Users/markoates/Releases/TheWeepingHouse-MacOS-chip_unknown/README.md"
#define FULL_PATH_OF_DESTINATION_DATA_FOLDER "/Users/markoates/Releases/TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Contents/Resources/data"
#define RELEASE_FOLDER_LOCATION "/Users/markoates/Releases/TheWeepingHouse-MacOS-chip_unknown"
#define FULL_BINARY_APP_PACKAGE_DESTINATION ("/Users/markoates/Releases/TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Contents/MacOS/" + NameGenerator::name_of_built_executable())

//#define FULL_PATH_TO_COPIED_SOURCE_ICNS_FILE NameGenerator::full_path_to_copied_source_icns_file()
//#define FULL_PATH_OF_SOURCE_RELEASE_FOLDER "/Users/markoates/Releases/TheWeepingHouse-SourceRelease-220903200818UTC/"
//#define FULL_PATH_TO_RELEASE_ZIP_FILE "/Users/markoates/Releases/TheWeepingHouse-MacOS-chip_unknown.zip"
//#define RELEASE_ZIP_FILENAME "TheWeepingHouse-MacOS-chip_unknown.zip"
//#define RELEASE_FOLDER_RELATIVE_TO_SYSTEM_RELEASES_FOLDER "TheWeepingHouse-MacOS-chip_unknown"



#include <fstream>
bool file_put_contents(std::string filename, std::string contents)
{
   std::ofstream file;
   file.open(filename.c_str());
   if (!file.is_open()) return false;
   file << contents.c_str();
   file.close();
   return true;
}





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
   static constexpr char* TYPE = (char*)"ValidateIconutil";

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
   static constexpr char* TYPE = (char*)"ValidateDylibBundlerVersion";

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
   static constexpr char* TYPE = (char*)"ValidateSips";

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


class ValidateZip : public Hexagon::BuildSystem::BuildStages::Base
{
private:
   std::string get_result_of_shell_execution()
   {
      std::stringstream shell_command;
      shell_command << "zip -v";
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      return shell_command_executor.execute();
   }

public:
   static constexpr char* TYPE = (char*)"ValidateZip";

   ValidateZip()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
   {}

   virtual bool execute() override
   {
      std::string match_expression = "Copyright \\\(c\\\) 1990-2008 Info-ZIP - Type ";
      std::string actual_string = get_result_of_shell_execution();
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
   static constexpr char* TYPE = (char*)"CopySourceReleaseFilesForBuilding";
   std::string name_of_source_folder;
   std::string name_of_temp_location_to_build;
   std::string shell_command_result;
   std::string shell_command_response_code;

   CopySourceReleaseFilesForBuilding()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
      , name_of_source_folder(NameGenerator::full_path_of_source_release_folder())
      , name_of_temp_location_to_build(FULL_PATH_OF_TEMP_LOCATION_FOR_BUILD)
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
   static constexpr char* TYPE = (char*)"BuildFromSourceInTempFolder";
   std::string name_of_temp_location_to_build;
   std::string shell_command_result;
   std::string shell_command_response_code;

   BuildFromSourceInTempFolder()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
      , name_of_temp_location_to_build(FULL_PATH_OF_TEMP_LOCATION_FOR_BUILD)
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
   static constexpr char* TYPE = (char*)"ValidatePresenceOfBuiltExecutable";
   std::string name_of_temp_location_to_build;
   std::string name_of_expected_executable;
   std::string shell_command_result;
   std::string shell_command_response_code;

   ValidatePresenceOfBuiltExecutable()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
      , name_of_temp_location_to_build(FULL_PATH_OF_TEMP_LOCATION_FOR_BUILD)
      , name_of_expected_executable(NameGenerator::name_of_built_executable())
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_result == ("./" + name_of_expected_executable + "\nyes\n")) return true;
      return false;
   }
};



#include <Blast/FileExistenceChecker.hpp>

class CopySourceAppIconPngToTempFolder : public Hexagon::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      std::string source = full_path_to_source_icon_png;
      std::string destination = full_destination_path_to_copied_source_icns_file;

      std::stringstream shell_command;
      shell_command << "cp \"" << source << "\" \"" << destination << "\"";
      std::cout << shell_command.str() << std::endl;

      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"CopySourceAppIconPngToTempFolder";
   std::string full_path_to_source_icon_png;
   std::string full_destination_path_to_copied_source_icns_file;
   std::string shell_command_result;
   std::string shell_command_response_code;

   CopySourceAppIconPngToTempFolder()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
      , full_path_to_source_icon_png(NameGenerator::FULL_PATH_TO_SOURCE_ICON_PNG)
      , full_destination_path_to_copied_source_icns_file(NameGenerator::full_path_to_copied_source_icns_file())
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_response_code == ("0\n") && Blast::FileExistenceChecker(full_destination_path_to_copied_source_icns_file).exists()) return true;
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
      // TODO: Extract icon name
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
   static constexpr char* TYPE = (char*)"BuildAppIcons";
   std::string name_of_temp_folder_for_icons;
   std::string shell_command_result;
   std::string shell_command_response_code;

   BuildAppIcons()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
      , name_of_temp_folder_for_icons(TEMP_DIRECTORY_FOR_ICON)
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
      shell_command << "(cd " << name_of_temp_location_to_build << " && ((ls \"./" << name_of_expected_generated_icns_file << "\" && echo yes) || echo no))";
      std::cout << shell_command.str() << std::endl;
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"ValidatePresenceOfIcnsFile";
   std::string name_of_temp_location_to_build;
   std::string name_of_expected_generated_icns_file;
   std::string shell_command_result;
   std::string shell_command_response_code;

   ValidatePresenceOfIcnsFile()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
      , name_of_temp_location_to_build(TEMP_DIRECTORY_FOR_ICON)
      , name_of_expected_generated_icns_file(NameGenerator::built_icns_filename())
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_result == ("./" + name_of_expected_generated_icns_file + "\nyes\n")) return true;
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
   static constexpr char* TYPE = (char*)"CreateFoldersForReleaseAndAppPackage";
   std::string system_releases_folder;
   std::vector<std::string> folders_to_create;
   std::string shell_command_result;
   std::string shell_command_response_code;

   CreateFoldersForReleaseAndAppPackage()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
      , system_releases_folder(NameGenerator::SYSTEM_RELEASES_FOLDER)
      , folders_to_create({
         // TODO: extract these or build them
         "TheWeepingHouse-MacOS-chip_unknown",
         "TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app",
         "TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Contents",
         "TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Contents/MacOS",
         "TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Contents/Resources",
         })
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_response_code == "0\n") return true;
      return false;
   }
};



#include <Blast/TemplatedFile.hpp>

const std::string PLIST_TEMPLATE_CONTENT = R"DELIM(<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
	<key>CFBundleDevelopmentRegion</key>
	<string>English</string>
	<key>CFBundleExecutable</key>
	<string>[[NAME_OF_EXECUTABLE]]</string>
	<key>CFBundleIconFile</key>
	<string>Icon.icns</string>
	<key>CFBundleIdentifier</key>
	<string>org.markoates.[[NAME_OF_EXECUTABLE]]</string>
	<key>CFBundleInfoDictionaryVersion</key>
	<string>6.0</string>
	<key>CFBundleName</key>
	<string></string>
	<key>CFBundlePackageType</key>
	<string>APPL</string>
	<key>CFBundleShortVersionString</key>
	<string>[[FULL_VERSION_NUMBER_WITH_BUILD]]</string>
	<key>CFBundleSignature</key>
	<string>????</string>
	<key>CFBundleVersion</key>
	<string>[[VERSION_NUMBER]]</string>
	<key>CSResourcesFileMapped</key>
	<true/>
	<key>LSRequiresCarbon</key>
	<true/>
	<key>NSHighResolutionCapable</key>
	<true/>
	<key>NSHumanReadableCopyright</key>
	<string>[[COPYRIGHT_TEXT]]</string>
  <key>LSMultipleInstancesProhibited</key>
  <false/>
</dict>
</plist>
)DELIM";



class CreateInfoDotPlistFile : public Hexagon::BuildSystem::BuildStages::Base
{
public:
   static constexpr char* TYPE = (char*)"CreateInfoDotPlistFile";
   std::string system_releases_folder;

   CreateInfoDotPlistFile()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
      , system_releases_folder("/Users/markoates/Releases/")
   {}

   virtual bool execute() override
   {
      Blast::TemplatedFile plist_template(PLIST_TEMPLATE_CONTENT, {
            {  "[[NAME_OF_EXECUTABLE]]",  NameGenerator::NAME_OF_EXECUTABLE},
            {  "[[COPYRIGHT_TEXT]]",      NameGenerator::COPYRIGHT_FULL_TEXT },
            {  "[[FULL_VERSION_NUMBER_WITH_BUILD]]", NameGenerator::FULL_VERSION_NUMBER_WITH_BUILD },
            {  "[[VERSION_NUMBER]]", NameGenerator::VERSION_NUMBER },
         });

      std::string full_path_and_filename = system_releases_folder + "TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Contents/Info.plist";
      file_put_contents(full_path_and_filename, plist_template.generate_content());

      return Blast::FileExistenceChecker(full_path_and_filename).exists();
   }
};



class ValidateSourceReadme : public Hexagon::BuildSystem::BuildStages::Base
{
public:
   static constexpr char* TYPE = (char*)"ValidateSourceReadme";
   std::string full_location_to_source_readme_file;

   ValidateSourceReadme()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
      , full_location_to_source_readme_file(FULL_PATH_TO_SOURCE_README)
   {}

   virtual bool execute() override
   {
      return Blast::FileExistenceChecker(full_location_to_source_readme_file).exists();
   }
};



class CopyBuiltBinaryToAppPackage : public Hexagon::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      std::string source = name_of_temp_location_with_build + name_of_built_executable;
      std::string destination = FULL_BINARY_APP_PACKAGE_DESTINATION;

      std::stringstream shell_command;
      shell_command << "cp \"" << source << "\" \"" << destination << "\"";
      std::cout << shell_command.str() << std::endl;

      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"CopyBuiltBinaryToAppPackage";
   std::string name_of_temp_location_with_build;
   std::string name_of_built_executable;
   std::string shell_command_result;
   std::string shell_command_response_code;

   CopyBuiltBinaryToAppPackage()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
      , name_of_temp_location_with_build(FULL_PATH_OF_TEMP_LOCATION_FOR_BUILD)
      , name_of_built_executable(NameGenerator::name_of_built_executable())
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_response_code == ("0\n")) return true;
      return false;
   }
};



#include <Blast/DirectoryExistenceChecker.hpp>

class CopyDataFolderToAppPackage : public Hexagon::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      //TODO: require '/' character at end
      std::stringstream shell_command;
      shell_command << "cp -R \"" << full_path_of_source_data_folder << "\" \"" << full_path_of_app_package_destination_folder << "\"";
      std::cout << shell_command.str() << std::endl;
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"CopyDataFolderToAppPackage";
   std::string full_path_of_source_data_folder;
   std::string full_path_of_app_package_destination_folder;
   std::string shell_command_result;
   std::string shell_command_response_code;

   CopyDataFolderToAppPackage()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
      , full_path_of_source_data_folder(FULL_PATH_OF_SOURCE_DATA_FOLDER)
      , full_path_of_app_package_destination_folder(FULL_PATH_OF_DESTINATION_DATA_FOLDER)
      , shell_command_result()
      , shell_command_response_code()
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_response_code == "0\n" && Blast::DirectoryExistenceChecker(full_path_of_app_package_destination_folder).exists()) return true;
      return false;
   }
};




class CopyIcnsFileToAppPackage : public Hexagon::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      std::stringstream shell_command;
      shell_command << "cp \"" << full_source_location_of_icns_file << "\" \"" << full_destination_location << "\"";
      std::cout << shell_command.str() << std::endl;

      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"CopyIcnsFileToAppPackage";
   std::string full_source_location_of_icns_file;
   std::string full_destination_location;
   std::string shell_command_result;
   std::string shell_command_response_code;

   CopyIcnsFileToAppPackage()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
      , full_source_location_of_icns_file(NameGenerator::full_path_to_built_icns_file())
      , full_destination_location(FULL_PATH_TO_DESTINATION_ICNS_FILE)
   {}

   virtual bool execute() override
   {
      // TODO: validate existence of file
      execute_shell_commands();
      if (shell_command_response_code == ("0\n")) return true;
      return false;
   }
};



class CopyReadmeFileToRelaseFolder : public Hexagon::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      std::stringstream shell_command;
      shell_command << "cp \"" << full_location_to_source << "\" \"" << full_location_to_destination << "\"";
      std::cout << shell_command.str() << std::endl;

      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"CopyReadmeFileToRelaseFolder";
   std::string full_location_to_source;
   std::string full_location_to_destination;
   std::string shell_command_result;
   std::string shell_command_response_code;

   CopyReadmeFileToRelaseFolder()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
      , full_location_to_source(FULL_PATH_TO_SOURCE_README)
      , full_location_to_destination(FULL_PATH_TO_DESTINATION_README)
   {}

   virtual bool execute() override
   {
      // TODO: validate existence of file
      execute_shell_commands();
      if (shell_command_response_code == ("0\n")) return true;
      return false;
   }
};



class BuildAndBundleDylibsWithAppPackage : public Hexagon::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      std::string release_folder_location = RELEASE_FOLDER_LOCATION;
      std::string app_package_folder_name = NameGenerator::app_package_folder_name();
      std::string app_package_executable_name = NameGenerator::app_package_executable_name();
      std::stringstream shell_command;
      shell_command << "(cd " << release_folder_location << " && (export DYLD_LIBRARY_PATH=/usr/local/lib" << std::endl
                    << "dylibbundler -x \"" << app_package_folder_name << "/Contents/MacOS/" << app_package_executable_name << "\" -b -d \"" << app_package_folder_name << "/Contents/MacOS\" -p @executable_path -s $DYLD_LIBRARY_PATH"
                    << "))";

      std::cout << shell_command.str() << std::endl;

      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"BuildAndBundleDylibsWithAppPackage";
   std::string shell_command_result;
   std::string shell_command_response_code;

   BuildAndBundleDylibsWithAppPackage()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_response_code == ("0\n")) return true;
      return false;
   }
};




class CreateZipFromReleaseFolder : public Hexagon::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      std::stringstream shell_command;
      shell_command << "(cd " << NameGenerator::SYSTEM_RELEASES_FOLDER  << " && (zip -r \"" << NameGenerator::release_zip_filename() << "\" \"" << NameGenerator::release_folder_relative_to_system_releases_folder() << "\"))";
      std::cout << shell_command.str() << std::endl;

      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"CreateZipFromReleaseFolder";
   std::string shell_command_result;
   std::string shell_command_response_code;

   CreateZipFromReleaseFolder()
      : Hexagon::BuildSystem::BuildStages::Base(TYPE)
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_response_code == ("0\n")) return true;
      return false;
   }
};



#include <exception>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <filesystem>

std::filesystem::path create_temporary_directory(unsigned long long max_tries = 100000)
{
    auto tmp_dir = std::filesystem::temp_directory_path();
    unsigned long long i = 0;
    std::random_device dev;
    std::mt19937 prng(dev());
    std::uniform_int_distribution<uint64_t> rand(0);
    std::filesystem::path path;
    while (true) {
        std::stringstream ss;
        ss << std::hex << rand(prng);
        path = tmp_dir / ss.str();
        // true if the directory was created.
        if (std::filesystem::create_directory(path)) {
            break;
        }
        if (i == max_tries) {
            throw std::runtime_error("could not find non-existing directory");
        }
        i++;
    }
    return path;
}



int main(int argc, char **argv)
{
   //std::filesystem::path temporary_directory1 = create_temporary_directory();
   //std::filesystem::path temporary_directory2 = create_temporary_directory();

   TEMP_DIRECTORY_FOR_BUILD = create_temporary_directory();
   TEMP_DIRECTORY_FOR_ICON = create_temporary_directory();

   std::cout << "=== TEMP_DIRECTORY_FOR_BUILD ===" << std::endl;
   std::cout << TEMP_DIRECTORY_FOR_BUILD << std::endl;
   std::cout << "=== TEMP_DIRECTORY_FOR_ICON ===" << std::endl;
   std::cout << TEMP_DIRECTORY_FOR_ICON << std::endl;



   NameGenerator::SYSTEM_RELEASES_FOLDER = "/Users/markoates/Releases/";
   NameGenerator::SOURCE_RELEASE_FOLDER_NAME //= "TheWeepingHouse-SourceRelease-220903200818UTC";
                                             = "TheWeepingHouse-SourceRelease-221209152039UTC";

   NameGenerator::NAME_OF_EXECUTABLE = "TheWeepingHouse";
   NameGenerator::COPYRIGHT_FULL_TEXT = "Copyright 2022 - Mark Oates - www.CLUBCATT.com";
   NameGenerator::FULL_VERSION_NUMBER_WITH_BUILD = "1.0.0.3";
   NameGenerator::VERSION_NUMBER = "1.0.0";
   // TODO: consider moving this static location for the default icon, also only use it as a fallback if the repo does not have an app icon
   NameGenerator::FULL_PATH_TO_SOURCE_ICON_PNG = "/Users/markoates/Repos/allegro_flare/bin/data/bitmaps/allegro-flare-generic-icon-1024.png";
   //NameGenerator::FULL_PATH_TO_SOURCE_ICON_PNG = "/Users/markoates/Releases/" + NameGenerator::SOURCE_RELEASE_FOLDER_NAME + "/data/system/allegro-flare-generic-icon-1024.png";
   NameGenerator::TEMP_DIRECTORY_FOR_BUILD = TEMP_DIRECTORY_FOR_BUILD;
   NameGenerator::TEMP_DIRECTORY_FOR_ICON = TEMP_DIRECTORY_FOR_ICON;






   Hexagon::BuildSystem::BuildStageFactory build_stage_factory;
   Hexagon::BuildSystem::Builds::Base *build = new Hexagon::BuildSystem::Builds::Base;
   build->set_build_stages({
      new CopySourceAppIconPngToTempFolder(),

      // validate these are present
      new ValidateDylibBundlerVersion(),
      new ValidateIconutil(),
      new ValidateSips(),
      new ValidateZip(),

      // // TODO: validate README.md in source, validate source icon needed for icns file

      // get copy of source release
      new CopySourceReleaseFilesForBuilding(),
      new ValidateSourceReadme(),

      // make a build from the source
      new BuildFromSourceInTempFolder(),
      new ValidatePresenceOfBuiltExecutable(),

      // Make the app package
      // TODO: copy the source's app icon png into the temp location to build the icns file
      new CopySourceAppIconPngToTempFolder(),
      new BuildAppIcons(),
      new ValidatePresenceOfIcnsFile(),
      new CreateFoldersForReleaseAndAppPackage(),
      new CreateInfoDotPlistFile(),
      new CopyBuiltBinaryToAppPackage(),
      new CopyDataFolderToAppPackage(),
      new CopyIcnsFileToAppPackage(),
      new CopyReadmeFileToRelaseFolder(),
      new BuildAndBundleDylibsWithAppPackage(), // TODO: this process can error but it will not report an error

      // Zip it up and prepare it for launch
      new CreateZipFromReleaseFolder(),
   });
   build->run();
   //parallel_build->run_all_in_parallel();





   Hexagon::BuildSystem::ReportRenderer report_renderer(build);
   std::cout << report_renderer.build_text_report() << std::endl;

   return 0;
}
