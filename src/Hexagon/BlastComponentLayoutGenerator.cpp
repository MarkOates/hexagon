

#include <Hexagon/BlastComponentLayoutGenerator.hpp>
#include <Blast/Project/Component.hpp>
#include <iostream>
#include <Blast/ProjectComponentFilenameGenerator.hpp>
#include <Blast/ProjectComponentFileTypes.hpp>
#include <Blast/ProjectComponentFilenameGenerator.hpp>
#include <Blast/ProjectComponentFileTypes.hpp>
#include <Blast/ProjectComponentFilenameGenerator.hpp>
#include <Blast/ProjectComponentFileTypes.hpp>
#include <Blast/ProjectComponentFilenameGenerator.hpp>
#include <Blast/ProjectComponentFileTypes.hpp>


namespace Hexagon
{


BlastComponentLayoutGenerator::BlastComponentLayoutGenerator(std::string project_directory, std::string component_name, int code_editor_width, int code_editor_height)
   : project_directory(project_directory)
   , component_name(component_name)
   , code_editor_width(code_editor_width)
   , code_editor_height(code_editor_height)
{
}


BlastComponentLayoutGenerator::~BlastComponentLayoutGenerator()
{
}


Hexagon::Layout BlastComponentLayoutGenerator::generate()
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
            component_generate_header_filename(),
            "cpp_header",
            placement3d{ -(float)code_editor_width, 0, 0 },
         },
         {
            component_generate_source_filename(),
            "cpp_source",
            placement3d{ 0, 0, 0 },
         },
         {
            component_generate_test_filename(),
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
            component_generate_quintessence_filename(),
            "blast_quintessence",
            placement3d{ -((float)code_editor_width * 0.5f), 0, 0 },
         },
         {
            component_generate_test_filename(),
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

std::string BlastComponentLayoutGenerator::component_generate_header_filename()
{
Blast::ProjectComponentFilenameGenerator filename_generator(
        component_name,
        Blast::ProjectComponentFileTypes::HEADER_FILE);
return project_directory + filename_generator.generate_filename();

}

std::string BlastComponentLayoutGenerator::component_generate_source_filename()
{
auto generator = Blast::ProjectComponentFilenameGenerator(
   component_name,
   Blast::ProjectComponentFileTypes::SOURCE_FILE
);
return project_directory + generator.generate_filename();

}

std::string BlastComponentLayoutGenerator::component_generate_test_filename()
{
auto generator = Blast::ProjectComponentFilenameGenerator(
   component_name,
   Blast::ProjectComponentFileTypes::TEST_FILE
);
return project_directory + generator.generate_filename();

}

std::string BlastComponentLayoutGenerator::component_generate_quintessence_filename()
{
auto generator = Blast::ProjectComponentFilenameGenerator(
   component_name,
   Blast::ProjectComponentFileTypes::QUINTESSENCE_FILE
);
return project_directory + generator.generate_filename();

}
} // namespace Hexagon


