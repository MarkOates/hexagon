

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
std::vector<std::tuple<std::string, Hexagon::Layout>> layouts = {};
return Hexagon::Project(project_name, layouts);

}

Hexagon::Project ProjectFactory::partner_performance_dashboard()
{
std::string project_name = "Partner Performance Dashboard";
std::vector<std::tuple<std::string, Hexagon::Layout>> layouts = {
   { "",
      {
         "models/ES::StoreRepository",
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

return Hexagon::Project(project_name, layouts);

}
} // namespace Hexagon


