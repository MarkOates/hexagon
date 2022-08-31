#pragma once


#include <string>


namespace Blast
{
   class FileExistenceChecker
   {
   private:
      std::string filename;

   protected:


   public:
      FileExistenceChecker(std::string filename="");
      ~FileExistenceChecker();

      std::string get_filename() const;
      bool exists();
   };
}



