#pragma once


#include <string>


namespace Blast
{
   class DirectoryExistenceChecker
   {
   private:
      std::string directory_name;

   protected:


   public:
      DirectoryExistenceChecker(std::string directory_name="");
      ~DirectoryExistenceChecker();

      bool exists();
   };
}



