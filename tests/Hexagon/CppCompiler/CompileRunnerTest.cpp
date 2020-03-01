
#include <gtest/gtest.h>

#include <Hexagon/CppCompiler/CompileRunner.hpp>

TEST(Hexagon_CppCompiler_CompileRunnerTest, can_be_created_without_blowing_up)
{
   CppCompiler::CompileRunner compile_runner("project_root", "output_filename.txt");
}

