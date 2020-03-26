

#include <Blast/Search/Elasticsearch/HealthChecker.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>


namespace Blast
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

std::string HealthChecker::request_health()
{
std::string command = get_health_check_shell_command();
Blast::ShellCommandExecutorWithCallback executor(command);
std::string result = executor.execute();
return result;

}
} // namespace Elasticsearch
} // namespace Search
} // namespace Blast


