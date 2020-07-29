

#include <Hexagon/ProjectFactory.hpp>



namespace Hexagon
{


ProjectFactory::ProjectFactory()
{
}


ProjectFactory::~ProjectFactory()
{
}


Hexagon::Project ProjectFactory::hexagon()
{
std::string project_name = "Hexagon";
std::string project_root = "/Users/markoates/Repos/hexagon/";
std::vector<std::tuple<std::string, Hexagon::Layout>> layouts = {};
return Hexagon::Project(project_name, project_root, layouts);

}

Hexagon::Project ProjectFactory::partner_performance_dashboard()
{
type: std::vector<StageInterface *>* stages = nullptr;

std::string project_name = "Partner Performance Dashboard";
std::string project_root = "/Users/markoates/dev_repos/partners/";
std::vector<std::tuple<std::string, Hexagon::Layout>> layouts = {
   { "",
      {
         "models/ES::StoreRepository",
         project_root,
         stages,
         {
            {
               "/Users/markoates/dev_repos/partners/app/models/es/store_repository.rb",
               "rails_model",
               {},
            },
            {
               "/Users/markoates/dev_repos/partners/spec/models/es/store_repository_spec.rb",
               "rails_spec",
               {},
            }
         },
      },
   }
};

return Hexagon::Project(project_name, project_root, layouts);

}
} // namespace Hexagon


