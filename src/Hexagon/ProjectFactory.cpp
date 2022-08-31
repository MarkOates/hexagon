

#include <Hexagon/ProjectFactory.hpp>

#include <Blast/FileExistenceChecker.hpp>
#include <Hexagon/ProjectFromYAML.hpp>
#include <allegro_flare/useful_php.h>


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

Hexagon::Project ProjectFactory::build_shopify_experts_conversations_system()
{
   std::string shopify_experts_conversations_system_project_title = "Shopify Experts Conversation System";
   std::string shopify_experts_conversations_system_project_filename =
     "/Users/markoates/Repos/me/hexagon_projects/shopify_experts_conversations_system.yml";
   if (!Blast::FileExistenceChecker(shopify_experts_conversations_system_project_filename).exists())
   {
      std::stringstream error_message;
      error_message << "[Hexagon/ProjectFactoy]: error: expecting the file \""
         << shopify_experts_conversations_system_project_filename
         << "\" to exist for reading, but it does not exist.";
      throw std::runtime_error(error_message.str());
   }
   std::string file_contents = php::file_get_contents(shopify_experts_conversations_system_project_filename);
   Hexagon::ProjectFromYAML project_from_yaml(
     shopify_experts_conversations_system_project_title,
     file_contents
   );
   return project_from_yaml.load();
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


