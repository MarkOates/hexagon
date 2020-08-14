#include <allegro5/allegro.h>
#include <yaml-cpp/yaml.h>

int main(int, char**)
{
   std::string invalid_source_yaml = "{# ke\ny{:";       // magic broke-ya string
   YAML::Node node = YAML::Load(invalid_source_yaml);
   return 0;
}
