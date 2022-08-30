

#include <Hexagon/ASTTraverser.hpp>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <Blast/FileExistenceChecker.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{


ASTTraverser::ASTTraverser(std::string json_ast_filename)
   : json_ast_filename(json_ast_filename)
   , json({})
   , initialized(false)
{
}


ASTTraverser::~ASTTraverser()
{
}


std::string ASTTraverser::get_json_ast_filename() const
{
   return json_ast_filename;
}


void ASTTraverser::set_json_ast_filename()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "ASTTraverser" << "::" << "set_json_ast_filename" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   return;
}

void ASTTraverser::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "ASTTraverser" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (json_ast_filename.empty() || !Blast::FileExistenceChecker(json_ast_filename).exists())
   {
      std::stringstream error_message;
      error_message << "Hexagon::ASTTraverser error: "
                    << "The file \"" << json_ast_filename << "\" does not exist. "
                    << "The current path is \"" << std::filesystem::current_path() << "\"";
      throw std::runtime_error(error_message.str());
   }

   std::ifstream ifs(json_ast_filename);
   nlohmann::json json = nlohmann::json::parse(ifs);
   initialized = true;
   return;
}
} // namespace Hexagon


