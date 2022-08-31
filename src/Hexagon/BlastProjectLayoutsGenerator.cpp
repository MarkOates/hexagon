

#include <Hexagon/BlastProjectLayoutsGenerator.hpp>

#include <Blast/Project/Component.hpp>
#include <Blast/Project/ComponentLister.hpp>
#include <Blast/ProjectComponentFileTypes.hpp>
#include <Blast/ProjectComponentFilenameGenerator.hpp>
#include <iostream>


namespace Hexagon
{


BlastProjectLayoutsGenerator::BlastProjectLayoutsGenerator(std::string project_directory)
   : project_directory(project_directory)
   , code_editor_width(1215)
   , code_editor_height(1350)
{
}


BlastProjectLayoutsGenerator::~BlastProjectLayoutsGenerator()
{
}


std::vector<Hexagon::Layout> BlastProjectLayoutsGenerator::generate()
{
   std::vector<Hexagon::Layout> result;

   Blast::Project::ComponentLister component_lister(project_directory);
   std::vector<std::string> component_names = component_lister.components();

   for (auto &component_name : component_names)
   {
      result.push_back(build_appropriate_layout_for_component(component_name));
   }

   return result;
}

Hexagon::Layout BlastProjectLayoutsGenerator::build_appropriate_layout_for_component(std::string component_name)
{
   Hexagon::Layout result;
   Blast::Project::Component component(component_name, project_directory);

   if (component.has_only_source_and_header())
   {
      // 3 expected files, synonymouse with
      // attempt_to_create_three_split_layout_fr...();
      result = Hexagon::Layout(
         component_name,
         {
            {
               component_generate_header_filename(component_name),
               "cpp_header",
               placement3d{ -(float)code_editor_width, 0, 0 },
            },
            {
               component_generate_source_filename(component_name),
               "cpp_source",
               placement3d{ 0, 0, 0 },
            },
            {
               component_generate_test_filename(component_name),
               "blast_test",
               placement3d{ (float)code_editor_width, 0, 0 },
            },
         }
      );
   }
   else if (component.has_quintessence() || component.has_test())
   {
      // 2 expected files, synonymous with
      // attempt_to_create_stage_from_last_component_navigator_selection();
      result = Hexagon::Layout(
         component_name,
         {
            {
               component_generate_quintessence_filename(component_name),
               "blast_quintessence",
               placement3d{ -((float)code_editor_width * 0.5f), 0, 0 },
            },
            {
               component_generate_test_filename(component_name),
               "blast_test",
               placement3d{ ((float)code_editor_width * 0.5f), 0, 0 },
            },
         }
      );

      return result;
   }
   else
   {
      std::cout << "cannot build_appropriate_layout_for_component "
                << "because the component \"" << component.get_name() << "\" "
                << "neither has a header/source combo nor a quintessence or test file."
                << std::endl;
      return {};
   }

   return result;
}

std::string BlastProjectLayoutsGenerator::component_generate_header_filename(std::string component_name)
{
   Blast::ProjectComponentFilenameGenerator filename_generator(
           component_name,
           Blast::ProjectComponentFileTypes::HEADER_FILE);
   return project_directory + filename_generator.generate_filename();
}

std::string BlastProjectLayoutsGenerator::component_generate_source_filename(std::string component_name)
{
   auto generator = Blast::ProjectComponentFilenameGenerator(
      component_name,
      Blast::ProjectComponentFileTypes::SOURCE_FILE
   );
   return project_directory + generator.generate_filename();
}

std::string BlastProjectLayoutsGenerator::component_generate_test_filename(std::string component_name)
{
   auto generator = Blast::ProjectComponentFilenameGenerator(
      component_name,
      Blast::ProjectComponentFileTypes::TEST_FILE
   );
   return project_directory + generator.generate_filename();
}

std::string BlastProjectLayoutsGenerator::component_generate_quintessence_filename(std::string component_name)
{
   auto generator = Blast::ProjectComponentFilenameGenerator(
      component_name,
      Blast::ProjectComponentFileTypes::QUINTESSENCE_FILE
   );
   return project_directory + generator.generate_filename();
}


} // namespace Hexagon


