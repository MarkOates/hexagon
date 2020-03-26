#pragma once


#include <string>


namespace Blast
{
   namespace Search
   {
      namespace Elasticsearch
      {
         class HealthChecker
         {
         private:

         public:
            HealthChecker();
            ~HealthChecker();


         std::string run();
         std::string get_health_check_shell_command();
         bool is_up();
         std::string request_health();
         };
      }
   }
}



