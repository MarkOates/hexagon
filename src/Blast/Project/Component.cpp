

#include <Blast/Project/Component.hpp>
#include <Blast/ProjectComponentFilenameGenerator.hpp>
#include <Blast/ProjectComponentFileTypes.hpp>
#include <Blast/FileExistenceChecker.hpp>
#include <Blast/ProjectComponentFileTypes.hpp>
#include <vector>
#include <Blast/ProjectComponentFileTypes.hpp>
#include <Blast/ProjectComponentFileTypes.hpp>
#include <Blast/ProjectComponentFileTypes.hpp>


namespace Blast
{
namespace Project
{


Component::Component(std::string name)
   : name(name)
{
}


Component::~Component()
{
}


std::string Component::get_name()
{
   return name;
}


bool Component::check_file_existence(Blast::ProjectComponentFileTypes::project_file_type_t type)
{
std::string filename = Blast::ProjectComponentFilenameGenerator(name, type).generate_filename();
return Blast::FileExistenceChecker(filename).exists();

}

bool Component::exists()
{
std::vector<Blast::ProjectComponentFileTypes::project_file_type_t> types_to_scan_for = {
   Blast::ProjectComponentFileTypes::QUINTESSENCE_FILE,
   Blast::ProjectComponentFileTypes::SOURCE_FILE,
   Blast::ProjectComponentFileTypes::HEADER_FILE,
   Blast::ProjectComponentFileTypes::TEST_FILE,
   Blast::ProjectComponentFileTypes::EXAMPLE_FILE,
   //Blast::ProjectComponentFileTypes::OBJECT_FILE,
   //Blast::ProjectComponentFileTypes::TEST_BINARY,
   //Blast::ProjectComponentFileTypes::EXAMPLE_BINARY,
};

for (auto &type_to_scan_for : types_to_scan_for)
{
   if (check_file_existence(type_to_scan_for)) return true;
}
return false;

}

bool Component::has_quintessence()
{
return check_file_existence(Blast::ProjectComponentFileTypes::QUINTESSENCE_FILE);

}

bool Component::has_only_source_and_header()
{
return (
  !has_quintessence()
  && check_file_existence(Blast::ProjectComponentFileTypes::SOURCE_FILE)
  && check_file_existence(Blast::ProjectComponentFileTypes::HEADER_FILE)
);

}

bool Component::has_test()
{
return check_file_existence(Blast::ProjectComponentFileTypes::TEST_FILE);

}
} // namespace Project
} // namespace Blast


