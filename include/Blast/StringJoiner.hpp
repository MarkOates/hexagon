#pragma once


#include <string>
#include <vector>


namespace Blast
{
   class StringJoiner
   {
   private:
      std::vector<std::string> words;
      std::string delimiter;

   public:
      StringJoiner(std::vector<std::string> words={}, std::string delimiter=", ");
      ~StringJoiner();

      std::string join();
   };
} // namespace Blast


