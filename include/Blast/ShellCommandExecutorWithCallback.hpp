#pragma once


#include <functional>
#include <string>


namespace Blast
{
   class ShellCommandExecutorWithCallback
   {
   private:
      std::string command;
      std::function<void(std::string)> callback;

   public:
      ShellCommandExecutorWithCallback();
      ~ShellCommandExecutorWithCallback();


   static void simple_cout_callback(std::string string_for_appending="");
   std::string execute();
   };
}



