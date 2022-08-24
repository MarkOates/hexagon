
#include <gtest/gtest.h>

#include <Hexagon/ASTTraverser.hpp>


#define AST_JSON_TEST_FILENAME "/Users/markoates/Repos/hexagon/tests/fixtures/ast_dump.json"


TEST(Hexagon_ASTTraverserTest, can_be_created_without_blowing_up)
{
   Hexagon::ASTTraverser ast_traverser;
}


TEST(Hexagon_ASTTraverserTest, run__returns_the_expected_response)
{
   Hexagon::ASTTraverser ast_traverser(AST_JSON_TEST_FILENAME);
   //ast_traverser.initialize();
   //TODO: test file does not exist
}

