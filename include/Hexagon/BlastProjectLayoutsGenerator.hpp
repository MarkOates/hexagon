#pragma once


#include <string>


namespace Hexagon
{
   class BlastProjectLayoutsGenerator
   {
   private:
      std::string project_directory;

   public:
      BlastProjectLayoutsGenerator(std::string project_directory={});
      ~BlastProjectLayoutsGenerator();


   void generate();
   };
}



