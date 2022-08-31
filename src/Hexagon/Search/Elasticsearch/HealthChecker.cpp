

#include <Hexagon/Search/Elasticsearch/HealthChecker.hpp>

#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Hexagon/RegexMatcher.hpp>


namespace Hexagon
{
namespace Search
{
namespace Elasticsearch
{


HealthChecker::HealthChecker()
{
}


HealthChecker::~HealthChecker()
{
}


std::string HealthChecker::run()
{
   return "Hello World!";
}

std::string HealthChecker::get_health_check_shell_command()
{
   std::string command = "curl -XGET \"http://localhost:9200/_cat/health\"";
   return command;
}

bool HealthChecker::is_up()
{
   std::string health_response = request_health();
   std::string up_regex = "[0-9]+ [0-9]+:[0-9]+:[0-9]+ [0-0a-zA-Z_]+ (yellow|red|green) .+";
   RegexMatcher matcher(health_response, up_regex);
   std::vector<std::pair<int, int>> match_infos = matcher.get_match_info();
   if (match_infos.empty()) return false;
   if (health_response.empty()) return false;
   return true;
}

std::string HealthChecker::request_health()
{
   std::string command = get_health_check_shell_command();
   Blast::ShellCommandExecutorWithCallback executor(command);
   std::string result = executor.execute();
   return result;
}


} // namespace Elasticsearch
} // namespace Search
} // namespace Hexagon


