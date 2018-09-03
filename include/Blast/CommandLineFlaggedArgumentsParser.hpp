#pragma once


#include <string>
#include <vector>


namespace Blast
{
   class CommandLineFlaggedArgumentsParser
   {
   private:
      std::vector<std::string> command_line_args;

   public:
      CommandLineFlaggedArgumentsParser(std::vector<std::string> command_line_args);
      ~CommandLineFlaggedArgumentsParser();

      bool has_flag(std::string flag);
      std::vector<std::vector<std::string>> get_flagged_args(std::string flag);

   private:

      std::vector<int> find_flag_positions(std::string flag);
      std::vector<std::string> get_args_within_flag(int arg_position);
      bool is_flag(std::string potential_flag_value);
   };
} // namespace Blast


