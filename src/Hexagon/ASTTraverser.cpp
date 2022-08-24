

#include <Hexagon/ASTTraverser.hpp>
#include <stdexcept>
#include <sstream>
#include <fstream>
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


std::string ASTTraverser::get_json_ast_filename()
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
   std::ifstream ifs("test.json");
   nlohmann::json json = nlohmann::json::parse(ifs);
   initialized = true;
   return;
}
} // namespace Hexagon


