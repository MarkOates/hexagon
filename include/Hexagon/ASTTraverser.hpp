#pragma once


#include <lib/nlohmann/json.hpp>
#include <string>


namespace Hexagon
{
   class ASTTraverser
   {
   private:
      std::string json_ast_filename;
      nlohmann::json json;
      bool initialized;

   public:
      ASTTraverser(std::string json_ast_filename={});
      ~ASTTraverser();

      std::string get_json_ast_filename() const;
      void set_json_ast_filename();
      void initialize();
   };
}



